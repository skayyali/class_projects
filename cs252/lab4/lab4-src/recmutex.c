#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include "recmutex.h"


int recursive_mutex_init (recursive_mutex_t *mu)
{
	int err;
	err = pthread_mutex_init(&mu->mutex, NULL);
	mu->count = 0;
	//mu->owner=pthread_self();
	
	if(err !=0)
	{
		perror("pthread_mutex_init");
		return -1;
	}
	else{
		return 0;
	}
}

int recursive_mutex_destroy (recursive_mutex_t *mu)
{
	int err;
	err = pthread_mutex_destroy(&mu->mutex);
	if(err != 0){
		perror("pthread_mutex_destroy");
		return -1;
	}
	else{
		return 1;
	}
}

int recursive_mutex_lock (recursive_mutex_t *mu)
{
	if(mu->count == 0){
		pthread_mutex_lock(&mu->mutex);
		mu->count=1;
		mu->owner = pthread_self();
	}
	if(mu->count > 0){ //mutex locked
		if(pthread_equal(mu->owner, pthread_self())){
			mu->count++;
		}
		else{
			//wait
			while(&(mu->count) != 0){
				printf("count:%d\n", &(mu->count));
				int res = pthread_cond_wait(&(mu->cond), &(mu->mutex));
				
			}
			pthread_mutex_lock(&mu->mutex);
			mu->count=1;
			mu->owner = pthread_self();
			
		}
	}
	return 0;
}

int recursive_mutex_unlock (recursive_mutex_t *mu)
{
	if(mu->count == 0){
		//nothing to unlock
		printf("NOTHING TO UNLOCK, EXITING\n");
		return -1;
		
	}
	else if (mu->count == 1){
		//normal unlock
		int error = pthread_cond_signal(&(mu->cond));
		int unlock = pthread_mutex_unlock(&(mu->mutex));
		//int error = pthread_cond_signal(&(mu->cond));
		
	}
	else if (mu->count >1){
		if(pthread_equal(mu->owner, pthread_self())){
			mu->count--;
		}
	}
	return 0;
}
