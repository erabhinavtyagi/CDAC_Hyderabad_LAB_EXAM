// To Receive Data of "stdio.h" from sender and print number of "s" in the file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mqueue.h>
#include <errno.h>

#define MAXSIZE 8192 // MAXIMUM DEFAULT QUEUE SIZE = 8Kb

mqd_t mqd;

struct mq_attr attr;

int main(int argc, char const *argv[])
{
    int fd, count = 0;
    unsigned int prio;
    unsigned char buff[MAXSIZE];

    attr.mq_flags = 0;
    attr.mq_maxmsg = 4;
    attr.mq_msgsize = 8192;
    attr.mq_curmsgs = 0;

    mqd = mq_open("/stdio_mq", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, &attr);

    for (int i = 0; i < 4; i++)
    {
        ssize_t rec = mq_receive(mqd, buff, MAXSIZE, &prio);

        printf("Received %ld bytes\n", rec);

        if (rec == -1)
        {
            perror("Error in Receiving file.\n");
            printf("Error No.%d\n", errno);
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i <= strlen(buff) + 1; i++)
        {
            if (buff[i] == 's')
                count++;
        }
    }
    printf("\nS comes %d times in stdio.h \n", count);

    mq_close(mqd);
    return 0;
}