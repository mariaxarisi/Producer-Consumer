#include "../include/producer.h"
#include <math.h>

void *calculateSine(void *arg) {
  double *angles = (double *)arg;
  for(int i=0; i<10; i++) {
    angles[i] = sin(angles[i]);
  }
  free(arg);
  return (NULL);
}

void *producer (void *q)
{
  queue *fifo = (queue *)q;

  for (int i = 0; i < LOOP; i++) {

    // Create a work function
    workFunction wf;
    wf.work = calculateSine;

    // Create arguments for the work function
    double *arg = (double *)malloc(sizeof(double)*10);
    for (int j = 0; j < 10; j++) {
      arg[j] = i + j * 0.1;
    }
    wf.arg = arg;

    pthread_mutex_lock (fifo->mut);

    while (fifo->full) {
      pthread_cond_wait (fifo->notFull, fifo->mut);
    }

    // Get the current time and add product to the queue
    gettimeofday (&wf.produceTime, NULL);
    queueAdd (fifo, wf);

    pthread_mutex_unlock (fifo->mut);
    pthread_cond_signal (fifo->notEmpty);
  }

  return (NULL);
}