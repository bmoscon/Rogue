/*
 * input.c
 *
 *
 * input handlers
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

#include "input.h"
#include "colors.h"
#include "windows.h"
#include "chars.h"
#include "items.h"
#include "level.h"
#include "logger.h"


// strdup is not in c99 standard, so simply including <string.h> will not suffice
extern char *strdup(const char *s);

static void quit_handler(state_st *state)
{
    log_func_enter;
    
    int i;

    // clear text area
    wmove(state->game, LINES-1, 0);
    for (i = 0; i < COLS; ++i) {
	wdelch(state->game);
    }
    refresh();
  
    // set color
    color_text();
    waddstr(state->game, "Are you sure you want to quit (y/n)?");
  
    i = getch();
  
    if (i == 'y') {
	state->running = false;
    } else {
	// replace with old text (i.e. stats)
	wmove(state->game, LINES-1, 0);
	for (i = 0; i < COLS; ++i) {
	    wdelch(state->game);
	}
	wrefresh(state->game);
    }

    log_func_exit;
}

static void help_handler(state_st *state)
{
    log_func_enter;

    if (switch_win(state->help) != 0) {
	endwin();
	logger_stop();
	free_state(state);
	exit(EXIT_FAILURE);
    }

    getch();
  
    if (switch_win(state->game) != 0) {
	endwin();
	logger_stop();
	free_state(state);
	exit(EXIT_FAILURE);
    }
  
    log_func_exit;
}


static void item_handler(state_st *state, items_e item)
{
    log_func_enter;
    
    uint32_t gold;
    int room;
  
    switch(item) {
    case I_GOLD:
	gold = 1 + (rand() % 25) + (state->level * rand() % 10);
	snprintf(state->message, sizeof(state->message), "You found %d gold", gold);
	state->gold += gold;
	break;
    case I_FOOD:
	state->food++;
	snprintf(state->message, sizeof(state->message), "You found some food.");
	break;
    case I_TRAP:
	break;
      
    default:
	break;
    }


    room = get_room(state->x, state->y, state);
    remove_item(state, room, item);

    log_func_exit;
}


// x and y indicate in what direction we are moving. 
static void move_handler(state_st *state, int x, int y)
{
    log_func_enter;
  
    cchar_t c;
  
    x += state->x;
    y += state->y;

    // get character from the screen
    // this is the character we want to move on to
    mvwin_wch(state->game, y, x, &c);

    // check what character it is. is it a legal move?
    if (c.chars[0] != FLOOR && c.chars[0] != TUNNEL && 
	c.chars[0] != DOOR && c.chars[0] != STAIRS &&
	c.chars[0] != GOLD && c.chars[0] != SCROLL &&
	c.chars[0] != POTION && c.chars[0] != FOOD &&
	c.chars[0] != ARMOR && c.chars[0] != AMULET &&
	c.chars[0] != TRAP && c.chars[0] != RING &&
	c.chars[0] != WAND && c.chars[0] != WEAPON) {
	log_func_exit;
	return;
    }
  
    // we are allowing the move, update rogue position
    state->x = x;
    state->y = y;

    // moving over an item? if so, collect it and remove it from the level
    if (c.chars[0] != FLOOR && c.chars[0] != TUNNEL && c.chars[0] != DOOR && c.chars[0] != STAIRS) {
	item_handler(state, c.chars[0]);
    }

    log_func_exit;
}

static void downstairs_handler(state_st *state)
{
    log_func_enter;
    
    // next level
    log_func_exit;
}


static void upstairs_handler(state_st *state)
{
    log_func_enter

    snprintf(state->message, sizeof(state->message), "The way is magically blocked");

    log_func_exit;
}


static void inventory_handler(state_st *state)
{
    log_func_enter
    int i;
  
    // clear previous entries on screen
    wmove(state->inventory, 1, 0);
    wclrtobot(state->inventory);

    // populate inventory screen.
    // food is always first
    wmove(state->inventory, 2, 0);
    if (state->food) {
	if (state->food == 1) {
	    waddstr(state->inventory, "Some food\n");
	} else {
	    wprintw(state->inventory, "%d pieces of food\n", state->food); 
	}
    }
    // everything else
    for (i = 0; i < INVENTORY_MAX; ++i) {
	if (state->inv[i].type == I_NONE) {
	    continue;
	} else {
	    wprintw(state->inventory, "%s\n", state->inv[i].name);
	}
    }
  

    // switch
    if (switch_win(state->inventory) != 0) {
	endwin();
	logger_stop();
	free_state(state);
	exit(EXIT_FAILURE);
    }
  
    getch();
  
    if (switch_win(state->game) != 0) {
	endwin();
	logger_stop();
	free_state(state);
	exit(EXIT_FAILURE);
    }

    log_func_exit;
}

void input_handler(state_st *state)
{
    log_func_enter;
    
    int input;

    if (!state) {
	endwin();
	fprintf(stderr, "%s:%d - %s() - NULL game state\n", __FILE__, __LINE__, __func__);
	log_error("NULL game state");
	logger_stop();
	free_state(state);
	exit(EXIT_FAILURE);
    }

    // even though ncurses has a getchw version (and we are using more than just stdscr), 
    // ncurses only has one input buffer, not one per window, so no need to use the
    // window specific function
    input = getch();
      

    switch(input) {
    case 'q':
	quit_handler(state);
	break;
    case 'h':
	help_handler(state);
	break;
    case '>':
	downstairs_handler(state);
	break;
    case '<':
	upstairs_handler(state);
	break;
    case KEY_DOWN:
	move_handler(state, 0, 1);
	break;
    case KEY_UP:
	move_handler(state, 0, -1);
	break;
    case KEY_RIGHT:
	move_handler(state, 1, 0);
	break;
    case KEY_LEFT:
	move_handler(state, -1, 0);
	break;
    case 'i':
	inventory_handler(state);
	break;
    default:
	break;
     
    }

    log_func_exit;
}


void name_handler(state_st *state)
{
    log_func_enter;
    
    char input[64];
  
    wgetnstr(state->game, input, sizeof(input));

    state->name = strdup(input);
    if (!state->name) {
	endwin();
	fprintf(stderr, "%s:%d - %s() - out of memory\n", __FILE__, __LINE__, __func__);
	log_error("malloc failed");
	logger_stop();
	free_state(state); 
	exit(EXIT_FAILURE);
    }

    log_func_exit;
}
