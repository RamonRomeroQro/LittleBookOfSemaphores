#include "header.h"

int main(int argc, char* argv[]) {
	int semid, shmid, i;
	unsigned short final_values[5];
	key_t key;
	
	if (argc != 2) {
		fprintf(stderr, "usage: %s cantidad_sillas \n", argv[0]);
		return -1;
	}
	
	if ( (key = ftok("/dev/null", 100)) == (key_t) -1 ) {
		perror(argv[0]);
		return -1;
	}
	
	if ( (semid = semget(key, 5, 0666 | IPC_CREAT)) < 0 ) {
		perror("semget");
		return -1;
	}

	int p_sillas=atoi(argv[1]);

	if (p_sillas<1){
		fprintf(stderr, "debe de ser un numero positivo\n" );
				return -1;

	}



	//n = 4
	//customers = 0
	//mutex = Semaphore (1)
	//customer = Semaphore (0)
	//barber = Semaphore (0)
	//customerDone = Semaphore (0)
	//barberDone = Semaphore (0)
	//0== nadie lo va a poder adquirir, almenos uno puedo entrar

semctl(semid, MUTEX, SETVAL, 1);
semctl(semid, CLIENTE, SETVAL, 0);
semctl(semid, BARBERO, SETVAL, 0);
semctl(semid,CLIENTEHECHO, SETVAL, 0);
semctl(semid, BARBEROHECHO, SETVAL, 0);
	
	
	semctl(semid, 0, GETALL, final_values);
	for (i = 0; i < 5; i++) {
		printf("%i  ", final_values[i]);
	}
	printf("\n");


	
	if ( (shmid = shmget(key, sizeof(Salon), 0666 | IPC_CREAT)) < 0 ) {
		semctl(semid, 0, IPC_RMID, 0);
		perror(argv[0]);
		return -1;
	}

	Salon *s;
	s = (Salon*) shmat(shmid, (void*) 0, 0);
	s->tamanio = p_sillas;
	s->clientes = 0;

	fprintf(stdout, "numero de sillas: %i\n", s->tamanio);
	printf("numero de clientes %i\n", s->clientes);
					
	shmdt(s);
	
	return 0;
}
