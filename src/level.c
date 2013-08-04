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

static void generate_rooms(state_st *state, int debug)
{
  int room_height_max;
  int room_width_max;
  int i;
  
  map_st *map = &(state->map);
  room_st *curr_room;
  FILE *fp = NULL;
  
  // randomly determine number of rooms
  map->num_rooms = (rand() % (ROOMS_MAX - ROOMS_MIN)) + ROOMS_MIN;
  map->rooms = (room_st *)malloc(sizeof(room_st) * map->num_rooms);
  if (!map->rooms) {
    endwin();
    fprintf(stderr, "%s:%d - %s() - out of memory\n", __FILE__, __LINE__, __FUNCTION__);
    free_state(state); 
    exit(EXIT_FAILURE);
  }

  if (debug == 1) {
    fp = fopen("debug.txt", "w");
  }

  if (fp) {
    fprintf(fp, "room count: %d\n", map->num_rooms);
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

 if (fp) {
   fprintf(fp, "room_max_width: %d\n", room_width_max);
   fprintf(fp, "room_max_height: %d\n", room_height_max);
  }
  
  // randomly generate dimensions for each room
  for (i = 0; i < map->num_rooms; ++i) {
    int startx;
    int starty;
    curr_room = &(map->rooms[i]);
    
    curr_room->y_len = (rand() % (room_height_max - ROOM_DIM_MIN)) + ROOM_DIM_MIN;
    curr_room->x_len = (rand() % (room_width_max - ROOM_DIM_MIN)) + ROOM_DIM_MIN;
    
    if (fp) {
      fprintf(fp, "room %d height: %d\n", i, curr_room->y_len);
      fprintf(fp, "room %d width: %d\n", i, curr_room->x_len);
    }
    
    startx = (MAP_COL / 3) * (i % 3);
    starty = room_height_max * (i / 3);

    // randomize x,y
    startx += (rand() % (room_width_max - curr_room->x_len));
    // +1 because we use the top row of the screen for text messages
    starty += (rand() % (room_height_max - curr_room->y_len)) + 1;
    
    if (fp) {
      fprintf(fp, "room %d startx: %d\n", i, startx);
      fprintf(fp, "room %d starty: %d\n", i, starty);
    }
    
    curr_room->coord.x = startx;
    curr_room->coord.y = starty;
  }
}

static void randomize_tunnels(state_st *state)
{

}


static void randomize_positions(state_st *state)
{
  map_st *m = &(state->map);
  // pick random room
  int r = (rand() % state->map.num_rooms);
  int s = (rand() % state->map.num_rooms);
  
  // pick random coords in rooms
  state->x = (rand() % (m->rooms[r].x_len - 3)) + m->rooms[r].coord.x + 1;
  state->y = (rand() % (m->rooms[r].y_len - 3)) + m->rooms[r].coord.y + 1;

  m->stairs.x = (rand() % (m->rooms[s].x_len - 3)) + m->rooms[r].coord.x + 1;
  m->stairs.y = (rand() % (m->rooms[s].y_len - 3)) + m->rooms[r].coord.y + 1;
  
}


void init_level(state_st *state)
{
  generate_rooms(state, 0);
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
    draw_room(map->rooms[i].coord.x, map->rooms[i].coord.y, map->rooms[i].y_len, 
	      map->rooms[i].x_len, (i == r), win);
    
    // draw doors on room
    for (j = 0; map->rooms->doors[j].coord.x && map->rooms->doors[j].coord.y; ++j) {
      if (!map->rooms[i].doors[j].hidden) {
	draw_door(map->rooms[i].doors[j].coord.x, map->rooms[i].doors[j].coord.y, win);
      }
    }
    
    if (r == i) {
      // draw objects in room
      for (j = 0; j < MAX_ITEMS; ++j) {
	draw_items(map->rooms[i].items[j].coord.x, map->rooms[i].items[j].coord.y, 
		   map->rooms[i].items[j].type, win);
      }
    }
  }

  // draw tunnel
  for (i = 0; i < map->num_tunnels; ++i) {
    for (j = 0; j < map->tunnels[i].len; ++j) {
      if (state->x == map->tunnels[i].coords[j].x && state->y == map->tunnels[i].coords[j].y) {
	tunnel = true;
      } 

      draw_tunnel(map->tunnels[i].coords[j].x, map->tunnels[i].coords[j].y, win);
    }
  }

  //draw stairs
  if (in_room(map->stairs.x, map->stairs.y, r, state)) {
    draw_stairs(map->stairs.x, map->stairs.y, win);
  }
  
  // draw rogue
  draw_rogue(state->x, state->y, tunnel, win);
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
 * 
 */
bool in_room(int x, int y, int room, const state_st *state)
{
  const room_st *r = &(state->map.rooms[room]);

  return (((x < (r->coord.x + r->x_len)) && (x >= r->coord.x)) && 
	  ((y < (r->coord.y + r->y_len)) && (y >= r->coord.y)));
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
