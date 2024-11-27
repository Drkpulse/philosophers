#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>

typedef struct s_rules {
    int n_philo;
    long time_death;
    long time_eat;
    long time_sleep;
    int num_eat; // Optional: number of times each philosopher must eat
} t_rules;

typedef struct s_philo {
    int id;
    long last_meal_time;
    int meals_eaten;
    t_rules *rules;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_t thread;
    bool is_alive;
} t_philo;

long get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void *philosopher_behavior(void *arg) {
    t_philo *philo = (t_philo *)arg;

    while (philo->is_alive) {
        // Thinking
        printf("Philosopher %d is thinking.\n", philo->id);
        usleep((rand() % 1000 + 500) * 1000); // Simulate thinking time

        // Acquire left fork
        pthread_mutex_lock(philo->left_fork);
        printf("Philosopher %d has taken left fork.\n", philo->id);

        // Acquire right fork
        pthread_mutex_lock(philo->right_fork);
        printf("Philosopher %d has taken right fork.\n", philo->id);

        // Eating
        philo->last_meal_time = get_time();
        philo->meals_eaten++;
        printf("Philosopher %d is eating.\n", philo->id);
        usleep(philo->rules->time_eat * 1000); // Simulate eating time

        // Release right fork
        pthread_mutex_unlock(philo->right_fork);
        printf("Philosopher %d has released right fork.\n", philo->id);

        // Release left fork
        pthread_mutex_unlock(philo->left_fork);
        printf("Philosopher %d has released left fork.\n", philo->id);

        // Sleeping
        printf("Philosopher %d is sleeping.\n", philo->id);
        usleep(philo->rules->time_sleep * 1000); // Simulate sleeping time

        // Check for death condition
        if (get_time() - philo->last_meal_time > philo->rules->time_death) {
            printf("Philosopher %d has died.\n", philo->id);
            philo->is_alive = false;
            break;
        }
    }
    return NULL;
}


void *monitor_philosophers(void *arg) {
    t_philo *philosophers = (t_philo *)arg;
    t_rules *rules = philosophers[0].rules;

    while (true) {
        for (int i = 0; i < rules->n_philo; i++) {
            if (!philosophers[i].is_alive) {
                return NULL; // Exit if any philosopher has died
            }
            // Check if all philosophers have eaten the required number of times
            if (rules->num_eat > 0 && philosophers[i].meals_eaten >= rules->num_eat) {
                // Check if all philosophers have eaten the required number of times
                bool all_ate_enough = true;
                for (int j = 0; j < rules->n_philo; j++) {
                    if (philosophers[j].meals_eaten < rules->num_eat) {
                        all_ate_enough = false;
                        break;
                    }
                }
                if (all_ate_enough) {
                    return NULL; // Exit if all have eaten the required number of times
                }
            }
        }
        usleep(100); // Check every 100 microseconds
    }
}


int main(int argc, char **argv) {
    if (argc < 5 || argc > 6) {
        fprintf(stderr, "Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return 1;
    }

    t_rules rules;
        // Parse command line arguments
    rules.n_philo = atoi(argv[1]);
    rules.time_death = atol(argv[2]);
    rules.time_eat = atol(argv[3]);
    rules.time_sleep = atol(argv[4]);
	rules.num_eat = 0;
	if (argc == 6)
    	rules.num_eat = atoi(argv[5]); // Optional argument

    // Initialize philosophers and mutexes
    t_philo philosophers[rules.n_philo];
    pthread_mutex_t forks[rules.n_philo];

    // Initialize mutexes for forks
    for (int i = 0; i < rules.n_philo; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Initialize philosophers
    for (int i = 0; i < rules.n_philo; i++) {
        philosophers[i].id = i + 1;
        philosophers[i].rules = &rules;
        philosophers[i].left_fork = &forks[i];
        philosophers[i].right_fork = &forks[(i + 1) % rules.n_philo];
        philosophers[i].meals_eaten = 0;
        philosophers[i].last_meal_time = get_time();
        philosophers[i].is_alive = true;
        pthread_create(&philosophers[i].thread, NULL, philosopher_behavior, &philosophers[i]);
    }

    // Create a monitoring thread
    pthread_t monitor_thread;
    pthread_create(&monitor_thread, NULL, monitor_philosophers, philosophers);

    // Wait for all philosopher threads to finish
    for (int i = 0; i < rules.n_philo; i++) {
        pthread_join(philosophers[i].thread, NULL);
    }

    // Clean up
    for (int i = 0; i < rules.n_philo; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    // Wait for the monitor thread to finish
    pthread_cancel(monitor_thread);
    pthread_join(monitor_thread, NULL);

    return 0;
}
