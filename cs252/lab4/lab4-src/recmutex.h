#include <pthread.h>


/*
 * The recursive_mutex structure. 
*/

struct recursive_mutex {

  pthread_cond_t    cond;

  pthread_mutex_t   mutex; //a non-recursive pthread mutex

  pthread_t         owner;

  unsigned int      count;

  unsigned int      wait_count;

};



typedef struct recursive_mutex  recursive_mutex_t;


/* Initialize the recursive mutex object. 
 *Return a non-zero integer if errors occur. 
 */

int recursive_mutex_init (recursive_mutex_t *mu);


/* Destroy the recursive mutex object. 
 *Return a non-zero integer if errors occur.
 */

int recursive_mutex_destroy (recursive_mutex_t *mu);


/* The recursive mutex object referenced by mu shall be 
   locked by calling pthread_mutex_lock(). When a thread 
   successfully acquires a mutex for the first time, 
   the lock count shall be set to one and successfully return. 
   Every time a thread relocks this mutex, the lock count 
   shall be incremented by one and return success immediately. 
   And any other calling thread can only wait on the conditional 
   variable until being waked up. Return a non-zero integer if errors occur. 
*/
int recursive_mutex_lock (recursive_mutex_t *mu);


/* The recursive_mutex_unlock() function shall release the 
  recursive mutex object referenced by mu. Each time the owner 
  thread unlocks the mutex, the lock count shall be decremented by one. 
  When the lock count reaches zero, the mutex shall become available 
  for other threads to acquire. If a thread attempts to unlock a 
  mutex that it has not locked or a mutex which is unlocked, 
  an error shall be returned. Return a non-zero integer if errors occur. 
*/

int recursive_mutex_unlock (recursive_mutex_t *mu);
