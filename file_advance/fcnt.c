#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char** argv)
{
	char buf[128];
	int ret;
	int flag;

	printf("trying to read....\n");
	memset(buf,0,sizeof(buf));
	ret = read(STDIN_FILENO,buf,sizeof(buf));
	printf("read() [%s] - %d bytes\n",buf,ret);
	
	flag = fcntl(STDIN_FILENO,F_GETFL);
	if(flag == -1){
		printf("fcnt(F_GETFL) fail\n");
		return -1;
	};

	ret = fcntl(STDIN_FILENO,F_SETFL,flag | O_NONBLOCK);
	if(ret == -1){
		printf("fcntl(F_SETFL) fail\n");
		return -1;
	}

	printf("trying to read....\n");
        memset(buf,0,sizeof(buf));
        ret = read(STDIN_FILENO,buf,sizeof(buf));
        printf("read() [%s] - %d bytes\n",buf,ret);
	if(ret == -1){
		printf("errno: %d. %s\n",errno,strerror(errno));
	}

	return 0;
}
