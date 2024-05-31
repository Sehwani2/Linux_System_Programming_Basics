#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <dirent.h>

int main(int argc, char** argv)
{
	DIR* dp;
	struct dirent* entry;

	dp = opendir(".");
	if(!dp){
		printf("opendir() fail\n");
		return -1;
	}
	
	while((entry = readdir(dp))){
		printf("%s: %d\n",entry->d_name,entry->d_type);
	}

	closedir(dp);
	return 0;
}

