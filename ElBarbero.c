#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int clientes = 0;
int duermeBarbero; //0 esta durmiendo y 1 esta despierto
int ubicacionDisponible = 10; //Cantidad de sillas contando la del barbero

sem_t semBarbero, semCliente;

pthread_mutex_t mutex;

/*------------------ ESTA SECCION PERTENECE AL BARBERO -------------------*/

void *BarberoDormilon(){
    
    while(1){
        sleep(1);
        sem_wait(&semBarbero);

        pthread_mutex_lock(&mutex);
        if(clientes == 0){
            duermeBarbero = 0; //Usar true o false para el estado del barbero
        }

        /*----- EL BARBERO ESTA DURMIENDO -----*/
        if(clientes <= 0){
            duermeBarbero = 0; //VER EL ESTADO DEL BARBERO
            printf("-BARBERO- Cliente en espera: %d \n Ubicaciones: %d \n", clientes, ubicacionDisponible);
            printf("-BARBERO- ZZZZZ \n");
        }

        /*----- EL BARBERO ESTA TRABAJANDO -----*/
        if(duermeBarbero = 1 && clientes > 0) {
            printf("-BARBERO- Cliente en espera: %d \n Ubicaciones: %d \n", clientes, ubicacionDisponible);
            printf("-BARBERO- XXXXX \n");
            clientes -= 1;
            ubicacionDisponible += 1;
        }

        pthread_mutex_unlock(&mutex);
        printf("-BARBERO- Cliente en espera: %d \n Ubicaciones: %d \n", clientes, ubicacionDisponible);

        sem_post(&semCliente);
    }
}

/*------------------ ESTA SECCION PERTENECE AL CLIENTE -------------------*/

void *Clientes(){
    int random = 0;

    while (1){
        sem_wait(&semCliente);
        sleep(1);

        srand(time(NULL));
        random = rand()%3;
        pthread_mutex_lock(&mutex);

        /*----- EL CLIENTA ESTA EN ESPERA -----*/
        if (duermeBarbero == 1 && clientes > 1){
            printf("-CLIENTE- Leyendo revista...\n");
        }

        
        if ((ubicacionDisponible - random) >= 0){
            clientes += random;
            ubicacionDisponible -= random;
            printf("-CLIENTE- Cliente en espera: %d \n Ubicaciones: %d \n", clientes, ubicacionDisponible);

            /*----- EL PRIMER CLIENTE DESPIERTA AL BARBERO -----*/
            if (duermeBarbero <= 0 && clientes > 0) {
                printf("ejem, ejem..., cof, cof... \n");
                duermeBarbero = 1;
            } 
        }   
        pthread_mutex_unlock(&mutex);

        /*----- EL CLIENTE SE VA POR QUE ESTA LLENO EL LUGAR -----*/
        if ((ubicacionDisponible - random) < 0){
            printf("-CLIENTE- Chau $ chau $");
        }

        random = 0;
        sem_post(&semBarbero);
    }
}

void *main(){
    printf("Comienza: \n");
    printf("\n");

    sem_init(&semBarbero,0,1);
    sem_init(&semCliente,0,0);

    pthread_mutex_init(&mutex, NULL);
    pthread_t t1,t2;

    pthread_create(&t1, NULL, BarberoDormilon, NULL);
    pthread_create(&t2, NULL, Clientes, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}