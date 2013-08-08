/*
 * level.c
 *
 *
 * Level functions
 *
 *
 * Copyright (C) 2013  Bryant Moscon - bmoscon@gmail.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions, and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution, and in the same 
 *    place and form as other copyright, license and disclaimer information.
 *
 * 3. The end-user documentation included with the redistribution, if any, must 
 *    include the following acknowledgment: "This product includes software 
 *    developed by Bryant Moscon (http://www.bryantmoscon.org/)", in the same 
 *    place and form as other third-party acknowledgments. Alternately, this 
 *    acknowledgment may appear in the software itself, in the same form and 
 *    location as other such third-party acknowledgments.
 *
 * 4. Except as contained in this notice, the name of the author, Bryant Moscon,
 *    shall not be used in advertising or otherwise to promote the sale, use or 
 *    other dealings in this Software without prior written authorization from 
 *    the author.
 *
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 *
 */
#define _XOPEN_SOURCE_EXTENDED


#include <stdlib.h>

#include "level.h"
#include "draw.h"
#include "items.h"
#include "tools.h"
#include "logger.h"


static void add_door(int x, int y, int r, bool h, state_st *state)
{
  for (int i = 0; i < MAX_DOORS; ++i) {
    if (state->map.rooms[r].doors[i].pos.x == 0 && state->map.rooms[r].doors[i].pos.y == 0) {
      state->map.rooms[r].doors[i].pos.x = x;
      state->map.rooms[r].doors[i].pos.y = y;
      state->map.rooms[r].doors[i].hidden = h;
      return;
    }
  }
}

static void add_tunnel(int x, int y, int end_x, int end_y, int r, state_st *state)
{
  int d_x = (end_x - x) ? 1 : 0;
  int d_y = (end_y - y) ? 1 : 0;
  int len = (end_x - x)  + (end_y - y);

  log_debug("d_x: %d, d_y %d, len: %d", d_x, d_y, len);

  for (int i = 0; i < MAX_DOORS; ++i) {
    if (!state->map.rooms[r].tunnels[i].pos) {
      state->map.rooms[r].tunnels[i].pos = malloc(sizeof(coord_st) * len);
      if (!state->map.rooms[r].tunnels[i].pos) {
	endwin();
	log_error("out of memory");
	logger_stop();
	free_state(state); 
	exit(EXIT_FAILURE);
      }

      state->map.rooms[r].tunnels[i].len = len;
      
      for (int j = 0; j < len; ++j) {
	state->map.rooms[r].tunnels[i].pos[j].x = x;
	state->map.rooms[r].tunnels[i].pos[j].y = y;
	x += d_x;
	y += d_y;
      }

      return;
    }
  }
}


static void tunnel_to_room(int dir_x, int dir_y, int r, state_st *state)
{
  if (r >= state->map.num_rooms) {
    return;
  }

  int x = state->map.rooms[r].pos.x;
  int y = state->map.rooms[r].pos.y;
  
  if (dir_x == 1) {
    x += state->map.rooms[r].x_len;
  } else if (dir_x == -1) {
    x -= 1;
  }

  if (dir_y == 1) {
    y += state->map.rooms[r].y_len;
  } else if (dir_y == -1) {
    y -= 1;
  }

  
  if (dir_y == 0) {
    for (int i = x; (i > 0) && (i < MAP_COL); i += dir_x) {
      for (int j = y+1; j < y + state->map.rooms[r].y_len - 1; ++j) {
	int ret = get_room(i, j, state);
	if (ret >= 0) {
	  if (in_room_corners(i, j, ret, state)) {
	    // we are hitting a corner, continue to the next y increment;
	    continue;
	  }
	  
	  log_debug("adding door at %d, %d in room %d", i, j, ret);
	  add_door(i, j, ret, false, state);
	  add_door(x-1, j, r, false, state);
	  log_debug("calling add tunnel with start (%d, %d), end (%d, %d), room %d",
		    x, j, i-1, j, r);
	  add_tunnel(x, j, i, j, r, state);
	  return;
	}
      }
    } 
  }

  if (dir_x == 0) {
    for (int i = x + 1; i < x + state->map.rooms[r].x_len - 1; ++i) {
      for (int j = y; (j > 0) && (j < MAP_ROW); j += dir_y) {
	int ret = get_room(i, j, state);
	if (ret >= 0) {
	  if (in_room_corners(i, j, ret, state)) {
	    // we are currently running inside of a wall, break out to the next iteration of the
	    // outer loop
	    break;
	  }
	  
	  add_door(i, j, ret, false, state);
	  add_door(i, y-1, r, false, state);
	  add_tunnel(i, y, i, j, r, state);
	  return;
	}
      } 
    }
  }
  
}

static void generate_rooms(state_st *state)
{
  int room_height_max;
  int room_width_max;
  int i;
  
  map_st *map = &(state->map);
  room_st *curr_room;
  
  // randomly determine number of rooms
  map->num_rooms = random(ROOMS_MIN, ROOMS_MAX);
  map->rooms = (room_st *)calloc(map->num_rooms, sizeof(room_st));
  if (!map->rooms) {
    endwin();
    log_error("out of memory");
    logger_stop();
    free_state(state); 
    exit(EXIT_FAILURE);
  }
  
  // determine max room dimensions
  room_width_max = (MAP_COL / 3);
  if (map->num_rooms == 3) {
    room_height_max = MAP_ROW;
  } else if (map->num_rooms <= 6) {
    room_height_max = 11;
  } else {
    room_height_max = 7;
  }

  // randomly generate dimensions for each room
  for (i = 0; i < map->num_rooms; ++i) {
    int startx;
    int starty;
    curr_room = &(map->rooms[i]);
    
    curr_room->y_len = random(ROOM_DIM_MIN, room_height_max);
    curr_room->x_len = random(ROOM_DIM_MIN, room_width_max);
    
    startx = (MAP_COL / 3) * (i % 3);
    starty = room_height_max * (i / 3);

    // randomize x,y
    startx += random(0, room_width_max - curr_room->x_len);
    // min is 1 because we use the top row of the screen for text messages
    starty += random(1, room_height_max - curr_room->y_len);
    
    curr_room->pos.x = startx;
    curr_room->pos.y = starty;
  }
}


static void randomize_tunnels(state_st *state)
{
  // connect all rooms to the right, and below
  for (int i = 0; i < state->map.num_rooms; ++i) {
    tunnel_to_room(1, 0, i, state);
    tunnel_to_room(0, 1, i, state);
  }
}


static void randomize_positions(state_st *state)
{
  map_st *m = &(state->map);
  // pick random room
  int r = random(0, state->map.num_rooms);
  int s = random(0, state->map.num_rooms);
  
  // pick random coords in rooms
  state->x = random(m->rooms[r].pos.x + 1, m->rooms[r].pos.x + m->rooms[r].x_len - 2);
  state->y = random(m->rooms[r].pos.y + 1, m->rooms[r].pos.y + m->rooms[r].y_len - 2);

  m->stairs.x = random(m->rooms[s].pos.x + 1, m->rooms[s].pos.x + m->rooms[s].x_len - 2);
  m->stairs.y = random(m->rooms[s].pos.y + 1, m->rooms[s].pos.y + m->rooms[s].y_len - 2);
  
}


void init_level(state_st *state)
{
  generate_rooms(state);
  randomize_tunnels(state);
  randomize_positions(state);
  
}

void draw_level(const state_st *state)
{
  int i;
  int j;
  int r;
  bool tunnel = false;
  WINDOW *win = state->game;
  const map_st *map = &(state->map);
  

  r = get_room(state->x, state->y, state);

  for (i = 0; i < map->num_rooms; ++i) {
    // draw room
    draw_room(map->rooms[i].pos.x, map->rooms[i].pos.y, map->rooms[i].y_len, 
	      map->rooms[i].x_len, (i == r), win);
    
    // draw doors on room
    for (j = 0; map->rooms[i].doors[j].pos.x && map->rooms[i].doors[j].pos.y; ++j) {
      if (!map->rooms[i].doors[j].hidden) {
	draw_door(map->rooms[i].doors[j].pos.x, map->rooms[i].doors[j].pos.y, win);
      }
    }
    
    if (r == i) {
      // draw objects in room
      for (j = 0; j < MAX_ITEMS; ++j) {
	draw_items(map->rooms[i].items[j].pos.x, map->rooms[i].items[j].pos.y, 
		   map->rooms[i].items[j].type, win);
      }
    }

    // draw tunnels
    for (j = 0; j < MAX_DOORS; ++j) {
      for (int t = 0; t < map->rooms[i].tunnels[j].len; ++t) {
	if ((state->x == map->rooms[i].tunnels[j].pos[t].x) && 
	    (state->y == map->rooms[i].tunnels[j].pos[t].y)) {
	  tunnel = true;
	}
	
	draw_tunnel(map->rooms[i].tunnels[j].pos[t].x, map->rooms[i].tunnels[j].pos[t].y, win);
      }	
    }
  }

  //draw stairs
  if (in_room(map->stairs.x, map->stairs.y, r, state)) {
    draw_stairs(map->stairs.x, map->stairs.y, win);
  }
  
  // draw rogue
  draw_rogue(state->x, state->y, tunnel, win);
}

bool in_room_corners(int x, int y, int room, const state_st *state)
{
  const room_st *r = &(state->map.rooms[room]);
  return (((x == r->pos.x) && (y == r->pos.y)) || 
	  ((x == r->pos.x) && (y == r->pos.y + r->y_len-1)) || 
	  ((x == r->pos.x + r->x_len-1) && (y == r->pos.y)) || 
	  ((x == r->pos.x + r->x_len-1) && (y == r->pos.y + r->y_len-1)));
}

/* check if the specified x,y coordinates are in a given room 
 *
 * x      IN - X coordinate we are checking
 * y      IN - Y coordinate we are checking
 * room   IN - room # we are checking (element in room array in map_st)
 * state  IN - the game state
 *
 * RETURNS - bool 
 *     true if coordinate is within the room, false if not
 *     NOTE: if the coordinate falls within the walls
 *     of the room this will still return true!
 * 
 */
bool in_room(int x, int y, int room, const state_st *state)
{
  const room_st *r = &(state->map.rooms[room]);

  return (((x < (r->pos.x + r->x_len)) && (x >= r->pos.x)) && 
	  ((y < (r->pos.y + r->y_len)) && (y >= r->pos.y)));
}


/* get room # for the x, y coordinates 
 *
 * x      IN - X coordinate we are checking
 * y      IN - Y coordinate we are checking
 * state  IN - the game state
 *
 * RETURNS - int
 *     element in the room_st array that contains the x,y coordinates
 * 
 */
int get_room(int x, int y, const state_st *state)
{
  int i;
  
  for (i = 0; i < state->map.num_rooms; ++i) {
    if (in_room(x, y, i, state)) {
      return (i);
    }
  }
  
  return (-1);
}
