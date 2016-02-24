/*
 * level.h
 *
 *
 * Level functions
 *
 *
 * Copyright (C) 2013-2016  Bryant Moscon - bmoscon@gmail.com
 * 
 * Please see the LICENSE file for the terms and conditions 
 * associated with this software.
 *
 */

#ifndef __ROGUE_LEVEL__
#define __ROGUE_LEVEL__


#include "rogue.h"


void init_level(state_st *state);

void draw_level(const state_st *state);

bool in_room_corners(int x, int y, int room, const state_st *state);

bool in_room(int x, int y, int room, const state_st *state);

int get_room(int x, int y, const state_st *state);


#endif
