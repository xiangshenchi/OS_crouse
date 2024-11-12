#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
#define NUM_THREADS 5 
 
typedef struct _thread_data_t 
{
  int tid;
  double stuff;
} thread_data_t;
 
double shared_x;
pthread_mutex_t lock_x;
 
void *thr_func(void *arg) 
{
  thread_data_t *data = (thread_data_t *)arg;
 
  printf("hello from thr_func, thread id: %d\n", data->tid);

  pthread_mutex_lock(&lock_x);
    shared_x += data->stuff;
    printf("x = %f\n", shared_x);
  pthread_mutex_unlock(&lock_x);
 
  pthread_exit(NULL);
}
 
int main(int argc, char **argv) 
{
  pthread_t thr[NUM_THREADS];
  int i, rc;
  /* ¿ýpÂppÄ */
  thread_data_t thr_data[NUM_THREADS];
 
  /* Ëq«ØÏ */
  shared_x = 0;
 
  /* Ë¥ */
  pthread_mutex_init(&lock_x, NULL);
 
  /* ú¿ */
  for (i = 0; i < NUM_THREADS; ++i) 
  {
    thr_data[i].tid = i;
    thr_data[i].stuff = (i + 1) * NUM_THREADS;
    if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) 
    {
      fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
      return EXIT_FAILURE;
    }
  }
  /* ;^I¿gLÓ_ */
  for (i = 0; i < NUM_THREADS; ++i) 
  {
    pthread_join(thr[i], NULL);
  }
 
  return EXIT_SUCCESS;
}
