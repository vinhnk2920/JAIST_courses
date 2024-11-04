#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main() {
	int pid, fd[2];
	char buffer[80];
	
	if (pipe(fd) < 0) {
		/* Un-named Pipe initiation error */
		fprintf(stderr, "Pipe failed... %s\n", strerror(errno));
		exit(-1);
	}
	
	/* fork a process */
	pid = fork();
	if (pid < 0) {
		/* Forking error */
		fprintf(stderr, "Fork failed... %s\n", strerror(errno));
		exit(-1);
	}
	
	if (pid == 0) {
		/* child process */
		close(fd[0]);
		if (write(fd[1], "testing message", 16) != 16) {
			/* Writing error */
			fprintf(stderr, "Child: Writing failed... %s\n", strerror(errno));
			exit(-1);
		}
		printf ("Child process (pid:%d): testing message sent\n", getpid());
	} else {
		/* parent process */
		close(fd[1]);
		if (read(fd[0], &buffer, 80) != 16) {
			/* Reading error */
			fprintf(stderr, "Parent: Reading failed... %s\n", strerror(errno));
			exit(-1);
		}
		wait(NULL);
		printf("Parent process (pid: %d): received from child process (pid:%d) message (%s)\n", getpid(), pid, buffer);
		}
	
	return 0;
}
