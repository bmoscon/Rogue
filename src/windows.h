/*
 * windows.h
 *
 *
 * init ncurses windows for rogue
 *
 *
 * Copyright (C) 2013-2016  Bryant Moscon - bmoscon@gmail.com
 * 
 * Please see the LICENSE file for the terms and conditions 
 * associated with this software.
 *
 */

#ifndef __ROGUE_WINDOWS__
#define __ROGUE_WINDOWS__


#ifdef __APPLE__
#include <ncurses.h>
#elif __linux__
#include <ncursesw/curses.h> 
#endif

#include <stdlib.h>


WINDOW* init_gamew();

WINDOW* init_helpw();

WINDOW* init_inventoryw();

int switch_win(WINDOW *win);



#endif

