/*
** EPITECH PROJECT, 2025
** Trains-Bridge
** File description:
** main
*/

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define NB_TRAINS 1

typedef struct train_s {
    char *name;
    pthread_mutex_t *bridge;
} train_t;

bool train_check_bridge(void *arg)
{
    train_t *train = (train_t *)arg;

    if (pthread_mutex_trylock(train->bridge) == 0) {
        printf("%s has permission to cross bridge.\n", train->name);
        return true;
    }
    return false;
}

void train_cross_bridge(void *arg)
{
    train_t *train = (train_t *)arg;

    printf("%s is crossing bridge...\n", train->name);
    sleep(3);
    pthread_mutex_unlock(train->bridge);
    printf("%s finished crossing the bridge !\n", train->name);
}

void *train_stop(void *arg)
{
    train_t *train = (train_t *)arg;

    printf("%s stopped at gare.\n", train->name);
    return NULL;
}

void *train_running(void *arg)
{
    train_t *train = (train_t *)arg;

    printf("%s is running....\n", train->name);
    sleep(1);

    while(!train_check_bridge(arg));

    train_cross_bridge(arg);
    
    return train_stop(arg);
}

int main(void)
{
    pthread_t train1;
    pthread_t train2;

    pthread_mutex_t bridge = PTHREAD_MUTEX_INITIALIZER;

    train_t arg[] = {
        {"Express 1", &bridge},
        {"Old Locomotive", &bridge}
    };

    if (pthread_create(&train1, NULL, train_running, &arg[0]) != 0) {
        perror("Thread_create (train1): ");
        return 84;
    }

    sleep(1);

    if (pthread_create(&train2, NULL, train_running, &arg[1]) != 0) {
        perror("Thread_create (train1): ");
        return 84;
    }

    if (pthread_join(train1, NULL) != 0) {
        perror("pthread_join (train1): ");
        return 84;
    }

    if (pthread_join(train2, NULL) != 0) {
        perror("pthread_join (train2): ");
        return 84;
    }

    printf("All trains are stopped.\n");
    
    return 0;
}