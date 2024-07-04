#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <stdio.h>
#include <string.h>

int graphic(char*);
void* receive_from_server();
void* write_message();