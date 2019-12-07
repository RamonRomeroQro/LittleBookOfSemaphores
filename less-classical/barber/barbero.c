#include "header.h"
void a_barbero(char * program) {
    int semid, shmid, i, j, k;
    Salon * s;
    key_t key;

    if ((key = ftok("/dev/null", 100)) == (key_t) - 1) {
        perror(program);
        exit(-1);
    }

    if ((semid = semget(key, 5, 0666)) < 0) {
        perror(program);
        exit(-1);
    }

    while (1) {

        sem_wait(semid, CLIENTE, 1);
        sem_signal(semid, BARBERO, 1);

        printf("\nBarbero corta el pelo de un cliente\n");

        sem_wait(semid, CLIENTEHECHO, 1);
        sem_signal(semid, BARBEROHECHO, 1);

    }

    exit(0);

}

int main(int argc, char * argv[]) {
    int amount, pid, i;

    if (argc != 1) {
        fprintf(stderr, "usage: %s \n", argv[0]);
        return -1;
    }

    a_barbero(argv[0]);

    return 0;
}