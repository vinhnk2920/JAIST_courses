
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

char *PIPE_NAME = "/tmp/msg_pipe";

int main() {

  int fd;
  char *MESSAGE = "Hello, I'm you buddy!";

  printf("This is the writer.\n");

  printf("Opening named pipe '%s'...\n", PIPE_NAME);
  if ((fd = open(PIPE_NAME, O_WRONLY)) == -1) {
    perror("open");
    return -1;
  }

  printf("Sleeping...\n");
  sleep(10);

  printf("Writing to named pipe...\n");
  ssize_t count;
  if ((count = write(fd, MESSAGE, strlen(MESSAGE)+1)) != (int)strlen(MESSAGE)+1) {
    perror("write");
    return -2;
  }

  printf("Closing pipe...\n");
  int result;
  if ((result=close(fd)) == -1) {
    perror("close");
    return -3;
  }

  return 0;
}
