/*
 * main.c
 *
 *
 * room algorithm test tool
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

#ifdef __APPLE__
#include <ncurses.h>
#elif __linux__
#include <ncursesw/curses.h>
#endif

#include "rooms.h"




// horizontal double line
#define HORIZ 0x2550
// for unicode 
#define HORIZU "\u2550"


// vertical double line
#define VERT 0x2551
#define VERTU "\u2551"


// top left corner 
#define TLCORNER 0x2554
#define TLCORNERU "\u2554"


// top right corner
#define TRCORNER 0x2557
#define TRCORNERU "\u2557"


// bottom left corner
#define BLCORNER 0x255A
#define BLCORNERU "\u255A"


// bottom right corner
#define BRCORNER 0x255D
#define BRCORNERU "\u255D"


// left T
#define LTEE 0x2560
#define LTEEU "\u2560"


// right T
#define RTEE 0x2563
#define RTEEU "\u2563"


// door
#define DOOR 0x256C
#define DOORU "\u256C"


// floor
#define FLOOR 0x2E
#define FLOORU "\x2E"


// tunnel
#define TUNNEL 0x2588
#define TUNNELU "\u2588"


static void horiz_line(int x, int y, int len)
{
  int i;

  move(y, x);

  for(i = 0; i < len; ++i) {
    addstr(HORIZU);
  } 

}

static void vert_line(int x, int y, int len)
{
  int i;
  
  for (i = 0; i < len; ++i) {
    move(y+i, x);
    addstr(VERTU);
  }
}


static void draw_box(int startx, int starty, int rows, int cols)
{
  move(starty, startx);
  
  addstr(TLCORNERU);
  horiz_line(startx+1, starty, cols-2);
  addstr(TRCORNERU);


  vert_line(startx, starty+1, rows-2);
  vert_line(startx+cols-1, starty+1, rows-2);

  
  move(starty+rows-1, startx);  
  addstr(BLCORNERU);
  horiz_line(startx+1, starty+rows-1, cols-2);
  addstr(BRCORNERU);
}

static void draw_room(int startx, int starty, int rows, int cols)
{
  int i, j;
  
  attrset(COLOR_PAIR(1));
  // first draw the box
  draw_box(startx, starty, rows, cols);
  
  attrset(COLOR_PAIR(2));
  // now fill the background
  for (i = 1; i < rows - 1; ++i) {
    for (j = 1; j < cols - 1; ++j) {
      move(starty + i, startx + j);
      addstr(FLOORU);
    }
  }
}



int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "");
  srand(time(NULL));
  
  initscr();
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
 
  map_st *m = generate_rooms();  

  for (int i = 0; i < m->num_rooms; ++i) {
     draw_room(m->rooms[i].pos.x, m->rooms[i].pos.y, m->rooms[i].y_len, m->rooms[i].x_len);
   }

   getch();
   endwin();

   free(m->rooms);
   free(m);
  
  return (0);
}
