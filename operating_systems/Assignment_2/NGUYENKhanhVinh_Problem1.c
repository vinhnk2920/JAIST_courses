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
    int transaction_type = rand() % 2; // 0: deposit, 1: withdraw
    int amount = rand() % (MAX_TRANSACTION_AMOUNT + 1);

    // Lock the mutex to ensure exclusive access to the balance variable
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

    // Unlock the mutex after updating the balance
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    srand(time(NULL));

    // Initialize the mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Mutex initialization failed");
        return 1;
    }

    // Create and start threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, bank_transaction, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    printf("Final bank balance: %d\n", balance);
    return 0;
}