#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>

#include <pthread.h>
#include "utils.h"
#include <semaphore.h>

/* Global Shared Memory Variables */
key_t shmKey;
int   shmId;
void *shmPtr;

void shmInit()
{
     shmKey = ftok(".", 'x');

     shmId = shmget(shmKey, sizeof(int)*3  + sizeof(struct Product) * BUFFER_SIZE, IPC_CREAT | 0666);
     
     if (shmId < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }
     
     printf("Produce create a buffer of size %d.\n", BUFFER_SIZE);
     
     shmPtr =  shmat(shmId, NULL, 0);
     if ((int) shmPtr == -1) {
          printf("*** shmat error (Producer) ***\n");
          exit(1);
     }
}

void shmClean()
{
     shmdt((void *) shmPtr);
     printf("Producer has detached its shared memory...\n");
     shmctl(shmId, IPC_RMID, NULL);
     printf("Producer has removed its shared memory...\n");
     printf("Producer exits...\n");
}

void  main(int  argc, char *argv[])
{

    struct Product  *buffer;
    int* counter;
    int  in = 0;

    int* status;

    struct Product product;
    int productId = 1;

    shmInit();

/* Shared Memory Layout */
/*
*    | counter[0] | counter[1] | status | Product[0] | Product[1] |......| Product[99] |
*/
    counter = (int*)shmPtr;
    status = counter + 2;

    buffer = (struct Product*)(status + 1);

    printf("Initialize shared variables...\n");
    counter[0]=0;
    counter[1]=0;

    *status = STATUS_READY;

    while(TRUE)
    {
        if( *status == STATUS_COMPLETE )
        {
            printf("Consumer exit.\n");
            break;
        }

        /* produce a new product */
        product.Id = productId++;
        sprintf(product.Name, "N:%d",product.Id);
        product.Value = product.Id;
        printf("Produced new product %d\n", product.Id);

        while(counter[0] == BUFFER_SIZE)
            ;

        buffer[in] = product;
        in = (in + 1) % BUFFER_SIZE;

        counter[0] ++;
        counter[1] ++;
    }

    shmClean();

    exit(0);
}

