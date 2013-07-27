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

#define WIDTH 80
#define HEIGHT 22
#define ROOMS_MAX 9
#define ROOMS_MIN 3
#define ROOM_DIM_MIN 4


room_st* generate_rooms(int debug)
{
  int room_count;
  int room_height_max;
  int room_width_max;
  int i;
  
  room_st *rooms;
  room_st *curr_room;
  FILE *fp = NULL;
  
  // randomly determine number of rooms
  room_count = (rand() % (ROOMS_MAX - ROOMS_MIN)) + ROOMS_MIN;
  rooms = (room_st *)malloc(sizeof(room_st));
  // check for bad malloc


  if (debug == 1) {
    fp = fopen("debug.txt", "w");
  }

  if (fp) {
    fprintf(fp, "room count: %d\n", room_count);
  }
  

  curr_room = rooms;
  for (i = 1; i < room_count; ++i) {
    rooms->next = malloc(sizeof(room_st));
    rooms = rooms->next;
    rooms->next = NULL;
  }
  
  rooms = curr_room;
  
  // determine max room dimensions
  room_width_max = (WIDTH / 3);
  if (room_count == 3) {
    room_height_max = 22;
  } else if (room_count <= 6) {
    room_height_max = 11;
  } else {
    room_height_max = 7;
  }

 if (fp) {
   fprintf(fp, "room_max_width: %d\n", room_width_max);
   fprintf(fp, "room_max_height: %d\n", room_height_max);
  }
  
  // randomly generate dimensions for each room
  for (i = 0; i < room_count; ++i) {
    int startx;
    int starty;
    
    
    curr_room->h = (rand() % (room_height_max - ROOM_DIM_MIN)) + ROOM_DIM_MIN;
    curr_room->w = (rand() % (room_width_max - ROOM_DIM_MIN)) + ROOM_DIM_MIN;
      
    if (fp) {
      fprintf(fp, "room %d height: %d\n", i, curr_room->h);
      fprintf(fp, "room %d width: %d\n", i, curr_room->w);
    }
  
    startx = (WIDTH / 3) * (i % 3);
    starty = room_height_max * (i / 3);
    
    if (fp) {
      fprintf(fp, "room %d startx: %d\n", i, startx);
      fprintf(fp, "room %d starty: %d\n", i, starty);
    }
    
    curr_room->x = startx;
    curr_room->y = starty;

    curr_room = curr_room->next;
  }
  
  return (rooms);
}
