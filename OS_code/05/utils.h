#define BUFFER_SIZE 100

#define TRUE  1
#define FALSE 0

/* Shared Memory Layout */
/*
*    | counter[0] | counter[1] | status | Product[0] | Product[1] |......| Product[99] |
*/

/* FLAGS For communication */
#define STATUS_READY    0
#define STATUS_RUNNING  1
#define STATUS_COMPLETE 2


#define PRODUCER 0
#define CONSUMER 1

struct Product
{
    int Id;
    char Name[32];
    int Value; 
};
