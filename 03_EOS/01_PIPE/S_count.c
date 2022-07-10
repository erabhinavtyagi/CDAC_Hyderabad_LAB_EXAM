//Count Number of "S" in stdio.h - Using PIPE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAXSIZE 81920            // 80Kb 

char buff[MAXSIZE];

int main(int argc, char const *argv[])
{
    int fd[2];
    pid_t id;
    char buff_rec[MAXSIZE];

    pipe(fd);
   
    int fdr = open("/usr/include/stdio.h", O_RDONLY, S_IRUSR | S_IWUSR);
    if (-1 == fdr)
    {
        perror("Can't Open file fd1.\n");
        exit(EXIT_FAILURE);
    }
    
    id = fork();
// In Parent process P1
    if ( 0 < id)
    {   
        if(read(fdr,buff,sizeof(buff)) == -1)
        {
            perror("Error in Reading File in Process P1");
            exit(EXIT_FAILURE); 
        }
        
        // fd[0] = To read, fd[1] = To write, 
        if(write(fd[1],buff,sizeof(buff)) == -1)
        {
            perror("Error in Writing File in Process P1");
            exit(EXIT_FAILURE); 
        }
    }

//In Child Process P2
    if ( 0 == id)
    {
        int num;
        int count =0;
        
        if(read(fd[0], &buff_rec, sizeof(buff_rec)) == -1)
        {
            perror("Error in Reading File in Process P2");
            exit(EXIT_FAILURE);
        }
        
        for (int i =0; i<=strlen(buff_rec); i++)
        {
            if (buff_rec[i] == 's')
            count++;
        }
        printf("\nS comes %d times in stdio.h \n", count);
    }

    close(fd[0]);
    close(fd[1]);
    return 0;
}