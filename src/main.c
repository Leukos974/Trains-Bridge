/*
** EPITECH PROJECT, 2025
** Trains-Bridge
** File description:
** main
*/

#include "train.h"

int main(void)
{
    pthread_t threads[NB_TRAINS];
    train_t trains[NB_TRAINS];
    pthread_mutex_t bridge = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t bridge_status = PTHREAD_COND_INITIALIZER;
    char *names[] = {
        "Express 1",
        "Old Locomotive",
        "TGV"
    };
    int trains_on_bridge = 0;

    for (int i = 0; i < NB_TRAINS; i++) {
        trains[i].name = names[i];
        trains[i].bridge = &bridge;
        trains[i].bridge_status = &bridge_status;
        trains[i].trains_on_bridge = &trains_on_bridge;
    
        if (pthread_create(&threads[i], NULL, train_running, &trains[i]) != 0) {
            perror("Thread_create: ");
            return 84;
        }
        sleep(1);
    }
    fflush(stdout);
    printf("All trains started their journey.\n");
    for (int i = 0; i < NB_TRAINS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join: ");
            return 84;
        }
    }
    printf("All trains are stopped.\n");
    return 0;
}