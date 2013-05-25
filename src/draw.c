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


#include "draw.h"
#include "colors.h"


void drawBox(int startx, int starty, int rows, int cols, WINDOW* win)
{
  int i;

  color_wall();

  wmove(win, starty, startx);
  
  addstr("\u2554");
  
  for(i = 2; i < cols; ++i) {
    addstr("\u2550");
  } 

  addstr("\u2557");

  for (i = 2; i < rows; ++i) {
    wmove(win, starty+i-1, startx);
    addstr("\u2551");
    
    wmove(win, starty+i-1, startx+cols-1);
    addstr("\u2551");
  }
  
  wmove(win, starty+rows-1, startx);
  
  addstr("\u255A");
  
  for(i = 2; i < cols; ++i) {
    addstr("\u2550");
  } 
  
  addstr("\u255D");
  
  refresh();
}


void drawRoom(int startx, int starty, int rows, int cols, WINDOW* win)
{
  int i, j;

  color_floor();

  // dark room? if so, don't draw anything except in the coordinates
  // directly next to the hero


  // first draw the box
  drawBox(startx, starty, rows, cols, win);
  
  startx++;
  starty++;

  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  attrset(COLOR_PAIR(2));
  // now fill the background
  for (i = starty; i < rows - 1; ++i) {
    wmove(win, i, startx);
    for (j = startx; j < cols - 1; ++j) {
      addstr(".");
    }
  }

  // draw doors

  // draw objects

  // draw monsters


}
