/*
 * main.c
 *
 *
 * entry point for rogue
 *
 *
 * Copyright (C) 2013-2016  Bryant Moscon - bmoscon@gmail.com
 * 
 * Please see the LICENSE file for the terms and conditions 
 * associated with this software.
 *
 */ 

#define _XOPEN_SOURCE_EXTENDED


#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "rogue.h"
#include "draw.h"
#include "windows.h"
#include "input.h"
#include "colors.h"
#include "level.h"
#include "logger.h"



static void game_init(state_st *state)
{
    log_func_enter;

    int i;

    // set up windows
    state->game = init_gamew();
    state->help = init_helpw();
    state->inventory = init_inventoryw();

    if (!state->game || !state->help || !state->inventory) {
	endwin();
	fprintf(stderr, "%s:%d - %s() - Failed to create window!\n", __FILE__, __LINE__, __func__);
	log_error("Window creation failed, aborting");
	logger_stop();
	free_state(state); 
	exit(EXIT_FAILURE);
    }

    if (LINES < MIN_ROW || COLS < MIN_COL) {
	endwin();
	fprintf(stderr, "Your terminal is too small. Minimum supported dimensions are %dx%d\n", 
		MIN_COL, MIN_ROW);
	log_error("Terminal size too small, aborting");
	logger_stop();
	free_state(state); 
	exit(EXIT_FAILURE);
    }

    curs_set(0);

    if(has_colors() == false) {
	endwin();
	fprintf(stderr, "Your terminal does not support color\n");
	log_error("Terminal colors not supported, aborting");
	logger_stop();
	free_state(state); 
	exit(EXIT_FAILURE);
    }
    start_color();
    init_colors();
  
    // allow us to catch the arrow keys
    keypad(state->game, TRUE);

    // generate random names for items
    for (i = 0; i < NUM_SCROLLS; ++i) {
	state->scroll_names[i] = calloc(ITEM_NAME_MAX, sizeof(char));
	if (!state->scroll_names[i]) {
	    endwin();
	    fprintf(stderr, "%s:%d - %s() - out of memory\n", __FILE__, __LINE__, __func__);
	    log_error("malloc failed");
	    logger_stop();
	    free_state(state); 
	    exit(EXIT_FAILURE);
	}
    
	random_string(state->scroll_names[i], ITEM_NAME_MAX-1);
    }

    // randomize ring types
    rings_init(state);

    // randomize potion names
    potions_init(state);

    // randomize wand names
    wands_init(state);

    state->running = true;
    init_level(state);

    log_func_exit;
}

static void draw(state_st *state)
{
    log_func_enter;

    draw_stats(state);
    draw_message(state);
    draw_level(state);

    log_func_exit;
}


static void welcome(state_st *state)
{
    log_func_enter;
  
    draw_welcome_box(state->game);
    refresh();
    name_handler(state);
    //once we are done getting rogue's name, turn off echo
    noecho();
  
    //roll rogue
    roll_rogue(state);
  
    // clear the screen
    wclear(state->game);
  
    // add welcome message to first level screen
    snprintf(state->message, sizeof(state->message), "Hello %s. Welcome to the Dungeons of Doom!", 
	     state->name);

    log_func_exit;
}

int main(int argc, char* argv[])
{
    state_st state = {0};
  
    // set locale, otherwise we cant use unicode characters for the walls
    setlocale(LC_ALL, "");

    // seed random #
    srand(time(NULL));

    // check for logging
    if (argc > 1) {
	if (!strcmp(argv[1], "--debug")) {
	    logger_set_level(LOGGER_LEVEL_DEBUG);
	} else if (!strcmp(argv[1], "--verbose")) {
	    logger_set_level(LOGGER_LEVEL_VERBOSE);
	} else if (!strcmp(argv[1], "--warn")) {
	    logger_set_level(LOGGER_LEVEL_WARN);
	} else if (!strcmp(argv[1], "--error")) {
	    logger_set_level(LOGGER_LEVEL_ERROR);
	}
    }

    // set up logger. If no level has been set this call will do nothing. 
    logger_init();
    
    // set up game state
    game_init(&state);

    // welcome screen. get rogue's name, roll rogue
    welcome(&state);

    // game loop
    do {
	// clear game window
	wclear(state.game);
	// draw
	draw(&state);
    
	// input
	input_handler(&state);
    
    } while(state.running);
 
    endwin();
  
    free_state(&state);
    logger_stop();
    return (EXIT_SUCCESS);
}
