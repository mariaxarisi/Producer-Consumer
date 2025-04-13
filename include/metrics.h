#ifndef METRICS_H
#define METRICS_H

#include "../include/config.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

extern double *elapsedTimes;
extern int elapsedCounter;
extern pthread_mutex_t elapsedMutex;

void initializeElapsedTimes(int size);
void freeElapsedTimes(void);
void printElapsedTimes(void);
double averageElapsedTime(void);

#endif