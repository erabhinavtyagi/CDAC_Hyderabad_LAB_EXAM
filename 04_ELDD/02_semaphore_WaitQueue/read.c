#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

unsigned char buff[50];

int main(int argc, char const *argv[])
{
    int fd;
    fd = open("/dev/readdriver", O_RDWR);
    if(fd == -1)
    {
        perror("Error in opening device file :");
        exit(EXIT_FAILURE);
    }
    else
    {
        ssize_t rd_ret;
        rd_ret = read(fd, buff, sizeof(buff));
        if(rd_ret == -1)
        {
            perror("Error in reading... :");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Read Data: %s\n", buff);
        }
    }
    return 0;
}