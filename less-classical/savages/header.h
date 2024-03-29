#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define MUTEX 		0
#define EMPTY		1
#define	FULL 		2


struct buffer {
	int value;
};


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

#endif
