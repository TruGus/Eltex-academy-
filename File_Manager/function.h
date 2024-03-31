#include <stdio.h>
#include <curses.h>
#include <dirent.h>

void dirinfo(WINDOW*, WINDOW*,WINDOW*, WINDOW*);
void* dirinfo_s(WINDOW*, char*, WINDOW*, WINDOW*);
void borderWrite(WINDOW*, WINDOW*);
