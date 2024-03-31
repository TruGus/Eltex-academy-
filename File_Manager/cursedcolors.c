#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <stdio.h>
#include <string.h>
#include "function.h"
#include <dirent.h>

void sig_winch(int signo)
{
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
  resizeterm(size.ws_row, size.ws_col);
}

int main(int argc, char ** argv)
{

  WINDOW * mainWindow;
  WINDOW * headWindow;
  WINDOW * submainWindow;

  WINDOW * secondWindow;
  WINDOW * headsecondWindow;
  WINDOW * subsecondWindow;

  initscr();
  int yMax, xMax;
  int *ptr_yMax;
  int *ptr_xMax;
  getmaxyx(stdscr,yMax,xMax);
  signal(SIGWINCH, sig_winch);
  start_color();
  refresh();

  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  init_pair(2, COLOR_YELLOW, COLOR_BLUE);

  mainWindow = newwin(yMax,xMax/2, 0, 0);
  wbkgd(mainWindow, COLOR_PAIR(1));
  wattron(mainWindow, A_BOLD);


  headWindow = derwin(mainWindow, yMax - 1, xMax/2 - 1, 1, 1);
  wbkgd(headWindow, COLOR_PAIR(2));
  wattron(headWindow, A_BOLD);

  submainWindow = derwin(mainWindow, yMax - 2, xMax/2 - 1, 1, 1);

  secondWindow = newwin(yMax,xMax/2, 0, xMax/2);
  wbkgd(secondWindow, COLOR_PAIR(1));
  wattron(secondWindow, A_BOLD);

  headsecondWindow = derwin(secondWindow, yMax - 1, xMax/2 - 1, 1, 1);
  wbkgd(headsecondWindow, COLOR_PAIR(2));
  wattron(headsecondWindow, A_BOLD);

  borderWrite(headWindow,headsecondWindow);

  subsecondWindow = derwin(secondWindow, yMax - 2, xMax/2 - 1, 1, 1);

  refresh();
  wrefresh(mainWindow);
  wrefresh(secondWindow);

  dirinfo(submainWindow, subsecondWindow, headWindow, headsecondWindow);

  refresh();
  wrefresh(mainWindow);
  wrefresh(secondWindow);
  delwin(mainWindow);

  refresh();
  getch();
  endwin();
  exit(EXIT_SUCCESS);
}
