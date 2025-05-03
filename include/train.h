/*
** EPITECH PROJECT, 2025
** Trains-Bridge
** File description:
** train
*/

#ifndef TRAIN_H_
    #define TRAIN_H_

    #include <pthread.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <unistd.h>

    #define NB_TRAINS 3
    #define NB_MAX 2

typedef struct train_s {
    char *name;
    pthread_mutex_t *bridge;
    pthread_cond_t *bridge_status;
    int *trains_on_bridge;
} train_t;

// TRAINS FUNCTIONS
bool train_check_bridge(void *arg);
void train_cross_bridge(void *arg);
void *train_stop(void *arg);
void *train_running(void *arg);

#endif /* !TRAIN_H_ */
