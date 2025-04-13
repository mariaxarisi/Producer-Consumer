#include "../include/config.h"
#include "../include/queue.h"
#include "../include/consumer.h"
#include "../include/producer.h"

int main ()
{
  queue *fifo;
  pthread_t pro, con;

  fifo = queueInit ();
  if (fifo ==  NULL) {
    fprintf (stderr, "main: Queue Init failed.\n");
    exit (1);
  }
  pthread_create (&pro, NULL, producer, fifo);
  pthread_create (&con, NULL, consumer, fifo);
  pthread_join (pro, NULL);
  pthread_join (con, NULL);
  queueDelete (fifo);

  return 0;
}
