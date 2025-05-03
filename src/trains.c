/*
** EPITECH PROJECT, 2025
** Trains-Bridge
** File description:
** trains
*/

#include "train.h"

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