#include  <stdio.h>
#include  <stdlib.h>
#include <unistd.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>

#include "utils.h" 
#include <pthread.h> 
#include <semaphore.h>

/* Shared Memory Global Variables */
key_t          shmKey;
int            shmId;
void          *shmPtr;
void shmInit()
{
    shmKey = ftok(".", 'x');
    shmId = shmget(shmKey, sizeof(int)*3 + sizeof(struct Product) * BUFFER_SIZE, 0666);
    if (shmId < 0) {
        printf("*** shmget error (consumer) ***\n");
        exit(1);
    }

    printf("Consumer has received a shared memory.\n");

    shmPtr = shmat(shmId, NULL, 0);

    if ((int) shmPtr == -1) {
        printf("*** shmat error (client) ***\n");
        exit(1);
    }
}

void shmClean()
{
     shmdt((void *) shmPtr);
     printf("Consumer has detached its shared memory...\n");
     printf("Consumer exits...\n");
}

/* Shared Memory Layout */
/*
*    | counter[0] | counter[1] | flag[PRODUCER] | flag[CONSUMER] | turn | status | Product[0] | Product[1] |......| Product[99] |
*/

void  main(void)
{
     struct Product *buffer;
     int           *counter;
     int           *status;

     int out = 0;

     struct Product next_consumed;
     
     shmInit();

     counter = (int*)shmPtr;
     status = counter + 2;

     buffer = (struct Product*)(status + 1);

     printf("Counter:%d\t%d\n",counter[0],counter[1]);
     printf("Consumer has attached the shared memory...\n");

     if( *status == STATUS_READY )
    *status = STATUS_RUNNING;

     while(TRUE)
     {
         while( counter[0] == 0 )
             ;
         next_consumed = buffer[ out ];
         out = (out + 1) % BUFFER_SIZE;

         counter[0]--;
         counter[1]--;

         printf("Consume the Product:\n\tId:%d\n\tName:%s\n\tValue:%d\n",
                next_consumed.Id,
                next_consumed.Name,
                next_consumed.Value);

     if(counter[0] != counter[1])
     {
             *status = STATUS_COMPLETE;
             printf("counter[0]=%d\tcounter[1]=%d\n", counter[0], counter[1]);
         break;
         }

     }

     shmClean();

     exit(0);
}

