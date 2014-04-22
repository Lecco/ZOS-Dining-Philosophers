/* 
 * File:   main.c
 * Author: Oldřich Pulkrt <O.Pulkrt@gmail.com>
 *
 * Created on 13. prosinec 2013, 10:59
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "constants.h"

/**
 Init section
 */
// int* forks = malloc(sizeof(int) * NUMBER_OF_PHILOSOPHERS);
pthread_mutex_t forks[NUMBER_OF_PHILOSOPHERS];
pthread_t philosophers[NUMBER_OF_PHILOSOPHERS];
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * Init forks, set each of them to zero (if fork has other number, it means
 * that it is hold by philosopher with that id - 1 => because zero is table,
 * so philosopher with id=0 is represented by 1).
 */
void initForks(int *philosophers_id)
{
    int i;
    for (i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
    {
        pthread_mutex_init(forks + (philosophers_id[i] = i), 0);
    }
}

/**
 * Philosopher tries to eat (he must have two forks, otherwise he puts
 * all forks back on table and waits)
 * 
 * @param id Id of philosopher
 */
void eat(int id)
{
    printf("Philosopher %d is trying to eat.\n", id);
    pthread_mutex_lock(forks[id]);
    printf("Philosopher %d has first fork.\n", id);
    pthread_mutex_lock(forks[id + 1 % NUMBER_OF_PHILOSOPHERS]);
    printf("Philosopher %d has second fork.\n", id);
    printf("Philosopher %d is eating.\n", id);
    sleep(rand() * 5);
    pthread_mutex_unlock(forks[id + 1 % NUMBER_OF_PHILOSOPHERS]);
    pthread_mutex_unlock(forks[id]);
}

/**
 * Philosopher thinks for a while before trying to eat again
 * 
 * @param id Id of philosopher
 */
void think(int id)
{
    printf("Philosopher %d is thinking.\n", id);
    sleep(rand() * 5);
}


/**
 * Philosophers think or eat
 * 
 * @param index Index of philosopher
 */
void philosoph(int index)
{
    while (1)
    {
        think(index);
        eat(index);
    }
}

/*
 * 
 */
int main(int argc, char** argv)
{
    printf("Starting...\n");
    // TODO: doplnit vice textu o tom, co program dela
    int philosophers_id[NUMBER_OF_PHILOSOPHERS];
    initForks(philosophers_id);
    return 0;
    //init philosopher threads
    int i;
    for (i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
    {
        pthread_create(philosophers + i, 0, philosoph, philosophers_id + i);
    }
    return pthread_join(philosophers[0], 0);
}
