#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* philosopher(void* arg) {
    int id = *(int*)arg;
    printf("Philosopher %d is thinking...\n", id);
    sleep(1); // Simulate thinking
    printf("Philosopher %d is eating...\n", id);
    sleep(1); // Simulate eating
    return NULL;
}

int main() {
    const int n_philosophers = 5;
    pthread_t threads[n_philosophers];
    int ids[n_philosophers];

    // Create philosopher threads
    for (int i = 0; i < n_philosophers; i++) {
        ids[i] = i + 1; // Assign an ID to each philosopher
        if (pthread_create(&threads[i], NULL, philosopher, &ids[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < n_philosophers; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
