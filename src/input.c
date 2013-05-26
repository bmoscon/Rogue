/*
 * input.c
 *
 *
 * input handlers
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


#include "input.h"
#include "colors.h"
#include "windows.h"


static void quit_handler(state_st *state)
{
  int i;

  // clear text area
  move(LINES-1, 0);
  for (i = 0; i < COLS; ++i) {
    delch();
  }
  refresh();
  
  // set color
  color_text();
  addstr("Are you sure you want to quit (y/n)?");
  
  i = getch();
  
  if (i == 'y') {
    state->running = false;
  } else {
    // replace with old text (i.e. stats)
    move(LINES-1, 0);
    for (i = 0; i < COLS; ++i) {
      delch();
    }
    refresh();
  }
}

static void help_handler(state_st *state)
{
  switch_win(state->help);
  getch();
  switch_win(state->game);
}


static void move_handler(state_st *state, int x, int y)
{
  // x and y indicate in what direction we are moving. 
  
}


void input_handler(state_st *state)
{
  int input;

  if (!state) {
    endwin();
    fprintf(stderr, "%s:%d - %s() - NULL game state\n", __FILE__, __LINE__, __FUNCTION__);
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
    default:
      break;
     
  }
  
 
  
}
