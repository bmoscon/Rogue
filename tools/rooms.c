/*
 * rooms.c
 *
 *
 * room algorithm
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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "rooms.h"



map_st* generate_rooms()
{
  int room_height_max;
  int room_width_max;
  int i;
  
  map_st *m = malloc(sizeof(map_st));
  if (!m) {
    return (NULL);
  }
  
  // randomly determine number of rooms
  m->num_rooms = (rand() % (ROOMS_MAX - ROOMS_MIN)) + ROOMS_MIN;
  m->rooms = (room_st *)malloc(sizeof(room_st) * m->num_rooms);
  if (!m->rooms) {
    return (NULL);
  }
  
  // determine max room dimensions
  room_width_max = (MAP_COL / 3);
  if (m->num_rooms == 3) {
    room_height_max = MAP_ROW;
  } else if (m->num_rooms <= 6) {
    room_height_max = 11;
  } else {
    room_height_max = 7;
  }
  
  // randomly generate dimensions for each room
  for (i = 0; i < m->num_rooms; ++i) {
    int startx;
    int starty;
    
    m->rooms[i].y_len = (rand() % (room_height_max - ROOM_DIM_MIN)) + ROOM_DIM_MIN;
    m->rooms[i].x_len = (rand() % (room_width_max - ROOM_DIM_MIN)) + ROOM_DIM_MIN;
  
    startx = (MAP_COL / 3) * (i % 3);
    starty = room_height_max * (i / 3);

    // randomize x,y
    startx += (rand() % (room_width_max - m->rooms[i].x_len));
    starty += (rand() % (room_height_max - m->rooms[i].y_len));
    
    m->rooms[i].pos.x = startx;
    m->rooms[i].pos.y = starty;
  }
    
  return (m);
}
