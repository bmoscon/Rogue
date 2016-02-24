/*
 * colors.c
 *
 *
 * Central place for setting colors before drawing
 *
 *
 * Copyright (C) 2013-2016  Bryant Moscon - bmoscon@gmail.com
 * 
 * Please see the LICENSE file for the terms and conditions 
 * associated with this software.
 *
 */

#define _XOPEN_SOURCE_EXTENDED

#ifdef __APPLE__
#include <ncurses.h>
#elif __linux__
#include <ncursesw/curses.h> 
#endif


#include "colors.h"
#include "logger.h"

void init_colors()
{
    log_func_enter;
    
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_BLACK, COLOR_WHITE);
    init_pair(7, COLOR_RED, COLOR_BLACK);
    init_pair(8, COLOR_CYAN, COLOR_BLACK);
    init_pair(9, COLOR_BLUE, COLOR_BLACK);
    
    log_func_exit;
}

inline void color_wall()
{
    attrset(COLOR_PAIR(1));
}


inline void color_floor()
{
    attrset(COLOR_PAIR(2));
}

inline void color_text()
{
    attrset(COLOR_PAIR(3) | A_BOLD);
}

inline void color_title()
{
    attrset(COLOR_PAIR(6));
}

inline void color_copyright()
{
    attrset(COLOR_PAIR(5) | A_BOLD);
}

inline void color_tunnel()
{
    attrset(COLOR_PAIR(3));
}

inline void color_rogue()
{
    attrset(COLOR_PAIR(1) | A_BOLD);
}

inline void color_rogue_tunnel()
{
    attrset(COLOR_PAIR(6));
}

inline void color_stairs()
{
    attrset(COLOR_PAIR(4) | A_BOLD);
}


inline void color_gold()
{
    attrset(COLOR_PAIR(1) | A_BOLD);
}


inline void color_food()
{
    attrset(COLOR_PAIR(7));
}


inline void color_monster()
{
    attrset(COLOR_PAIR(8) | A_BOLD);
}


inline void color_item()
{
    attrset(COLOR_PAIR(9) | A_BOLD);
}


inline void color_trap()
{
    attrset(COLOR_PAIR(5) | A_BOLD);
}
