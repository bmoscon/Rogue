/*
 * rogue.c
 *
 *
 * definitions for the game
 *
 *
 * Copyright (C) 2013-2016  Bryant Moscon - bmoscon@gmail.com
 * 
 * Please see the LICENSE file for the terms and conditions 
 * associated with this software.
 *
 */

#define _XOPEN_SOURCE_EXTENDED


#include <stdlib.h>
#include <string.h>

#include "rogue.h"
#include "logger.h"
#include "tools.h"

// strdup is not in c99 standard, so simply including <string.h> will not suffice
extern char *strdup(const char *s);

char *ring_types[] = {"topaz",
                      "diamond",
                      "agate",
                      "onyx",
                      "emerald",
                      "ruby",
                      "saphire",
                      "turquoise",
                      "opal",
                      "jade",
                      "saphire",
                      "amethyst"};

char *potion_types[] = {"black",
			"crimson",
			"amber",
			"aquamarine",
			"cyan",
			"magenta",
			"green",
			"gold",
			"silver",
			"tan",
			"tangerine",
			"clear",
                        "white",
                        "yellow"};

char *wand_types[] = {"birch",
		      "oak",
		      "elm",
		      "ash",
		      "cherry",
		      "willow",
		      "hemlock",
		      "maple",
		      "cedar",
		      "poplar",
		      "teak",
		      "walnut",
		      "redwood"};


void free_state(state_st *state)
{
    int i;
    
    if (state->name) {
	free(state->name);
    }
    
    for (i = 0; i < state->map.num_rooms; ++i) {
	for (int j = 0; j < MAX_DOORS; ++j) {
	    if (state->map.rooms[i].tunnels[j].pos) {
		free(state->map.rooms[i].tunnels[j].pos);
	    }
	}				      
    }
    
    if (state->map.rooms) {
	free(state->map.rooms);
    }
    
    
    // clean up scrolls names
    for (i = 0; i < NUM_SCROLLS; ++i) {
	if (state->scroll_names[i]) {
	    free(state->scroll_names[i]);
	}
    }
    
    // clean up ring names
    for (i = 0; i < NUM_RINGS; ++i) {
	if (state->ring_names[i]) {
	    free(state->ring_names[i]);
	}
    }
    
    // clean up potion names
    for (i = 0; i < NUM_POTIONS; ++i) {
	if (state->potion_names[i]) {
	    free(state->potion_names[i]);
	}
    }
    
    // clean up wand names
    for (i = 0; i < NUM_WANDS; ++i) {
	if (state->wand_names[i]) {
	    free(state->wand_names[i]);
	}
    }
    
}


void roll_rogue(state_st *state)
{ 
    log_func_enter;
    
    // strength should be between 9 and 12
    state->str_max = 9 + (rand() % 3);
    state->str = state->str_max;
    
    // hp should be between 10 and 15
    state->hp_max = 10 + (rand() % 5);
    state->hp = state->hp_max;
    
    // set up default inventory items and equip wep + armor
    // items should be food, 5 armor item, +0,+0 mace, 10 arrows
    state->armor = 5;
    
    // init other values
    state->gold = 0;
    state->level = 1;
    state->rank = 1;
    
    log_func_exit;
}

void rings_init(state_st *state)
{
    log_func_enter;
    
    int i;
    int indices[NUM_RINGS];
    
    for (i = 0; i < NUM_RINGS; ++i) {
	indices[i] = i;
    }
    
    random_shuffle(indices, NUM_RINGS);
    
    for (i = 0; i < NUM_RINGS; ++i) {
	state->ring_names[i] = strdup(ring_types[indices[i]]);
	if (!state->ring_names[i]) {
	    endwin();
	    fprintf(stderr, "%s:%d - %s() - out of memory\n", __FILE__, __LINE__, __func__);
	    free_state(state); 
	    exit(EXIT_FAILURE);
	}
    }
    
    log_func_exit;
}


void potions_init(state_st *state)
{
    log_func_enter;
    
    int i;
    int indices[NUM_POTIONS];
    
    for (i = 0; i < NUM_POTIONS; ++i) {
	indices[i] = i;
    }
    
    random_shuffle(indices, NUM_POTIONS);
    
    for (i = 0; i < NUM_POTIONS; ++i) {
	state->potion_names[i] = strdup(potion_types[indices[i]]);
	if (!state->potion_names[i]) {
	    endwin();
	    fprintf(stderr, "%s:%d - %s() - out of memory\n", __FILE__, __LINE__, __func__);
	    free_state(state); 
	    exit(EXIT_FAILURE);
	}
    }
    
    log_func_exit;
}


void wands_init(state_st *state)
{
    log_func_enter;
    
    int i;
    int indices[NUM_WANDS];
  
    for (i = 0; i < NUM_WANDS; ++i) {
	indices[i] = i;
    }
    
    random_shuffle(indices, NUM_WANDS);
    
    for (i = 0; i < NUM_WANDS; ++i) {
	state->wand_names[i] = strdup(wand_types[indices[i]]);
	if (!state->wand_names[i]) {
	    endwin();
	    fprintf(stderr, "%s:%d - %s() - out of memory\n", __FILE__, __LINE__, __func__);
	    free_state(state); 
	    exit(EXIT_FAILURE);
	}
    }
    
    log_func_exit;
}


void state_log(const state_st *state)
{
    log_func_enter;
    
    log_debug("Current game state:\n"
	      "\trunning: %s\n"
	      "\tmessage: %s\n"
	      "\tname: %s\n"
	      "\thp: %d\n"
	      "\thp_max: %d\n"
	      "\tstr: %d\n"
	      "\tstr_max: %d\n"
	      "\tarmor: %d\n"
	      "\tgold: %d\n"
	      "\tlevel: %d\n"
	      "\trank: %d\n"
	      "\tfood: %d\n"
	      "\tx: %d\n"
	      "\ty: %d",
	      (state->running) ? "yes" : "no", state->message, state->name, state->hp, 
	      state->hp_max, state->str, state->str_max, state->armor, state->gold, state->level,
	      state->rank, state->food, state->x, state->y);
    
    log_func_exit;
}
