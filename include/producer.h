#ifndef PRODUCER_H
#define PRODUCER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "config.h"
#include "queue.h"

void *producer (void *args);

#endif