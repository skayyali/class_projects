#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include "recmutex.h"

//argument structure for the thread
typedef struct _arg_{
    int n1;
    int n2;
    int ntimes;
}Arg;

int count; //global counter
recursive_mutex_t mutex; //the recursive mutex

void do_inc(int n){
    int ret;
    if(n == 0){	
	return;
    }else{
	int c;
	ret = recursive_mutex_lock(&mutex);
	assert(ret == 0);
	c = count;
	c = c + 1;
	count = c;
	do_inc(n - 1);
	ret = recursive_mutex_unlock(&mutex);
	assert(ret == 0);
    }
}

/*  Counter increment function. It will increase the counter by n1 * n2 * ntimes. */
void inc(void *arg){
    Arg * a = (Arg *)arg;
    for(int i = 0; i < a->n1; i++){
	for(int j = 0; j < a->n2; j++){
	    do_inc(a->ntimes);
	}
    }
}

int isPositiveInteger (const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
            return 0;
    char * p;
    int ret = strtol (s, &p, 10);
    if(*p == '\0' && ret > 0)
	return 1;
    else
	return 0;
}


int test1(char **argv){

    printf("==========================Test 1===========================\n");
    int ret;
    //Get the arguments from the command line.
    int num_threads = atoi(argv[1]); //The number of threads to be created.
    int n1 = atoi(argv[2]);          //The outer loop count of the inc function.
    int n2 = atoi(argv[3]);          //The inner loop count of the inc function.
    int ntimes = atoi(argv[4]);      //The number of increments to be performed in the do_inc function.
    
    pthread_t *th_pool = new pthread_t[num_threads];
    pthread_attr_t attr;
    pthread_attr_init( &attr );
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    ret = recursive_mutex_init(&mutex);
    assert(ret == 0);

    printf("Start Test. Final count should be %d\n", num_threads * n1 * n2 * ntimes );

    // Create threads
    for(int i = 0; i < num_threads; i++){
	Arg *arg = (Arg *)malloc(sizeof(Arg));
	arg->n1 = n1;
	arg->n2 = n2;
	arg->ntimes = ntimes;
	ret = pthread_create(&(th_pool[i]), &attr, (void * (*)(void *)) inc, (void *)arg);
	assert(ret == 0);
    }
    
    // Wait until threads are done
    for(int i = 0; i < num_threads; i++){
	ret = pthread_join(th_pool[i], NULL);
	assert(ret == 0);
    }
    
    if ( count != num_threads * n1 * n2 * ntimes) {
	printf("\n****** Error. Final count is %d\n", count );
	printf("****** It should be %d\n", num_threads * n1 * n2 * ntimes );
    }
    else {
	printf("\n>>>>>> O.K. Final count is %d\n", count );
    }

    ret = recursive_mutex_destroy(&mutex);
    assert(ret == 0);

    delete [] th_pool;
    return 0;
}


int foo(){
    int ret;
    printf("Function foo\n");
    ret = recursive_mutex_unlock(&mutex);
    assert(ret != 0);
    return ret;
}

//test a thread call unlock without actually holding it.
int test2(){
    int ret;
    printf("\n==========================Test 2==========================\n");
    pthread_t th;
    pthread_attr_t attr;
    pthread_attr_init( &attr );
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    ret = recursive_mutex_init(&mutex);
    ret = pthread_create(&th, &attr, (void * (*)(void *))foo, NULL);
    
    printf("Waiting for thread to finish\n");
    ret = pthread_join(th, NULL);
    assert(ret == 0);
    return 0;
}


int main( int argc, char ** argv )
{
    int ret;
    count = 0;
    
    if( argc != 5 ) {
	printf("You must enter 4 arguments. \nUsage: ./count_recursive num_threads n1 n2 ntimes\n");
	return -1;
    }
    
    if(isPositiveInteger(argv[1]) != 1 || isPositiveInteger(argv[2]) != 1 || isPositiveInteger(argv[3]) != 1 || isPositiveInteger(argv[4]) != 1 ){
	printf("All the 4 arguments must be positive integers\n");
	return -1;
    }

    test1(argv);

    test2();

    return 0;
}




