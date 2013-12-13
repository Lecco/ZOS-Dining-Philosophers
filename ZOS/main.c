/* 
 * File:   main.c
 * Author: Oldřich Pulkrt <O.Pulkrt@gmail.com>
 *
 * Created on 13. prosinec 2013, 10:59
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "constants.h"
#include "philosopher.c"

/**
 Init section
 */
int* forks = malloc(sizeof(int) * NUMBER_OF_PHILOSOPHERS);

/**
 * Init forks, set each of them to zero (if fork has other number, it means
 * that it is hold by philosopher with that id - 1 => because zero is table,
 * so philosopher with id=0 is represented by 1).
 */
void initForks()
{
    int i;
    for (i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
    {
        forks[i] = 0;
    }
}

/*
 * 
 */
int main(int argc, char** argv)
{
    printf("Starting...\n");
    initForks();
    return 0;
}
