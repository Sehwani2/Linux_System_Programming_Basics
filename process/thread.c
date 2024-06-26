#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_TRY 	100000000
int shared = 0;
pthread_mutex_t mutex;

void* child_thread_main(void* arg)
{
	int i;
	printf("pthread_ id(%lu)\n",pthread_self());
	
	pthread_mutex_lock(&mutex);
	for(i=0; i< MAX_TRY; i++){
		shared++;
	}
	for(i=0; i< MAX_TRY; i++){
		shared--;
	}
	pthread_mutex_unlock(&mutex);

	return NULL;
}


int main(int argc, char** argv)
{	
	int ret;
	pthread_t child_threads[2];
	
	if(pthread_mutex_init(&mutex,NULL)){
		printf("mytex init fail\n");
		return -1;
	}

	printf("main pthread_ id(%lu)\n",pthread_self());	
	ret = pthread_create(&child_threads[0],NULL,child_thread_main,NULL);	
	if(ret){
		printf("pthread_create() fail(%d)\n",ret);
		return -1;
	}
	ret = pthread_create(&child_threads[1],NULL,child_thread_main,NULL);
        if(ret){
                printf("pthread_create() fail(%d)\n",ret);
                return -1;
        }
	
	printf("trying to join %lu \n",child_threads[0]);
	if(pthread_join(child_threads[0],NULL)){
		printf("pthread_join(%lu) fail\n",child_threads[0]);
	}

	printf("trying to join %lu \n",child_threads[1]);
	if(pthread_join(child_threads[1],NULL)){
                printf("pthread_join(%lu) fail\n",child_threads[1]);
        }

	printf("shared = %d\n",shared);
	printf("Done\n");


	return 0;
}

