#include "function.h"
#include <curses.h>
#include <stdlib.h>

void borderWrite(WINDOW* headWindow, WINDOW* headsecondWindow){

  int yMax, xMax;
  getmaxyx(stdscr,yMax,xMax);

  for(int i = 0; i < xMax/2 - 10; i++){
    mvwvline(headWindow, 1, i, '-', 1);
  }

  for(int i = 0; i < yMax; i++){
    mvwvline(headWindow, i, 0, '|', 1);
    mvwvline(headWindow, i, xMax/2 - 10, '|', 1);
  }

  mvwprintw(headWindow, 0, 1, "%s", "Name");
  mvwprintw(headWindow, 0, 40, "%s", "Type");



  for(int i = 0; i < xMax/2 - 10; i++){
    mvwvline(headsecondWindow, 1, i, '-', 1);
  }
  for(int i = 0; i < yMax; i++){
    mvwvline(headsecondWindow, i, 0, '|', 1);
    mvwvline(headsecondWindow, i, xMax/2 - 10, '|', 1);
  }
  mvwprintw(headsecondWindow, 0, 1, "%s", "Name");
  mvwprintw(headsecondWindow, 0, 40, "%s", "Type");


  wrefresh(headWindow);
  wrefresh(headsecondWindow);
}
