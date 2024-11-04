
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

char *PIPE_NAME = "/tmp/msg_pipe";
size_t BUFFER_SIZE = 100;

int main() {

  int fd;
  char buffer[BUFFER_SIZE];

  printf("This is the reader.\n");

  printf("Creating named pipe '%s'...\n", PIPE_NAME);
  mkfifo(PIPE_NAME, S_IWUSR | S_IRUSR);

  printf("Opening named pipe...\n");
  fd = open(PIPE_NAME, O_RDONLY);

  printf("Reading from named pipe...\n");
  ssize_t count = read(fd, buffer, BUFFER_SIZE);

  // Print the received message
  printf("Received message '%s'. [%ld chars]\n",
	 buffer, count);

  printf("Closing pipe...\n");
  close(fd);

  printf("Removing pipe...\n");
  unlink(PIPE_NAME);

  return 0;
}
