/*
 * I233E -- Lecture 2: Processes
 *
 * Demo on process creation using fork().
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char* argv[]) {

  int pid;

  /* Fork another process */
  pid = fork();

  if(pid < 0) {
    /* Error occurred */
    fprintf(stderr, "Fork failed!\n");
    return -1;
  } else if (pid == 0) {

    /* Inside the child process */
    printf ("I am the child process (pid:%d).\n", getpid());
    execlp("/bin/ls", "ls", "-l", NULL); /* Run the command 'ls' */
    return 0;
  } else {

    /* Inside the parent process */
    wait(NULL); /* Wait for the child process to end */
    printf("I am the parent process (pid:%d); my child (pid:%d) has completed.\n", getpid(), pid);
    return 0;
  }
}
