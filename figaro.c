#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

sem_t semFiiiiigaro, semFigaro, semFigaro1, semFigaro2, semFigaroFi, semFigaroFa;
int cantidad;

void *imprimirFiiiiigaro (){

    for (int i = 0; i < cantidad; i++)
    {
        sem_wait(&semFiiiiigaro);
        printf("Fiiiiigaro \n");
        sem_post(&semFigaro);
    }

    pthread_exit(NULL);
}

void *imprimirFigaro () {

    for (int i = 0; i < cantidad; i++)
    {
        sem_wait(&semFigaro);
        printf("Figaro ");
        sem_post(&semFigaro1);
    }

    pthread_exit(NULL);
}

void *imprimirFigaro1 () {

    for (int i = 0; i < cantidad; i++)
    {
        sem_wait(&semFigaro1);
        printf("Figaro ");
        sem_post(&semFigaro2);
    }

    pthread_exit(NULL);
}

void *imprimirFigaro2 () {

    for (int i = 0; i < cantidad; i++)
    {
        sem_wait(&semFigaro2);
        printf("Figaro \n");
        sem_post(&semFigaroFi);
    }

    pthread_exit(NULL);
}

void *imprimirFigaroFi() {

    for (int i = 0; i < cantidad; i++)
    {
        sem_wait(&semFigaroFi);
        printf("Figaro Fi \n");
        sem_post(&semFigaroFa);
    }

    pthread_exit(NULL);
}

void *imprimirFigaroFa(){

    for (int i = 0; i < cantidad; i++)
    {
        sem_wait(&semFigaroFa);
        printf("Figaro Fa \n");
        sem_post(&semFiiiiigaro);
        sleep(1);
    }

    pthread_exit(NULL);
}

void *Sem(){
    sem_init(&semFiiiiigaro,0,1);
    sem_init(&semFigaro,0,0);
    sem_init(&semFigaro1,0,0);
    sem_init(&semFigaro2,0,0);
    sem_init(&semFigaroFi,0,0);
    sem_init(&semFigaroFa,0,0);
}

void *hilos(){
    pthread_t hiloFiiiiigaro, hiloFigaro, hiloFigaro1, hiloFigaro2, hiloFigaroFi, hiloFigaroFa;

    pthread_create(&hiloFiiiiigaro, NULL, imprimirFiiiiigaro, NULL);
    pthread_create(&hiloFigaro, NULL, imprimirFigaro, NULL);
    pthread_create(&hiloFigaro1, NULL, imprimirFigaro1, NULL);
    pthread_create(&hiloFigaro2, NULL, imprimirFigaro2, NULL);
    pthread_create(&hiloFigaroFi, NULL, imprimirFigaroFi, NULL);
    pthread_create(&hiloFigaroFa, NULL, imprimirFigaroFa, NULL);

    pthread_join(hiloFiiiiigaro, NULL);
    pthread_join(hiloFigaro, NULL);
    pthread_join(hiloFigaro1, NULL);
    pthread_join(hiloFigaro2, NULL);
    pthread_join(hiloFigaroFi, NULL);
    pthread_join(hiloFigaroFa, NULL);
}

void *destruirSem() {
    sem_destroy(&semFiiiiigaro);
    sem_destroy(&semFigaro);
    sem_destroy(&semFigaro1);
    sem_destroy(&semFigaro2);
    sem_destroy(&semFigaroFi);
    sem_destroy(&semFigaroFa);
}

int main () {
    printf("Ingrese cantidad de figaros a entonar: ");
    scanf("%i", &cantidad);

    Sem();
    hilos();
    pthread_exit(NULL);
    destruirSem();

    return 0;
}