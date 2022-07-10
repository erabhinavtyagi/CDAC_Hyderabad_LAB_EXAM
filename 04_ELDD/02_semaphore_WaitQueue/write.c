#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

unsigned char buff[50];

int main(int argc, char const *argv[])
{
    int fd;
    fd = open("/dev/writedriver", O_RDWR);
    if(fd == -1)
    {
        perror("Error in opening device file :");
        exit(EXIT_FAILURE);
    }
    else
    {
        ssize_t rd_ret;
        printf("Enter a String to write :");
        scanf("%[^\n]s", buff);
        rd_ret = write(fd, buff, sizeof(buff));
        if(rd_ret == -1)
        {
            perror("Error in writing... :");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Write Successfull...\n");
        }
    }
    return 0;
}