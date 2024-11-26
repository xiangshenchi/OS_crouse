#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct Student{
	int Id;
	char Name[87];
	ushort Age;
};
int main()
{
    int fd;

    // FIFO file path
    char * myfifo = "/tmp/myfifo";

    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(myfifo, 0666);

    struct Student s1,s2;
    while (1)
    {
        // Open FIFO for write only
        fd = open(myfifo, O_WRONLY);

        // Take an input arr2ing from user.
        // 80 is maximum length
        //fgets(arr2, 80, stdin);
		printf("Enter Student Id, Name, Age:\n");
        scanf("%d %s %hu", &s1.Id, s1.Name, &s1.Age);

        // Write the input arr2ing on FIFO
        // and close it
        write(fd, &s1, sizeof(s1));
        close(fd);

        // Open FIFO for Read only
        fd = open(myfifo, O_RDONLY);

        // Read from FIFO
        read(fd, &s2, sizeof(s2));

        // Print the read message
        //printf("User2: %s\n", arr1);
        close(fd);
        
		printf("Received: Id=%d, Name=%s, Age=%hu\n", s2.Id, s2.Name, s2.Age);
        if (s2.Id >= 100) break;
    }
    return 0;
}
