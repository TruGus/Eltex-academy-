#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include "function.h"
#include <sys/shm.h>

  
WINDOW * mainWindow;
WINDOW * Username;
WINDOW * Input;
int userposition = 2;
int msgposition = 2;
int usercount = 0;

struct msgbuf{
  char All_message[20][20];
  char All_users[10][20];
  char Start_message[20];
  char Alert_message[20];
  char Your_name[20];
  char User_message[20];
  int usercount;
  int check_user;
  int check_message;
  short usercontrol;
  short messagecontrol;
  short allertcontrol;
};

struct msgbuf *memory = {0};

void sig_winch(int signo)
{
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
  resizeterm(size.ws_row, size.ws_col);
}

int graphic(char* login)
{
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

  mainWindow = newwin(yMax,xMax, 0, 0);
  mvwprintw(mainWindow, 1, 1, "%s", "Chat");

  Username = subwin(mainWindow, yMax - yMax/6 + 1, xMax/4, 0, xMax - xMax/4);
  mvwprintw(Username, 1, 1, "%s", "Users");

  Input = subwin(mainWindow, yMax/6, xMax, yMax - yMax/6, 0);

  mvwprintw(Input, 0, 0, "%s", "Message:");
  keypad(Input, true);
  curs_set(true);

  refresh();
  wrefresh(mainWindow);

  pthread_t thread_in;
  pthread_t thread_alert;
  int *s;
  
  pthread_create(&thread_in, NULL, receive_from_server, NULL);
  pthread_create(&thread_alert, NULL, write_message(), NULL);


  pthread_join(&thread_in,(void**)&s);
  pthread_join(&thread_alert,(void**)&s);


}

void* receive_from_server(){

  struct sembuf lock[2] = {{0,0,0},
  {0,1,0}};
  struct sembuf unlock[1] = {0,-1,0};

  char* path = "server";
  char my_name[20];

  __key_t key = ftok(path, 1);
  __key_t key_for_sem = ftok(path, 2);
  int msg = shmget(key, 1, 0);
  int sem = semget(key_for_sem, 1, 0);

  //получение нашего никнейма
  if(memory->check_user == 1){
    strncpy(my_name, memory->All_users[memory->check_user-1], 20);
  }
  else{
    strncpy(my_name, memory->All_users[memory->check_user], 20);
  }
  mvwprintw(Username, userposition, 1, "%s", my_name);
  userposition++;
  memory->usercontrol = 0;
  memory->messagecontrol = 0;
  wrefresh(Username);

  while(1){
  //прием сообщений других пользователей
    if(memory->messagecontrol == 1){
      mvwprintw(mainWindow, msgposition, 1, "%s", memory->All_message[memory->check_message]);
      msgposition++;
      memory->messagecontrol = 0;
      wrefresh(mainWindow);
    }

  //прием уведомлений
  //прием никнеймов других клиентов
    if(memory->allertcontrol == 1){
      mvwprintw(mainWindow, msgposition, 1, "%s", memory->Alert_message);
      msgposition++;
      wrefresh(mainWindow);
      for(int i = 0; i < memory->usercount + 1; i++){
        mvwprintw(Username, userposition, 1, "%s", memory->All_users[i]);
        userposition++;
        wrefresh(Username);
      }
      userposition = 2;
      memory->allertcontrol = 0;
    }
  }
}

void* write_message(){

  struct sembuf lock[2] = {{0,0,0},
  {0,1,0}};
  struct sembuf unlock[1] = {0,-1,0};

  char* path = "server";

  __key_t key = ftok(path, 1);
  __key_t key_for_sem = ftok(path, 2);
  int msg = shmget(key, 1, 0);
  int sem = semget(key_for_sem, 1, 0);

  memory = (struct msgbuf *) shmat(msg, 0, 0666);

  int ch;
  int x, y = 0;
  int i = 2;

  while(ch = wgetch(Input)){

    if(ch == KEY_BACKSPACE){
      getyx(Input, y, x);
      mvwdelch(Input, y,x);
      refresh();
      wrefresh(mainWindow);
    }
    if(ch == '\n'){
      werase(Input);
      wrefresh(Input);
    if(ch == '\n'){
      wgetnstr(Input, memory->User_message, 20);      
      werase(Input);
      mvwaddch(Input, 1, 0, '>');
      refresh();
      wrefresh(mainWindow);
      wrefresh(Input);
      leaveok(Input, TRUE);
      memory->messagecontrol = 1;
      semop(sem, &unlock,1);       
    }
    if(ch == KEY_UP){
      delwin(mainWindow);
      refresh();
      getch();
      endwin();
      exit(0);
    }
    }

    refresh();
    wrefresh(mainWindow);
  }
    shmdt(memory);
    shmctl(msg, IPC_RMID, 0);
    semctl(sem, 3, IPC_RMID);
}
