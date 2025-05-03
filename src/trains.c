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

    pthread_mutex_lock(train->bridge);
    
    if (*(train->trains_on_bridge) < NB_MAX) {
        printf("%s has permission to cross bridge.\n", train->name);
        (*train->trains_on_bridge)++;
        pthread_mutex_unlock(train->bridge);
        return true;
    }
    printf("%s is waiting for crossing the bridge\n", train->name);
    pthread_cond_wait(train->bridge_status, train->bridge);
    pthread_mutex_unlock(train->bridge);
    return false;
}

void train_cross_bridge(void *arg)
{
    train_t *train = (train_t *)arg;

    printf("%s is crossing bridge...\n", train->name);
    sleep(6);
    printf("%s finished crossing the bridge !\n", train->name);
    pthread_mutex_lock(train->bridge);
    (*train->trains_on_bridge)--;
    pthread_cond_broadcast(train->bridge_status);
    pthread_mutex_unlock(train->bridge);
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