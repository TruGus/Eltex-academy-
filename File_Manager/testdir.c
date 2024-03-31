#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <curses.h>
#include "function.h"
#include <string.h>
#include <sys/stat.h>
#include <malloc.h>


void dirinfo(WINDOW* mainWindow, WINDOW* secondWindow, WINDOW* headWindow, WINDOW* headsecondWindow){

    keypad(mainWindow, true);
    noecho();

    int c = 0;
    int i = 0;
    int namePosition_x = 1;
    int namePosition_y = 2;
    int curPosition_x = 0;
    int curPosition_y = 0;
    int curPosition_x_max;
    int curPosition_y_max;
    int filecount = 0;
    struct dirent **files;
    int count = 0;
    char slash[2] = "/";
    char str[200] = "/";
    char *path;
    int listcount = 1;

      count = scandir("/", &files, 0, alphasort);
      if(count < 0)
        perror("scandir");

      while(count--){
        if(files[count]->d_type == DT_DIR){
          mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
          mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "DIR");
        }

        if(files[count]->d_type == DT_REG){
          mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
          mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "REG");
        }

        if(files[count]->d_type == DT_FIFO){
          mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
          mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "FIFO");
        }

        if(files[count]->d_type == DT_UNKNOWN){
          mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
          mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "---");
        }

        if(files[count]->d_type == DT_BLK){
          mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
          mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "BLK");
          }

        if(files[count]->d_type == DT_CHR){
          mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
          mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "CHR");
        }

        if(files[count]->d_type == DT_LNK){
          mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
          mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "LNK");
          }

        if(files[count]->d_type == DT_SOCK){
          mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
          mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "SOCK");
        }

        namePosition_y++;
        filecount++;
        wrefresh(mainWindow);
      }


      path = realloc(path, sizeof(char) * filecount * 10);
      strcpy(path, slash);

      count = 0;
      filecount = 0;

      getyx(mainWindow, curPosition_y_max, curPosition_x_max);
      mvwprintw(mainWindow, curPosition_y_max - 6, 57, "%s", "exit");
      mvwprintw(mainWindow, curPosition_y_max - 5, 57, "%s", "<---");
      mvwprintw(mainWindow, curPosition_y_max - 4, 57, "%s", "wnd");
      mvwprintw(mainWindow, curPosition_y_max - 3, 57, "%s", "TAB");
      mvwprintw(mainWindow, curPosition_y_max - 2, 57, "%s", "---");
      mvwprintw(mainWindow, curPosition_y_max - 1, 57, "%s", "list");
      mvwprintw(mainWindow, curPosition_y_max, 57, "%s", "<-->");
      mvwinsch(mainWindow, curPosition_y_max, 1, '>');
      curPosition_x = curPosition_x_max;
      curPosition_y = curPosition_y_max;
      //mvwprintw(mainWindow, 2, namePosition_x + 55, "%d/%d", listcount, 1);

      while(c != KEY_BACKSPACE){

        c = wgetch(mainWindow);
        switch (c) {
          case KEY_UP:
            if(curPosition_y > 2){
              mvwdelch(mainWindow, curPosition_y, 1);
              mvwinsch(mainWindow, curPosition_y - 1, 1, '>');
              count++;
              curPosition_y--;
            }
          break;

          case KEY_DOWN:
            if(count > 0 && curPosition_y <= curPosition_y_max){
              mvwdelch(mainWindow, curPosition_y, 1);
              mvwinsch(mainWindow, curPosition_y + 1, 1, '>');
              count--;
              curPosition_y++;
            }
          break;

          case KEY_LEFT:
            if(listcount > 1){
              filecount = 0;
              werase(mainWindow);
              borderWrite(headWindow,headsecondWindow);
              getmaxyx(stdscr,curPosition_y_max,curPosition_x_max);
              namePosition_y = 2;
              curPosition_y = 2;
              listcount--;
              //mvwprintw(mainWindow, 2, namePosition_x + 55, "%d/%d", listcount, listcount + 1);
              count = scandir(str, &files, 0, alphasort);
              if(count < 0)
                perror("scandir");

                while(count--){
                  if(files[count]->d_type == DT_DIR){
                    mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                    mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "DIR");
                  }

                  if(files[count]->d_type == DT_REG){
                    mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                    mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "REG");
                  }

                  if(files[count]->d_type == DT_FIFO){
                    mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                    mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "FIFO");
                  }

                  if(files[count]->d_type == DT_UNKNOWN){
                    mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                    mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "---");
                  }

                  if(files[count]->d_type == DT_BLK){
                    mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                    mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "BLK");
                    }

                  if(files[count]->d_type == DT_CHR){
                    mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                    mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "CHR");
                  }

                  if(files[count]->d_type == DT_LNK){
                    mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                    mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "LNK");
                    }

                  if(files[count]->d_type == DT_SOCK){
                    mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                    mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "SOCK");
                  }
                    namePosition_y++;
                    curPosition_y++;
                    filecount++;

                    wrefresh(mainWindow);
                }
                wrefresh(mainWindow);
                mvwinsch(mainWindow, 2, 1, '>');

                curPosition_y = 2;
                count = filecount - 1;
              }
            break;

          case KEY_RIGHT:
            if(filecount > curPosition_y_max){
              werase(mainWindow);
              borderWrite(headWindow,headsecondWindow);
              listcount++;
              //mvwprintw(mainWindow, 2, namePosition_x + 55, "%d/%d", listcount, listcount);
              count = scandir(str, &files, 0, alphasort) - curPosition_y_max - 2;

              if(count < 0)
                perror("scandir");

                filecount = count;

              namePosition_y = 2;
              while(count >= 0){
                if(files[count]->d_type == DT_DIR){
                  mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                  mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "DIR");
                }

                if(files[count]->d_type == DT_REG){
                  mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                  mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "REG");
                }

                if(files[count]->d_type == DT_FIFO){
                  mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                  mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "FIFO");
                }

                if(files[count]->d_type == DT_UNKNOWN){
                  mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                  mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "---");
                }

                if(files[count]->d_type == DT_BLK){
                  mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                  mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "BLK");
                  }

                if(files[count]->d_type == DT_CHR){
                  mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                  mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "CHR");
                }

                if(files[count]->d_type == DT_LNK){
                  mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                  mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "LNK");
                  }

                if(files[count]->d_type == DT_SOCK){
                  mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                  mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "SOCK");
                }
                  namePosition_y++;
                  count--;
                  wrefresh(mainWindow);
              }

              mvwinsch(mainWindow, namePosition_y - 1, 1, '>');

              wrefresh(mainWindow);
              curPosition_y = namePosition_y;
              curPosition_y--;
              count = 0;
            }


            break;

          case '\n':
          if(files[count]->d_type == DT_DIR && count >= 0){
          werase(mainWindow);
          borderWrite(headWindow,headsecondWindow);
          namePosition_y = 2;
          strcat(str,slash);
          strcat(str,files[count]->d_name);
          count = scandir(str, &files, 0, alphasort);
          if(count < 0)
            perror("scandir");

          while(count--){
              if(files[count]->d_type == DT_DIR){
                mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "DIR");
              }

              if(files[count]->d_type == DT_REG){
                mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "REG");
              }

              if(files[count]->d_type == DT_FIFO){
                mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "FIFO");
              }

              if(files[count]->d_type == DT_UNKNOWN){
                mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "---");
              }

              if(files[count]->d_type == DT_BLK){
                mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "BLK");
                }

              if(files[count]->d_type == DT_CHR){
                mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "CHR");
              }

              if(files[count]->d_type == DT_LNK){
                mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "LNK");
                }

              if(files[count]->d_type == DT_SOCK){
                mvwprintw(mainWindow, namePosition_y, namePosition_x, "%s", files[count]->d_name);
                mvwprintw(mainWindow, namePosition_y, namePosition_x + 40, "%s", "SOCK");
              }

              namePosition_y++;
              filecount++;
              wrefresh(secondWindow);
              free(files[count]);

            }

          curPosition_y = 1;
          count = namePosition_y - 2;
          wrefresh(mainWindow);
        }
          break;

          case '\t':
          mvwdelch(mainWindow, curPosition_y, 1);
          wrefresh(mainWindow);

          path = dirinfo_s(secondWindow, path, headWindow, headsecondWindow);
          break;

          case KEY_BACKSPACE:
            break;
        }

      }
      free(files);
    //  free(str);
      free(path);
};
