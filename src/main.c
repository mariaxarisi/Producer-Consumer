#include "../include/config.h"
#include "../include/queue.h"
#include "../include/consumer.h"
#include "../include/producer.h"
#include "../include/metrics.h"

int PRODUCERS = 0;
int CONSUMERS = 0;

int main (int argc, char *argv[]){

  if (argc != 3) {
      fprintf(stderr, "Usage: %s <producers> <consumers>\n", argv[0]);
      return 1;
  }

  PRODUCERS = atoi(argv[1]);
  CONSUMERS = atoi(argv[2]);
  
  queue *fifo;
  pthread_t *producers, *consumers;
  producers = (pthread_t *) malloc (PRODUCERS * sizeof(pthread_t));
  consumers = (pthread_t *) malloc (CONSUMERS * sizeof(pthread_t));
  initializeElapsedTimes(LOOP * PRODUCERS);

  fifo = queueInit ();
  if (fifo ==  NULL) {
    fprintf (stderr, "main: Queue Init failed.\n");
    exit (1);
  }
  
  for (int i = 0; i < PRODUCERS; i++) {
    pthread_create(&producers[i], NULL, producer, fifo);
  }
  for (int i = 0; i < CONSUMERS; i++) {
    pthread_create(&consumers[i], NULL, consumer, fifo);
  }

  for (int i = 0; i < PRODUCERS; i++) {
    pthread_join(producers[i], NULL);
  }

  // Poison pills for consumers
  for (int i = 0; i < CONSUMERS; i++) {
    workFunction wf;
    wf.work = NULL;
    wf.arg = NULL;
    gettimeofday (&wf.produceTime, NULL);

    pthread_mutex_lock(fifo->mut);
    while (fifo->full) {
      pthread_cond_wait (fifo->notFull, fifo->mut);
    }
    queueAdd(fifo, wf);
    pthread_mutex_unlock(fifo->mut);
    pthread_cond_signal(fifo->notEmpty);
  }

  for (int i = 0; i < CONSUMERS; i++) {
    pthread_join(consumers[i], NULL);
  }

  queueDelete (fifo);

  //printElapsedTimes();
  double avgTime = averageElapsedTime();
  printf("Producers: %d, Consumers: %d, Average Time: %f sec\n", PRODUCERS, CONSUMERS, avgTime);

  return 0;
}
