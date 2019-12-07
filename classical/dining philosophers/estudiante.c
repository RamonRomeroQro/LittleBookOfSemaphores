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

void a_consumer(char* program) {
	int semid, shmid, i, j, k;
	int *b;
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
	*b=0;
	
	while (1){
		sem_wait(semid, MUTEX, 1);
		if (*b==0){
			fprintf(stderr, "NO PIZZA\n");
			sem_signal(semid, NOPIZZA, 1);
			sem_wait(semid, PIZZA, 1);
			//*b=10;
		}else{
			fprintf(stderr, "rebanadas: [ %i] \n", *b);

			fprintf(stderr, "come uno y estudia \n");
			*b-= 1;

		}
		sem_signal(semid, MUTEX, 1);



		sleep(1);
	}
	
	shmdt(b);
	exit(0);
}

int main(int argc, char* argv[]) {
	int amount, pid, i;
	
	if (argc != 2) {
		fprintf(stderr, "usage: %s amount\n", argv[0]);
		return -1;
	}
	
	amount = atoi(argv[1]);
	if (amount < 1) {
		fprintf(stderr, "%s: The amount students >0.\n", argv[0]);
		return -1;
	}
	
	for (i = 0; i < amount; i++) {
		if ( (pid = fork()) < 0 ) {
			perror(argv[0]);
			return -1;
		} else if (pid == 0) {
			a_consumer(argv[0]);
		} else {
			//do_nothing
		}
	}
	
	return 0;
}