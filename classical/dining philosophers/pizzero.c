#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define SIZE	10
#define MUTEX	0
#define NOPIZZA	1
#define PIZZA	2




int sem_wait(int semid, int semnum, unsigned int val) {
	struct sembuf op;
	
	op.sem_num = semnum;
	op.sem_op = -val;
	op.sem_flg = 0; 
	return semop(semid, &op, 1);
}

int sem_signal(int semid, int semnum, unsigned int val) {
	struct sembuf op;
	
	op.sem_num = semnum;
	op.sem_op = val;
	op.sem_flg = 0; 
	return semop(semid, &op, 1);
}


void a_producer(char* program, int amount) {
	int semid, shmid, i, j, k;
	int  *b;
	key_t key;
	
	if ( (key = ftok("/dev/null", 65)) == (key_t) -1 ) {
		perror(program);
		exit(-1);
	}
	
	if ( (semid = semget(key, 3, 0666)) < 0 ) {
		perror(program);
		exit(-1);
	}
	
	if ( (shmid = shmget(key, sizeof(int), 0666)) < 0 ) {
		perror(program);
		exit(-1);
	}
	b = (int*) shmat(shmid, (void*) 0, 0);
	
	srand( getpid() );
	while (1){

			sem_wait(semid, NOPIZZA, 1);
			*b=amount;
			fprintf(stderr, "%i\n", *b );
			sem_signal(semid, PIZZA, 1);

		
		sleep(1);
	}
	
	shmdt(b);
	exit(0);
}

int main(int argc, char* argv[]) {
	int amount, pid, i;
	
	if (argc != 2) {
		fprintf(stderr, "usage: %s rebanadas\n", argv[0]);
		return -1;
	}
	
	amount = atoi(argv[1]);
	if (amount < 1) {
		fprintf(stderr, "%s: The amount slices must be a positive number greater than zero.\n", argv[0]);
		return -1;
	}
	

			a_producer(argv[0], amount);
		
	
	return 0;
}
