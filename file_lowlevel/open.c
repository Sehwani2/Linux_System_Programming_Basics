#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int trunc_file(void)
{
	int fd;

	fd = open("datafile",O_WRONLY | O_CREAT | O_TRUNC,0644);
	if(fd == -1){
		printf("open() error\n");
		return -1;
	}

	dprintf(fd,"byeybye\n");

	close(fd);
	return 0;
}

static int append_file(void)
{
        int fd;

        fd = open("datafile",O_WRONLY | O_APPEND);
        if(fd == -1){
                printf("open() error\n");
                return -1;
        }

        dprintf(fd,"HELLO AGAIN\n");

        close(fd);
        return 0;
}


static int write_file(void)
{
	int fd;
	fd = open("datafile",O_WRONLY | O_CREAT,0644);
	if(fd == -1){
		printf("open() error\n");
		return -1;
	}
	dprintf(fd,"Hello world");

	close(fd);
	return 0;
}


int main(int argc, char** argv)
{
	if(write_file()){
		printf("write_file() error\n");
		return -1;
	}
	 if(trunc_file()){
                printf("turnc_file() error\n");
                return -1;
        }
	
	if(append_file()){
                printf("append_file() error\n");
                return -1;
        }

	return 0;
}

