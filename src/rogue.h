/*
 * rogue.h
 *
 *
 * definitions for the game
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
#ifndef __ROGUE__
#define __ROGUE__


#include <ncursesw/curses.h>
#include <stdbool.h>
#include <stdint.h>

#include "chars.h"


#define MIN_COL 80
#define MIN_ROW 24

// set map size
#define MAP_COL MIN_COL
// - 2 because we reserve top row for messages
// and bottom row for stats
#define MAP_ROW MIN_ROW - 2

// max number of doors per room
#define MAX_DOORS 4

// max items per room
#define MAX_ITEMS 5


typedef enum {
  I_NONE = 0,
  I_GOLD = GOLD,
  I_SCROLL = SCROLL,
  I_POTION = POTION,
  I_WEAPON = WEAPON,
  I_ARMOR = ARMOR,
  I_RING = RING,
  I_FOOD = FOOD,
  I_WAND = WAND,
  I_TRAP = TRAP,
  I_AMULET = AMULET
} items_e;


typedef struct coord_st {
  int x;
  int y;
} coord_st;


typedef struct item_st {
  coord_st coord;
  items_e type;
} item_st;


typedef struct door_t {
  coord_st coord;
  bool hidden;
} door_st;

typedef struct room_t {
  coord_st coord;
  int x_len;
  int y_len;
  door_st doors[MAX_DOORS];
  item_st items[MAX_ITEMS];
} room_st;

typedef struct tunnel_st {
  int len;
  coord_st *coords;
} tunnel_st;


typedef struct map_t {
  coord_st stairs;
  int num_rooms;
  int num_tunnels;
  room_st *rooms;
  tunnel_st *tunnels;
} map_st;


// Game State
typedef struct state_st {
  WINDOW *game;
  WINDOW *help;
  WINDOW *inventory;

  bool running;

  // current game message
  char message[MIN_COL]; 
  
  // rogue's name
  char *name;

  // stats
  uint32_t hp;
  uint32_t hp_max;
  uint32_t str;
  uint32_t str_max;
  uint32_t armor;
  
  uint32_t gold;
  uint32_t level;
  uint32_t rank;
  uint32_t food;
  
  // rogue map position
  int x;
  int y;
  
  map_st map;
} state_st;




void free_state(state_st *state);

void roll_rogue(state_st *state);


#endif

