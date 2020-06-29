#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
 
#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N
 
int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };
int eaten[5];
int thinking[5];
time_t t;

sem_t mutex;
sem_t S[N];
int counter=0; 

void test(int phnum)
{
	//srand((unsigned) time(&t));
	int cond=1,i;
    if (state[phnum] == HUNGRY
        && state[LEFT] != EATING
        && state[RIGHT] != EATING) {
        // state that eating
        state[phnum] = EATING;
		if(counter<5)
			{
				eaten[counter]=phnum;
				counter++;
			} 
        sleep(2);
 
        //printf("Philosopher %d takes fork %d and %d\n",
        //              phnum + 1, LEFT + 1, phnum + 1);
 
        printf("Philosopher %d is now Eating\n", phnum + 1);
 
        // sem_post(&S[phnum]) has no effect
        // during takefork
        // used to wake up hungry philosophers
        // during putfork
        sem_post(&S[phnum]);
    }
    else
    	{	
    		for(i=0;i<counter+1;++i)
    			if (eaten[i]==phnum)
    				cond=0;
    		if(cond)
				printf("Philosopher %d can't pick up forks and start waiting\n", phnum + 1);
    	}
}
 
// take up chopsticks
void pickup_forks(int phnum)
{
 
    sem_wait(&mutex);
 
    // state that hungry
    state[phnum] = HUNGRY;
 
    printf("Philosopher %d is now Hungry and trying to pick up forks\n", phnum + 1);
 
    // eat if neighbours are not eating
    test(phnum);
 
    sem_post(&mutex);
 
    // if unable to eat wait to be signalled
    sem_wait(&S[phnum]);
 
    sleep(1);
}
 
// put down chopsticks
void return_forks(int phnum)
{
 
    sem_wait(&mutex);
 	int j;
    // state that thinking
    state[phnum] = THINKING;
 
    ///printf("Philosopher %d putting fork %d and %d down\n",
       //    phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d returns forks and then starts TESTING %d and %d\n", phnum + 1,LEFT + 1,RIGHT + 1);
 
    test(LEFT);
    test(RIGHT);
 
    sem_post(&mutex);
    //sleep(j);
}
 
void* philospher(void* num)
{
    int* i = num;
    int j;
    //srand((unsigned) time(&t));
    j=thinking[*i];
    printf("Philosopher %d is now thinking for %d seconds.\n", *i+1, j);
	sleep(j);
    pickup_forks(*i);
    //j=rand() % 3 + 1;
    sleep(0);
    return_forks(*i);
 
}
 
int main()
{
 
    int i,j,co=0;
    pthread_t thread_id[N];
 	srand((unsigned) time(&t));
    // initialize the semaphores
    sem_init(&mutex, 0, 1);
 
    for (i = 0; i < N; i++)
 
        sem_init(&S[i], 0, 0);
 
    for (i = 0; i < N; i++) {
 
        // create philosopher processes
        j=rand()%3 + 1;
        thinking[co++]=j;
        //printf("Philosopher %d is now thinking for %d seconds\n", i + 1,j);
        //sleep(j);
        pthread_create(&thread_id[i], NULL,
                       philospher, &phil[i]);
 
    }
 
    for (i = 0; i < N; i++)
 
        pthread_join(thread_id[i], NULL);
}
