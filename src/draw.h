/*
 * draw.h
 *
 *
 * draw routines
 *
 *
 * Copyright (C) 2013-2016  Bryant Moscon - bmoscon@gmail.com
 * 
 * Please see the LICENSE file for the terms and conditions 
 * associated with this software.
 *
 */

#ifndef __ROGUE_DRAW__
#define __ROGUE_DRAW__


#include "rogue.h"


void draw_box(int, int, int, int, WINDOW*);

void draw_room(int, int, int, int, bool, WINDOW*);

void draw_welcome_box(WINDOW*);

void draw_stats(const state_st *state);

void draw_message(state_st *state);

void draw_door(int, int, WINDOW*);

void draw_tunnel(int, int, WINDOW*);

void draw_rogue(int, int, bool, WINDOW*);

void draw_stairs(int, int, WINDOW*);

void draw_items(int, int, items_e, WINDOW*);

#endif
