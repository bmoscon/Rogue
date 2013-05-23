#include "colors.h"

void color_wall()
{
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);
  attrset(COLOR_PAIR(1));
}


void color_floor()
{
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  attrset(COLOR_PAIR(2));
}
