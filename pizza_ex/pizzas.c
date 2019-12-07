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


int main(int argc, char* argv[]) {
	int semid, shmid, i;
	unsigned short final_values[3];
	key_t key;
	
	if (argc != 1) {
		fprintf(stderr, "usage: %s\n", argv[0]);
		return -1;
	}
	
	if ( (key = ftok("/dev/null", 65)) == (key_t) -1 ) {
		perror(argv[0]);
		return -1;
	}
	
	if ( (semid = semget(key, 3, 0666 | IPC_CREAT)) < 0 ) {
		perror(argv[0]);
		return -1;
	}
/*
servings = 0
mutex = Semaphore (1)
emptyPot = Semaphore (0)
fullPot = Semaphore (0)
*/








	
	semctl(semid, MUTEX, SETVAL, 1);
	semctl(semid, NOPIZZA, SETVAL, 0);
	semctl(semid, PIZZA, SETVAL, 0);
	
	semctl(semid, 0, GETALL, final_values);
	for (i = 0; i < 3; i++) {
		printf("%3i", final_values[i]);
	}
	printf("\n");
	
	if ( (shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT)) < 0 ) {
		semctl(semid, 0, IPC_RMID, 0);
		perror(argv[0]);
		return -1;
	}
	
	return 0;
}
