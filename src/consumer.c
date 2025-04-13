#include "../include/consumer.h"
#include "../include/metrics.h"

void *consumer (void *q)
{
  queue *fifo = (queue *)q;

  while(1) {
    workFunction wf;
    struct timeval consumeTime;

    pthread_mutex_lock (fifo->mut);

    while (fifo->empty) {
      pthread_cond_wait (fifo->notEmpty, fifo->mut);
    }

    queueDel (fifo, &wf);
    pthread_mutex_unlock (fifo->mut);
    pthread_cond_signal (fifo->notFull);

    if(wf.work == NULL) {
      // Poison pill received, exit the loop
      break;
    }

    // Calculate the elapsed time since the product was added to the queue
    gettimeofday (&consumeTime, NULL);
    long sec = consumeTime.tv_sec - wf.produceTime.tv_sec;
    long usec = consumeTime.tv_usec - wf.produceTime.tv_usec;
    if (usec < 0) {
      usec += 1000000;
      sec -= 1;
    }
    double elapsed = sec + usec*1e-6;
    if (elapsed < 0) {
      elapsed = 0;
    }

    // Store the elapsed time in elapsedTimes array
    pthread_mutex_lock(&elapsedMutex);
    if(elapsedCounter < LOOP * PRODUCERS) {
      elapsedTimes[elapsedCounter++] = elapsed;
    }
    pthread_mutex_unlock(&elapsedMutex);

    // Execute the work function
    wf.work(wf.arg);
  }

  return (NULL);
}