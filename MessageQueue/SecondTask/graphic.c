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
#include "function.h"

  
WINDOW * mainWindow;
WINDOW * Username;
WINDOW * Input;
int userposition = 2;
int msgposition = 2;
int usercount = 0;

struct msgbuf{
  long mtype;
  char buf[20];
  int size;
};

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

  struct msgbuf old_msg = {0, ""};
  struct msgbuf users = {0};
  struct msgbuf user_message = {0};
  char our_name[50];
  struct msqid_ds qstatus = {0};
 

  key_t key_for_servmsg = ftok("server", 1);
  int msg_serv_username = msgget(key_for_servmsg, 0);

  key_t key_for_servmsg_1 = ftok("server", 2);
  int msg_serv_alert = msgget(key_for_servmsg_1, 0);

  key_t key_for_clientmsg = ftok("server", 3);
  int msg_serv = msgget(key_for_clientmsg, 0);

  if(key_for_servmsg == -1){
    perror("key");
  }
  if(msg_serv_alert < 0){
    perror("msg");
  }

  //получение нашего никнейма
  size_t rcvmsg_user = msgrcv(msg_serv_username, &users, 60, 7, 0);
  userposition++;
  mvwprintw(Username, userposition, 1, "%s", users.buf);
  wrefresh(Username);
  rcvmsg_user = 0;
  strncpy(our_name, users.buf, strlen(users.buf));
  memset(users.buf, '\0', 1);

  msgqnum_t num_of_msg = 0;

  while(1){
  //прием сообщений других пользователей
  size_t rcvmsg_1 = msgrcv(msg_serv_alert, (struct msgbuf*) &user_message, sizeof(struct msgbuf) - 8 - 4, 5, 0); 
  if(msgctl(msg_serv_alert, IPC_STAT, &qstatus)< 0){
    perror("ctl");
  }
      if(user_message.mtype == 5){
        mvwprintw(mainWindow, msgposition, 1, "%s", our_name);
        msgposition++;
        mvwprintw(mainWindow, msgposition, 1, "%s", user_message.buf);
        msgposition++;
        wrefresh(mainWindow);
        user_message.mtype = 0;
      }

  //прием уведомлений
  size_t rcvmsg_new = msgrcv(msg_serv_alert, &old_msg, 60, 2, IPC_NOWAIT);
  if(msgctl(msg_serv_alert, IPC_STAT, &qstatus)< 0){
    perror("ctl");
  }
  else{
    if(qstatus.msg_qnum > num_of_msg){
      mvwprintw(mainWindow, msgposition, 1, "%s", old_msg.buf);
      msgposition++;
      wrefresh(mainWindow);
    }
  }
  
  //прием никнеймов других клиентов
  size_t rcvmsg_user = msgrcv(msg_serv_username, &users, 60, 7, IPC_NOWAIT);
  if(msgctl(msg_serv_username, IPC_STAT, &qstatus)< 0){
    perror("ctl");
  }  
  else{
    if(users.mtype == 7){
      userposition++;
      mvwprintw(Username, userposition, 1, "%s", users.buf);
      wrefresh(Username);
      memset(users.buf, '\0', 1);
      users.mtype = 0;
    }
  }
  }
}

void* write_message(){

  char usersname_buf[10][10];
  char only_name_buf[10];
  struct msgbuf user_message = {3, ""};

  key_t key_for_clientmsg = ftok("server", 3);
  int msg_serv = msgget(key_for_clientmsg, 0);
    
  if(key_for_clientmsg == -1){
      perror("key");
  }
  if (msg_serv <= 0){
      perror("msgTYT");
  }

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
      wgetnstr(Input, user_message.buf, 19);
      user_message.size = strlen(user_message.buf) + 1 + 8;
      int send = msgsnd(msg_serv, &user_message, user_message.size, 0);
      if(send < 0){
         perror("send");
      }      

      msgposition++;
      werase(Input);
      mvwaddch(Input, 1, 0, '>');
      refresh();
      wrefresh(mainWindow);
      wrefresh(Input);
      leaveok(Input, TRUE);       
    }
    }

    refresh();
    wrefresh(mainWindow);
  }


  //delwin(mainWindow);

  refresh();
  getch();
  endwin();
  exit(EXIT_SUCCESS);
 
}
