#ifndef CONSUMER_H
#define CONSUMER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "config.h"
#include "queue.h"

void *consumer (void *args);

#endif