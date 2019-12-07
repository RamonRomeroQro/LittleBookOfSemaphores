#include "header.h"
int tiempo;

void a_cliente(char* program) {
	int semid, shmid, i, j, k;
	Salon *s;
	key_t key;
	
	if ( (key = ftok("/dev/null", 100)) == (key_t) -1 ) {
		perror(program);
		exit(-1);
	}
	
	if ( (semid = semget(key, 5, 0666)) < 0 ) {
		perror(program);
		exit(-1);
	}
	
	if ( (shmid = shmget(key, sizeof(Salon), 0666)) < 0 ) {
		perror(program);
		exit(-1);
	}
	s = (Salon*) shmat(shmid, (void*) 0, 0);
	
	for (k = 0; k < 10; k++) {

		sem_wait(semid, MUTEX, 1);


		if (s->clientes==s->tamanio){

			sem_signal(semid, MUTEX, 1);
			fprintf(stdout, "\nEl salon esta lleno, el cliente se va.\n");

		}

		else{

		s->clientes+=1;
		
		fprintf(stdout, "\nUn cliente entra al salon\n");

		fprintf(stdout, "\n# Clientes = %i \n", s->clientes);
		
		sem_signal(semid, MUTEX, 1);
		sem_signal(semid, CLIENTE, 1);
		sem_wait(semid, BARBERO, 1);


		sem_signal(semid, CLIENTEHECHO, 1);
		sem_wait(semid, BARBEROHECHO, 1);
		fprintf(stdout, "\nUn cliente se corta pelo\n");


		sem_wait(semid, MUTEX, 1);
		
		s->clientes-=1;

		fprintf(stdout, "\nUn cliente se va\n");

		fprintf(stdout, "\n# Clientes = %i \n", s->clientes);


		sem_signal(semid, MUTEX, 1);

		}

		sleep(tiempo);
	}
	
	shmdt(s);
	exit(0);
}

int main(int argc, char* argv[]) {
	int p_tiempo, p_nclientes, pid, i;
	
	if (argc != 3) {
		fprintf(stderr, "Usage: %s periodo_de_regreso numero_clientes\n", argv[0]);
		return -1;
	}
	
	p_tiempo = atoi(argv[1]);
	if (p_tiempo < 1) {
		fprintf(stderr, "%s: El tiempo debe de ser mayor a cero .\n", argv[0]);
		return -1;
	}
	tiempo=p_tiempo;

	p_nclientes = atoi(argv[2]);
	if (p_tiempo < 1) {
		fprintf(stderr, "%s: El numero de clientes debe de ser mayor a cero.\n", argv[0]);
		return -1;
	}
		

	for (i = 0; i < p_nclientes; i++) {
		if ( (pid = fork()) < 0 ) {
			perror(argv[0]);
			return -1;
		} else if (pid == 0) {
			a_cliente(argv[0]);
		} else {
			//do_nothing
		}
	}
	
	return 0;
}
