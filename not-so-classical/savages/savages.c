#include "header.h"

void a_consumer()
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
	k = 10;
	// while  True:
	// 	mutex.wait()
	// 		if  servings  == 0:
	// 			emptyPot.signal ()
	// 			fullPot.wait()
	// 			servings = M
	// 		servings  -= 1
	// 		getServingFromPot ()
	// 	mutex.signal ()
	// 	eat()

	b = (struct buffer *)shmat(shmid, (void *)0, 0);

	while (1)
	{
		sem_wait(semid, MUTEX, 1); ///  1,0
		printf("Savage %i has accessed the buffer... %i \n", getpid(), b->value);

		if (b->value == 0)
		{
			printf("Se sirve \n");
			sem_signal(semid, EMPTY, 1); ///  1,0
			sem_wait(semid, FULL, 1);	///  1,0
			// b->value = nP;
		}
		b->value -= 1;
		printf("\n Left portions: %i \n ", b->value);
		sem_signal(semid, MUTEX, 1); ///  1,0
		printf("Eats \n");
		sleep(1);
	}

	shmdt(b);
	exit(0);
}

int main(int argc, char *argv[])
{
	int amount = 0, semid, i, pid, pot;
	key_t key;

	if (argc != 2)
	{
		printf("usage: %s amountSavages \n", argv[0]);
		return -1;
	}

	amount = atoi(argv[1]);
	if (amount <= 0)
	{
		printf("%s: The amount must be a positive number\n", argv[0]);
		return -1;
	}



	for (i = 0; i < amount; i++)
	{
		if ((pid = fork()) < 0)
		{
			perror("fork");
			return -1;
		}
		else if (pid == 0)
		{
			a_consumer();
		}
		else
		{
		}
	}
	return 0;
}
