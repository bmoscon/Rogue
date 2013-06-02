/*
 * draw.c
 *
 *
 * draw routines
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


#include <string.h>

#include "draw.h"
#include "colors.h"
#include "chars.h"


static void center_text(int row, const char *text, WINDOW *win)
{
  int indent;
  
  indent = COLS - strlen(text);
  indent /= 2;
  
  mvwaddstr(win, row, indent, text);
}

static void horiz_line(int x, int y, int len, WINDOW *win)
{
  int i;

  wmove(win, y, x);

  for(i = 0; i < len; ++i) {
    waddstr(win, HORIZU);
  } 

}

static void vert_line(int x, int y, int len, WINDOW *win)
{
  int i;
  
  for (i = 0; i < len; ++i) {
    wmove(win, y+i, x);
    waddstr(win, VERTU);
  }
}

void draw_box(int startx, int starty, int rows, int cols, WINDOW* win)
{
  color_wall();
  wmove(win, starty, startx);
  
  waddstr(win, TLCORNERU);
  horiz_line(startx+1, starty, cols-2, win);
  waddstr(win, TRCORNERU);


  vert_line(startx, starty+1, rows-2, win);
  vert_line(startx+cols-1, starty+1, rows-2, win);

  
  wmove(win, starty+rows-1, startx);  
  waddstr(win, BLCORNERU);
  horiz_line(startx+1, starty+rows-1, rows-2, win);
  waddstr(win, BRCORNERU);
}


void draw_room(int startx, int starty, int rows, int cols, bool floor, WINDOW* win)
{
  int i, j;
  // dark room? if so, don't draw anything except in the coordinates
  // directly next to the hero


  // first draw the box
  draw_box(startx, starty, rows, cols, win);
  
  startx++;
  starty++;
  if (floor) {
    color_floor();
    // now fill the background
    for (i = starty; i < rows; ++i) {
      wmove(win, i, startx);
      for (j = startx; j < cols - 1; ++j) {
	waddstr(win, FLOORU);
      }
    }
  }
}


void draw_welcome_box(WINDOW *win)
{
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
  center_text(LINES-6, "Copyright (C) 2013", win);
  center_text(LINES-5, "Bryant Moscon", win);
  center_text(LINES-4, "All Rights Reserved", win);

  wmove(win, LINES-2, 1);
  color_text();
  waddstr(win, "Rogue's Name: ");
  
}


void draw_stats(const state_st *state)
{
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

}

void draw_message(state_st *state)
{
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
}


void draw_door(int x, int y, WINDOW *win)
{
  color_wall();
  wmove(win, y, x);
  waddstr(win, DOORU);
}


void draw_tunnel(int x, int y, WINDOW *win)
{
  color_tunnel();
  wmove(win, y, x);
  waddstr(win, TUNNELU);
}


void draw_rogue(int x, int y, bool tunnel, WINDOW *win)
{
  if (tunnel) {
    color_rogue_tunnel();
  } else {
    color_rogue();
  }
  
  wmove(win, y, x);
  waddstr(win, ROGUEU);
}


void draw_stairs(int x, int y, WINDOW *win)
{
  color_stairs();
  wmove(win, y, x);
  waddstr(win, STAIRSU);
}


void draw_items(int x, int y, items_e item, WINDOW *win)
{
  switch(item) {
    case I_GOLD:
      color_gold();
      wmove(win, y, x);
      waddstr(win, GOLDU);
      break;
    default:
      break;
  }
    
  
}
