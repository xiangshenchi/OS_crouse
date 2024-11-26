#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct Student {
    int Id;
    char Name[87];
    ushort Age;
};

int main()
{
    int fd1;

    // FIFO file path
    char * myfifo = "/tmp/myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>,<permission>)
    mkfifo(myfifo, 0666);

    //char str1[80], str2[80];
    struct Student s1,s2;
    while (1)
    {
        // First open in read only and read
        fd1 = open(myfifo,O_RDONLY);
        read(fd1, &s1, sizeof(s1));

        // Print the read string and close
        //printf("User1: %s\n", str1);
        close(fd1);
        
		printf("Received: Id=%d, Name=%s, Age=%hu\n", s1.Id, s1.Name, s1.Age);

        s2 = s1;
        s2.Id++;
        s2.Age++;

        // Now open in write mode and write
        // string taken from user.
        fd1 = open(myfifo, O_WRONLY);
        write(fd1, &s2, sizeof(s2));
        close(fd1);

        if (s2.Id >= 100) break;
    }
    return 0;
}
