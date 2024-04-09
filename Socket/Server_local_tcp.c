#include <stdlib>

int main(){
  Struct sockaddr_un serv, client;
  int fd = Socket(AF_LOCAL, SOCK_STREAM,0);
  Bind(serv);
  Listen(fd,1);
  Sun_family = AF_LOCAL;
  Sun_path = /tmp/stream_serv;
  new_fd = accept(fd, client, len);
  Recv(new_fd, buf, size, 0);
  Send(new_fd, buf, size, 0);
  close(new_fd);
  close(fd);

}
