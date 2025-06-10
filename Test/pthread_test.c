#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 5

pthread_mutex_t mutex;
int shared_counter = 0;

void* increment_counter(void* arg) {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 10000; i++) {
        shared_counter++;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value: %d\n", shared_counter);
    pthread_mutex_destroy(&mutex);
    return 0;
}
