/*
 * draw.c
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

#define _XOPEN_SOURCE_EXTENDED


#include <string.h>

#include "draw.h"
#include "colors.h"
#include "chars.h"
#include "logger.h"


static void center_text(int row, const char *text, WINDOW *win)
{
    log_func_enter;
    
    int indent;
    
    indent = COLS - strlen(text);
    indent /= 2;
    
    mvwaddstr(win, row, indent, text);
    
    log_func_exit;
}

static void horiz_line(int x, int y, int len, WINDOW *win)
{
    log_func_enter;
    
    int i;
    
    wmove(win, y, x);
    
    for(i = 0; i < len; ++i) {
	waddstr(win, HORIZU);
    } 
    
    log_func_exit;
}

static void vert_line(int x, int y, int len, WINDOW *win)
{
    log_func_enter;
    
    int i;
    
    for (i = 0; i < len; ++i) {
	wmove(win, y+i, x);
	waddstr(win, VERTU);
    }
    
    log_func_exit;
}

void draw_box(int startx, int starty, int rows, int cols, WINDOW* win)
{
    log_func_enter;
    
    color_wall();
    wmove(win, starty, startx);
    
    waddstr(win, TLCORNERU);
    horiz_line(startx+1, starty, cols-2, win);
    waddstr(win, TRCORNERU);
    
    
    vert_line(startx, starty+1, rows-2, win);
    vert_line(startx+cols-1, starty+1, rows-2, win);
    
    
    wmove(win, starty+rows-1, startx);  
    waddstr(win, BLCORNERU);
    horiz_line(startx+1, starty+rows-1, cols-2, win);
    waddstr(win, BRCORNERU);
    
    log_func_exit;
}


void draw_room(int startx, int starty, int rows, int cols, bool floor, WINDOW* win)
{
    log_func_enter;
    
    int i, j;
    // dark room? if so, don't draw anything except in the coordinates
    // directly next to the hero
    
    
    // first draw the box
    draw_box(startx, starty, rows, cols, win);
    
    if (floor) {
	color_floor();
	// now fill the background
	for (i = 1; i < rows - 1; ++i) {
	    for (j = 1; j < cols - 1; ++j) {
		wmove(win, starty + i, startx + j);
		waddstr(win, FLOORU);
	    }
	}
    }
    
    log_func_exit;
}


void draw_welcome_box(WINDOW *win)
{
    log_func_enter;
    
    color_wall();
    
    wmove(win, 0, 0);
    
    // top line (+ corners)
    waddstr(win, TLCORNERU);
    horiz_line(1, 0, COLS-2, win);
    waddstr(win, TRCORNERU);
    
    //sides
    vert_line(0, 1, LINES-3, win);
    vert_line(COLS-1, 1, LINES-3, win);
    
    wmove(win, LINES-3, 0);
    
    // draw left vertial with horizontal intersect
    waddstr(win, LTEEU);
    wmove(win, LINES-3, COLS-1);
    waddstr(win, RTEEU);
    horiz_line(1, LINES-3, COLS-2, win);
    vert_line(0, LINES-2, 1, win);
    vert_line(COLS-1, LINES-2, 1, win);
    
    // bottom line
    wmove(win, LINES-1, 0);
    waddstr(win, BLCORNERU);
    horiz_line(1, LINES-1, COLS-2, win);
    waddstr(win, BRCORNERU);
    
    //print out the title
    color_title();
    center_text(3, "Rogue: The Dungeons of Doom", win);
    
    // copyright
    color_copyright();
    center_text(LINES-6, "Copyright (C) 2013 - 2016", win);
    center_text(LINES-5, "Bryant Moscon", win);
    center_text(LINES-4, "All Rights Reserved", win);
    
    wmove(win, LINES-2, 1);
    color_text();
    waddstr(win, "Rogue's Name: ");
    
    log_func_exit;
}


void draw_stats(const state_st *state)
{
    log_func_enter;
    
    color_text();
    wmove(state->game, LINES-1, 0);
    wprintw(state->game, "Level:%d", state->level);
    
    wmove(state->game, LINES-1, 10);
    wprintw(state->game, "Hits:%d(%d)", state->hp, state->hp_max);
    
    wmove(state->game, LINES-1, 26);
    wprintw(state->game, "Str:%d(%d)", state->str, state->str_max);
    
    wmove(state->game, LINES-1, 40);
    wprintw(state->game, "Gold:%d", state->gold);
    
    wmove(state->game, LINES-1, 51);
    wprintw(state->game, "Armor:%d", state->armor);
    
    wmove(state->game, LINES-1, 64);
    switch(state->rank) {
    case 1:
	waddstr(state->game, "Initiate");
	break;
    case 2:
	waddstr(state->game, "Apprentice");
	break;
    default:
	break;
    }
    
    log_func_exit;
}

void draw_message(state_st *state)
{
    log_func_enter;
    
    int i;
    
    color_text();
    
    wmove(state->game, 0, 0);
    if (state->message[0] == 0) {
	for (i = 0; i < COLS; ++i) {
	    waddstr(state->game, " ");
	}
    } else {
	waddstr(state->game, state->message);
    }
    
    memset(state->message, 0, sizeof(state->message));
    
    log_func_exit;
}


void draw_door(int x, int y, WINDOW *win)
{
    log_func_enter;
    
    color_wall();
    wmove(win, y, x);
    waddstr(win, DOORU);
    
    log_func_exit;
}


void draw_tunnel(int x, int y, WINDOW *win)
{
    log_func_enter;
    
    color_tunnel();
    wmove(win, y, x);
    waddstr(win, TUNNELU);
    
    log_func_exit;
}


void draw_rogue(int x, int y, bool tunnel, WINDOW *win)
{
    log_func_enter;
  
    if (tunnel) {
	color_rogue_tunnel();
    } else {
	color_rogue();
    }
    
    wmove(win, y, x);
    waddstr(win, ROGUEU);
    
    log_func_exit;
}


void draw_stairs(int x, int y, WINDOW *win)
{
    log_func_enter;
    
    color_stairs();
    wmove(win, y, x);
    waddstr(win, STAIRSU);

    log_func_exit;
}


void draw_items(int x, int y, items_e item, WINDOW *win)
{
    log_func_enter;
  
    wmove(win, y, x);
    color_item();

    switch(item) {
    case I_GOLD:
	color_gold();
	waddstr(win, GOLDU);
	break;
    case I_SCROLL:
	waddstr(win, SCROLLU);
	break;
    case I_POTION:
	waddstr(win, POTIONU);
	break;
    case I_FOOD:
	color_food();
	waddstr(win, FOODU);
	break;
    case I_ARMOR:
	waddstr(win, ARMORU);
	break;
    case I_AMULET:
	waddstr(win, AMULETU);
	break;
    case I_TRAP:
	color_trap();
	waddstr(win, TRAPU);
	break;
    case I_RING:
	waddstr(win, RINGU);
	break;
    case I_WAND:
	waddstr(win, WANDU);
	break;
    case I_WEAPON:
	waddstr(win, WEAPONU);
	break;
    default:
	break;
    }
    
    log_func_exit;
}
