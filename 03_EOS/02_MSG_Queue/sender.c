// To send Data of "stdio.h" to receiver.
// Receiver will count number of "s" in the file.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mqueue.h>
#include <errno.h>

#define MAXSIZE 8192 // MAXIMUM DEFAULT QUEUE SIZE = 8Kb
unsigned char buff[MAXSIZE];

mqd_t mqd;
struct mq_attr attr;

int main(int argc, char const *argv[])
{

    // Default size of queue is 8Kb. so we need to send the data 4times.
    // size of file "stdio.h" is 31176 bytes. i.e around 32Kb

    attr.mq_flags = 0;
    attr.mq_maxmsg = 4;
    attr.mq_msgsize = 8192;
    attr.mq_curmsgs = 0;

    mqd = mq_open("/stdio_mq", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &attr);
    if (-1 == mqd)
    {
        perror("Message Queue not created.\n");
        printf("Error No.%d\n", errno);
        exit(EXIT_FAILURE);
    }
    int fd = open("/usr/include/stdio.h", O_RDONLY, S_IRUSR | S_IWUSR);
    if (-1 == fd)
    {
        perror("File not opened.\n");
        printf("Error No.%d\n", errno);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 4; i++)
    {
        ssize_t sender = read(fd, buff, sizeof(buff));
        if (sender == -1)
        {
            perror("File not opened.\n");
            printf("Error No.%d\n", errno);
            exit(EXIT_FAILURE);
        }

        if (mq_send(mqd, (const char *)&buff, MAXSIZE, 0) == -1)
        {
            perror("Error in sending file.\n");
            printf("Error No.%d\n", errno);
            exit(EXIT_FAILURE);
        }
        printf("File Sent Successfully. Total Size %ld \n", sender);
    }
    mq_close(mqd);
    return 0;
}