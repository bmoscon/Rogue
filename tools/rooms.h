/*
 * rooms.h
 *
 *
 * room algorithm
 *
 * Copyright (C) 2013-2016  Bryant Moscon - bmoscon@gmail.com
 *
 * Please see the LICENSE file for the terms and conditions 
 * associated with this software.
 *
 */

#ifndef __ROOMS__
#define __ROOMS__

#include <stdbool.h>


#define MIN_COL 80
#define MIN_ROW 24

// set map size
#define MAP_COL MIN_COL
// - 2 because we reserve top row for messages
// and bottom row for stats
#define MAP_ROW MIN_ROW - 2

// min/max # of rooms, and minimum room dimensions
#define ROOMS_MAX 9
#define ROOMS_MIN 3
#define ROOM_DIM_MIN 4

// max number of doors per room
#define MAX_DOORS 4

typedef struct coord_st {
  int x;
  int y;
} coord_st;

typedef struct door_t {
  coord_st  pos;
  bool      hidden;
} door_st;

typedef struct tunnel_st {
  int       len;
  coord_st  pos;
} tunnel_st;


typedef struct room_t {
  coord_st   pos;
  int        x_len;
  int        y_len;
  door_st    doors[MAX_DOORS];
} room_st;

typedef struct map_t {
  coord_st    stairs;
  int         num_rooms;
  int         num_tunnels;
  room_st    *rooms;
  tunnel_st  *tunnels;
} map_st;



map_st* generate_rooms();



#endif
