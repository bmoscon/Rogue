/*
 * windows.c
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

#define _XOPEN_SOURCE_EXTENDED


#include "windows.h"
#include "logger.h"


WINDOW* init_gamew()
{
    log_func_enter;
    
    // main game window doesn't require any default
    // stuff drawn, so just return the window
    
    log_func_exit;
    return (initscr());
}


WINDOW* init_helpw()
{
    log_func_enter;
    
    // need to draw the help menu onto the window. Each time we want to display it, we can just
    // touch the window and refresh.
    
    WINDOW *help = newwin(0,0,0,0);
    if (!help) {
	log_func_exit;
	return (NULL);
    }
    
    // create help menu
    mvwaddstr(help, 0, 0, "Rogue Help Menu");
    mvwaddstr(help, 2, 0, "h: this menu");
    mvwaddstr(help, 3, 0, "i: inventory");
    mvwaddstr(help, 4, 0, "q: quit");
    
    log_func_exit;
    return (help);
}


WINDOW* init_inventoryw()
{ 
    log_func_enter;
    
    WINDOW *inv = newwin(0,0,0,0);
    if (!inv) {
	log_func_exit;
	return (NULL);
    }
    
    mvwaddstr(inv, 0, 0, "Rogue Inventory");
    
    log_func_exit;
    return (inv);
}


int switch_win(WINDOW *win)
{
    log_func_enter;
    
    if (!win) {
	fprintf(stderr, "%s:%d - %s() - NULL window\n", __FILE__, __LINE__, __func__);
	log_error("NULL window");
	log_func_exit;
	return (-1);
    }
    
    touchwin(win);
    wrefresh(win);
    
    log_func_exit;
    return (0);
}
