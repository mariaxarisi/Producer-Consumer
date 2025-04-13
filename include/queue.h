#ifndef QUEUE_H
#define QUEUE_H

#include "config.h"
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct {
  void * (*work)(void *);
  void * arg;
  struct timeval produceTime;
} workFunction;

typedef struct {
  workFunction buf[QUEUESIZE];
  long head, tail;
  int full, empty;
  pthread_mutex_t *mut;
  pthread_cond_t *notFull, *notEmpty;
} queue;

queue *queueInit (void);
void queueDelete (queue *q);
void queueAdd (queue *q, workFunction in);
void queueDel (queue *q, workFunction *out);

#endif