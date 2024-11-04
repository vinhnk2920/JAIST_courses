#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

typedef struct {
    int number;
    int pipe_fd[2];
} thread_data_t;

void *sum_digits(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    int num = data->number;
    int sum = (num / 100) + ((num / 10) % 10) + (num % 10);

    if (write(data->pipe_fd[1], &sum, sizeof(int)) == -1) {
        perror("Write to pipe failed");
        pthread_exit(NULL);
    }
    pthread_exit(NULL);
}

int main() {
    int student_id_last_three;
    thread_data_t data;
    pthread_t thread;
    int result;

    printf("Enter the last three digits of your student ID: ");
    if (scanf("%d", &student_id_last_three) != 1 || student_id_last_three < 100 || student_id_last_three > 999) {
        fprintf(stderr, "Invalid input. Please enter a three-digit number.\n");
        exit(EXIT_FAILURE);
    }

    data.number = student_id_last_three;
    if (pipe(data.pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread, NULL, sum_digits, &data) != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(thread, NULL) != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }

    if (read(data.pipe_fd[0], &result, sizeof(int)) == -1) {
        perror("Read from pipe failed");
        exit(EXIT_FAILURE);
    }
    printf("The sum of the digits is: %d\n", result);
    close(data.pipe_fd[0]);
    close(data.pipe_fd[1]);

    return 0;
}