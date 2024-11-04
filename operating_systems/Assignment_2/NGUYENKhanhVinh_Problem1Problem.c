#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define INITIAL_BALANCE 1000
#define NUM_THREADS 5
#define MAX_TRANSACTION_AMOUNT 500

int balance = INITIAL_BALANCE;
pthread_mutex_t mutex;

void* bank_transaction(void* arg) {
    int transaction_type = rand() % 2;
    int amount = rand() % (MAX_TRANSACTION_AMOUNT + 1);

    pthread_mutex_lock(&mutex);

    if (transaction_type == 0) {
        // Deposit
        balance += amount;
        printf("Deposited %d. New balance: %d\n", amount, balance);
    } else {
        // Withdraw
        if (balance >= amount) {
            balance -= amount;
            printf("Withdrew %d. New balance: %d\n", amount, balance);
        } else {
            printf("Attempted to withdraw %d, but insufficient funds. Balance remains: %d\n", amount, balance);
        }
    }

    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    srand(time(NULL));

    // Initialize mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Mutex initialization failed");
        return 1;
    }

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, bank_transaction, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    printf("Final bank balance: %d\n", balance);
    return 0;
}