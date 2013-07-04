/*
 * main.c
 *
 *
 * entry point for rogue
 *
 *
 * Copyright (C) 2013  Bryant Moscon - bmoscon@gmail.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions, and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution, and in the same 
 *    place and form as other copyright, license and disclaimer information.
 *
 * 3. The end-user documentation included with the redistribution, if any, must 
 *    include the following acknowledgment: "This product includes software 
 *    developed by Bryant Moscon (http://www.bryantmoscon.org/)", in the same 
 *    place and form as other third-party acknowledgments. Alternately, this 
 *    acknowledgment may appear in the software itself, in the same form and 
 *    location as other such third-party acknowledgments.
 *
 * 4. Except as contained in this notice, the name of the author, Bryant Moscon,
 *    shall not be used in advertising or otherwise to promote the sale, use or 
 *    other dealings in this Software without prior written authorization from 
 *    the author.
 *
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 *
 */
#define _XOPEN_SOURCE_EXTENDED


#include <locale.h>
#include <stdlib.h>
#include <time.h>

#include "rogue.h"
#include "draw.h"
#include "windows.h"
#include "input.h"
#include "colors.h"
#include "level.h"


static void game_init(state_st *state)
{
  int i;

  // set up windows
  state->game = init_gamew();
  state->help = init_helpw();
  state->inventory = init_inventoryw();

  if (!state->game || !state->help || !state->inventory) {
    endwin();
    fprintf(stderr, "%s:%d - %s() - Failed to create window!\n", __FILE__, __LINE__, __FUNCTION__);
    free_state(state); 
    exit(EXIT_FAILURE);
  }

  if (LINES < MIN_ROW || COLS < MIN_COL) {
    endwin();
    fprintf(stderr, "Your terminal is too small. Minimum supported dimensions are %dx%d\n", 
	    MIN_COL, MIN_ROW);
    free_state(state); 
    exit(EXIT_FAILURE);
  }

  curs_set(0);

  if(has_colors() == false) {
    endwin();
    fprintf(stderr, "Your terminal does not support color\n");
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
    random_string(state->scroll_names[i], ITEM_NAME_MAX-1);
  }


  // randomize ring types
  rings_init(state);
  endwin();
  for (i = 0; i < NUM_RINGS; ++i) {
    printf("%s\n", state->ring_names[i]);
  }
  exit(0);

  state->running = true;
  init_level(state);
}

static void draw(state_st *state)
{
  draw_stats(state);
  draw_message(state);
  draw_level(state);
}

static bool running(const state_st *state)
{
  return (state->running);
}



static void welcome(state_st *state)
{
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
}

int main()
{
  state_st state = {};
  
  // set locale, otherwise we cant use unicode characters for the walls
  setlocale(LC_ALL, "");

  // seed random #
  srand(time(NULL));

  // set up game state
  game_init(&state);

  // welcome screen. get rogue's name, roll rogue
  welcome(&state);

  // game loop
  do {
    wclear(state.game);
    // draw
    draw(&state);
    
    // input
    input_handler(&state);
    
  } while(running(&state));
  
  
  
  
  
 
  endwin();
  
  free_state(&state); 
  return (EXIT_SUCCESS);
}
