/*
 * rooms.c
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
	free(m);
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
