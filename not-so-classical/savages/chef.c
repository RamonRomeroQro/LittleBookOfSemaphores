#include "header.h"

void a_producer(nP)
{
	int semid, shmid, i, j, k, size;
	key_t key;
	struct buffer *b;

	if ((key = ftok("/dev/null", 65)) == (key_t)-1)
	{
		perror("ftok");
		exit(-1);
	}

	if ((semid = semget(key, 3, 0666)) < 0) // NUMERO DE SEMAFOROS
	{
		perror("semget");
		exit(-1);
	}

	if ((shmid = shmget(key, sizeof(struct buffer), 0666)) < 0)
	{
		perror("shmid");
		exit(-1);
	}
	

	srand(getpid());

	// while  True:
	// 	emptyPot.wait()
	// 	putServingsInPot (M)
	// 	fullPot.signal ()

	k = 10;
	b = (struct buffer *)shmat(shmid, (void *)0, 0);

	while (1)
	{
		sem_wait(semid, EMPTY, 1);
		b->value = nP;
		sem_signal(semid, FULL, 1);
		printf("Chef fills the pot...\n");


	}

	shmdt(b);
	exit(0);
}

int main(int argc, char *argv[])
{
	int numPortions, semid, i, pid;
	key_t key;

	if (argc != 2)
	{
		printf("usage: %s amountPortions \n", argv[0]);
		return -1;
	}

	numPortions = atoi(argv[1]);
	if (numPortions <= 0)
	{
		printf("%s: The amount must be a positive number \n", argv[0]);
		return -1;
	}

	if ((pid = fork()) < 0)
	{
		perror("fork");
		return -1;
	}
	else if (pid == 0)
	{
		a_producer(numPortions);
	}
	else
	{
	}

	return 0;
}
