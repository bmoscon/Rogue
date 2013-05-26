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


#include <locale.h>
#include <stdlib.h>


#include "rogue.h"
#include "draw.h"
#include "windows.h"
#include "input.h"
#include "colors.h"


static void game_init(state_st *state)
{
  // set up windows
  state->game = init_gamew();
  if (!state->game) {
    endwin();
    fprintf(stderr, "%s:%d - %s() - Failed to create window!\n", __FILE__, __LINE__, __FUNCTION__);
    exit(EXIT_FAILURE);
  }
      
  state->help = init_helpw();
  if (!state->help) {
    endwin();
    fprintf(stderr, "%s:%d - %s() - Failed to create window!\n", __FILE__, __LINE__, __FUNCTION__);
    exit(EXIT_FAILURE);
  }

  curs_set(0);

  if(has_colors() == false) {
    endwin();
    fprintf(stderr, "Your terminal does not support color\n");
    exit(EXIT_FAILURE);
  }
  start_color();
  init_colors();
  
  // allow us to catch the arrow keys
  keypad(state->game, TRUE);

}

static void draw(state_st *state)
{
  drawRoom(0, 0, LINES-1, COLS-1, state->game);
}

static bool running(state_st *state)
{
  return (state->running);
}

static void welcome(state_st *state)
{

  //once we are done getting rogue's name, turn off echo
  noecho();
}

int main()
{
  state_st state;
  
  // set locale, otherwise we cant use unicode characters for the walls
  setlocale(LC_ALL, "");

  // set up game
  game_init(&state);

  // welcome screen. get rogue's name
  welcome(&state);
  
  // roll character
  //rogue_init(&state);

  // game loop
  do {
    // draw
    draw(&state);
    
    // input
    input_handler(&state);
    
  } while(running(&state));
  
  
  
  
  
 
  endwin(); 
  return (EXIT_SUCCESS);
}
