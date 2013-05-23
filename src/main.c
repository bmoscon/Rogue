#include <ncurses.h>
#include <locale.h>

#include "draw.h"

int main()
{
  WINDOW *win;
  
  setlocale(LC_ALL, "");
  
  win = initscr();
  curs_set(0);
  
  if(has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    return(1);
  }
  start_color();
  
  
  drawRoom(0, 0, LINES, COLS, win);
  
  
  getch();
  endwin();
  
  return 0; 
}
