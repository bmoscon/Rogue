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
