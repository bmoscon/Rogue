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


void init_level(state_st *state)
{
  state->map.num_rooms = 1;
  state->map.rooms = malloc(sizeof(room_st));
  state->map.rooms->x = 0;
  state->map.rooms->y = 1;
  state->map.rooms->x_len = 5;
  state->map.rooms->y_len = 5;
  state->map.rooms->num_doors = 2;
  state->map.rooms->doors[0].x = 2;
  state->map.rooms->doors[0].y = 5;
  state->map.rooms->doors[0].hidden = false;
  state->map.rooms->doors[1].x = 4;
  state->map.rooms->doors[1].y = 2;
  state->map.rooms->doors[1].hidden = false;
  state->x = 1;
  state->y = 3;

  state->map.num_tunnels = 1;
  state->map.tunnels = malloc(sizeof(tunnel_st));
  state->map.tunnels->coords = malloc(sizeof(coord_st) * 5);
  state->map.tunnels->len = 5;
  state->map.tunnels->coords[0].x = 5;
  state->map.tunnels->coords[0].y = 2;
  state->map.tunnels->coords[1].x = 6;
  state->map.tunnels->coords[1].y = 2;
  state->map.tunnels->coords[2].x = 7;
  state->map.tunnels->coords[2].y = 2;
  state->map.tunnels->coords[3].x = 8;
  state->map.tunnels->coords[3].y = 2;
  state->map.tunnels->coords[4].x = 9;
  state->map.tunnels->coords[4].y = 2; 
}

void draw_level(state_st *state)
{
  int i;
  int j;
  bool tunnel = false;
  WINDOW *win = state->game;
  map_st *map = &(state->map);

  for (i = 0; i < map->num_rooms; ++i) {
    if (!map->rooms->doors[i].hidden) {
      draw_room(map->rooms[i].x, map->rooms[i].y, map->rooms[i].x_len, map->rooms[i].y_len, win);
      
      for (j = 0; j < map->rooms->num_doors; ++j) {
	if (!map->rooms[i].doors[j].hidden) {
	  draw_door(map->rooms[i].doors[j].x, map->rooms[i].doors[j].y, win);
	}
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
  
  // draw rogue
  draw_rogue(state->x, state->y, tunnel, win);
}
