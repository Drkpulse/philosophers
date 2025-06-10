#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>

#define MAX_PHILOSOPHERS 100

typedef struct {
    int id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    int meals_eaten;
    bool is_alive;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
} philosopher_t;

pthread_mutex_t forks[MAX_PHILOSOPHERS];
philosopher_t philosophers[MAX_PHILOSOPHERS];

long get_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void *philosopher_life(void *arg) {
    philosopher_t *phil = (philosopher_t *)arg;
    long last_meal_time = get_time_ms();

    while (phil->is_alive) {
        // Thinking
        printf("%ld %d is thinking\n", get_time_ms(), phil->id);
        usleep(phil->time_to_sleep * 1000);

        // Try to take forks
        pthread_mutex_lock(phil->left_fork);
        printf("%ld %d has taken a fork\n", get_time_ms(), phil->id);
        pthread_mutex_lock(phil->right_fork);
        printf("%ld %d has taken a fork\n", get_time_ms(), phil->id);

        // Eating
        printf("%ld %d is eating\n", get_time_ms(), phil->id);
        last_meal_time = get_time_ms();
        usleep(phil->time_to_eat * 1000);
        phil->meals_eaten++;

        // Drop forks
        pthread_mutex_unlock(phil->right_fork);
        pthread_mutex_unlock(phil->left_fork);

        // Check if the philosopher has died
        if (get_time_ms() - last_meal_time > phil->time_to_die) {
            phil->is_alive = false;
            printf("%ld %d died\n", get_time_ms(), phil->id);
            break;
        }

        // Sleeping
        printf("%ld %d is sleeping\n", get_time_ms(), phil->id);
        usleep(phil->time_to_sleep * 1000);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 5 || argc > 6) {
        fprintf(stderr, "Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return 1;
    }

    int number_of_philosophers = atoi(argv[1]);
    int time_to_die = atoi(argv[2]);
    int time_to_eat = atoi(argv[3]);
    int time_to_sleep = atoi(argv[4]);
    int number_of_times_each_philosopher_must_eat = (argc == 6) ? atoi(argv[5]) : -1;

    if (number_of_philosophers > MAX_PHILOSOPHERS) {
        fprintf(stderr, "Maximum number of philosophers is %d\n", MAX_PHILOSOPHERS);
        return 1;
    }

    // Initialize forks and philosophers
    for (int i = 0; i < number_of_philosophers; i++) {
        pthread_mutex_init(&forks[i], NULL);
        philosophers[i].id = i + 1;
        philosophers[i].time_to_die = time_to_die;
        philosophers[i].time_to_eat = time_to_eat;
        philosophers[i].time_to_sleep = time_to_sleep;
        philosophers[i].meals_eaten = 0;
        philosophers[i].is_alive = true;
        philosophers[i].left_fork = &forks[i];
        philosophers[i].right_fork = &forks[(i + 1) % number_of_philosophers];
    }

    // Create philosopher threads
    pthread_t threads[MAX_PHILOSOPHERS];
    for (int i = 0; i < number_of_philosophers; i++) {
        pthread_create(&threads[i], NULL, philosopher_life, &philosophers[i]);
    }

    // Wait for all philosophers to finish
    for (int i = 0; i < number_of_philosophers; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up
    for (int i = 0; i < number_of_philosophers; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

