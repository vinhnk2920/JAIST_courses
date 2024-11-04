#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

struct InputData {
    int nums[3];
};

struct OutputData {
    int sum;
    double average;
};

void calculate_sum_avg(struct InputData *input, struct OutputData *output) {
    output->sum = input->nums[0] + input->nums[1] + input->nums[2];
    output->average = output->sum / 3.0;
}

int main() {
    struct InputData inputData;
    struct OutputData outputData;
    int pipefd[2];
    pid_t pid;

    printf("Enter three integers separated by spaces: ");
    for (int i = 0; i < 3; i++) {
        if (scanf("%d", &inputData.nums[i]) != 1) {
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }
    }

    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        close(pipefd[0]);
        calculate_sum_avg(&inputData, &outputData);
        if (write(pipefd[1], &outputData, sizeof(outputData)) == -1) {
            perror("write failed");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        close(pipefd[1]);
        if (read(pipefd[0], &outputData, sizeof(outputData)) == -1) {
            perror("read failed");
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]);
        // Wait for child process to finish
        wait(NULL);
        printf("Sum: %d, Average: %.3f\n", outputData.sum, outputData.average);
    }

    return 0;
}