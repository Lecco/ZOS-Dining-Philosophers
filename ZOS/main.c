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

int leftRightHands[NUMBER_OF_PHILOSOPHERS];
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
    int firstFork, secondFork;
    if (leftRightHands[id] == 1)
    {
        firstFork = id;
        secondFork = (id + 1) % NUMBER_OF_PHILOSOPHERS;
    }
    else
    {
        firstFork = (id + 1) % NUMBER_OF_PHILOSOPHERS;
        secondFork = id;
    }
    printf("Philosopher %d is trying to eat.\n", id);
    pthread_mutex_lock(&forks[firstFork]);
    printf("Philosopher %d has first fork.\n", id);
    pthread_mutex_lock(&forks[secondFork]);
    printf("Philosopher %d has second fork.\n", id);
    printf("Philosopher %d is eating.\n", id);
    usleep(rand() % 5);
    pthread_mutex_unlock(&forks[secondFork]);
    pthread_mutex_unlock(&forks[firstFork]);
}

/**
 * Philosopher thinks for a while before trying to eat again
 * 
 * @param id Id of philosopher
 */
void think(int id)
{
    printf("Philosopher %d is thinking.\n", id);
    usleep(rand() % 5);
}


/**
 * Philosophers think or eat
 * 
 * @param philosopher Philosopher thread
 */
void* philosoph(void* philosopher)
{
    int index = *(int*)philosopher;
    while (1)
    {
        think(index);
        eat(index);
        usleep(1);
    }
}

/*
 * 
 */
int main(int argc, char** argv)
{
    printf("This program starts %d threads as philosophers. Each philosopher either thinks or eats. Philosopher needs two forks to eat.\n", NUMBER_OF_PHILOSOPHERS);
    printf("You can either run program withou parameters (one of philosophers will be left handed) or you can run it as <program name> -right to let all philosophers be right handed (this option may cause deadlock).\n\nPRESS ANY KEY TO CONTINUE...\n");
    
    char line[256];
    int i;
    
    for (i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
    {
        leftRightHands[i] = 1;
    }
    
    if (argc == 1)
    {
        leftRightHands[0] = 0;
    }
    
    fgets(line, sizeof line, stdin);
    int philosophers_id[NUMBER_OF_PHILOSOPHERS];
    initForks(philosophers_id);
    //init philosopher threads
    for (i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
    {
        pthread_create(philosophers + i, 0, philosoph, philosophers_id + i);
    }
    for (i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], 0);
    }
    
    return 0;
}
