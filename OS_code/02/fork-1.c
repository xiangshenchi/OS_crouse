
#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>

#define   MAX_COUNT  200
#define   BUF_SIZE   100

char MyStr[BUF_SIZE];

void  main(void)
{
     pid_t  pid;
     int    i;
     char   buf[BUF_SIZE];

     sprintf(MyStr,"%s\n","Hello World!");

     MyStr[4]='a';

     fork();

     pid = getpid();

     printf("MyStr:%s\n", MyStr);
     
     for (i = 1; i <= MAX_COUNT; i++) {
          sprintf(buf, "This line is from pid %d, value = %d\n", pid, i);
          write(1, buf, strlen(buf));
     } 
     
}

