#include "../include/metrics.h"

double *elapsedTimes = NULL;
int elapsedCounter = 0;
pthread_mutex_t elapsedMutex = PTHREAD_MUTEX_INITIALIZER;

void initializeElapsedTimes(int size) {
  elapsedTimes = (double *)malloc(size * sizeof(double));
  if (elapsedTimes == NULL) {
      fprintf(stderr, "Failed to allocate memory for elapsedTimes.\n");
      exit(1);
  }
}

void freeElapsedTimes(void) {
  free(elapsedTimes);
}

void printElapsedTimes(void) {
  for(int i=0; i<elapsedCounter; i++) {
    printf("%d : %f sec\n", i, elapsedTimes[i]);
  }
}

double averageElapsedTime(void) {
  double sum = 0.0;
  for(int i=0; i<elapsedCounter; i++) {
    sum += elapsedTimes[i];
  }
  return sum / elapsedCounter;
}