#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int cantClientes = 0;
int cliente = 1;
int sillasTotales = 3;
int duermeBarbero; //0 esta durmiendo y 1 esta despierto
//int ubicacionDisponible = 3; //Cantidad de sillas contando la del barbero

sem_t semBarbero, semCliente;

pthread_mutex_t mutex;

/*------------------ ESTA SECCION PERTENECE AL BARBERO -------------------*/

void *BarberoDormilon(){
    
    while(1){
        sleep(1);
        sem_wait(&semBarbero);

        pthread_mutex_lock(&mutex);

        if(cantClientes == 0){
            duermeBarbero = 0; //Usar true o false para el estado del barbero
            printf("-BARBERO- ZZZZZZZ \n");
	    
        }

	else{
		
		printf("-BARBERO- XXXXX \n");          	
		cantClientes--;
		
		printf("-BARBERO- Cliente en espera: %d \n Ubicaciones: %d \n", cantClientes, sillasTotales-cantClientes);
		
		//sem_post(&semCliente);
	}

        pthread_mutex_unlock(&mutex);
        sem_post(&semCliente);
    }
}

/*------------------ ESTA SECCION PERTENECE AL CLIENTE -------------------*/

void *Clientes(){

    while (1){
        sem_wait(&semCliente);
        sleep(1);

	srand(time(NULL));
	cliente = rand() % 3;
        pthread_mutex_lock(&mutex);
	cantClientes+=0;
	if (cantClientes < sillasTotales-cantClientes){
	      //cantClientes ++;
              printf("-CLIENTE- Cliente en espera: %d \n Ubicaciones: %d \n", cantClientes, sillasTotales-cantClientes);
              printf("PRUEBA%d",cantClientes);
              /*----- EL CLIENTA ESTA EN ESPERA -----*/
              if (duermeBarbero == 1){
                 printf("-CLIENTE- Leyendo revista...\n");
              }

               /*----- EL PRIMER CLIENTE DESPIERTA AL BARBERO -----*/
               if (duermeBarbero == 0 && cantClientes>0) {
		  
                  printf("ejem, ejem..., cof, cof... \n");
                  duermeBarbero = 1;
		  
            } 

        }   
    
        /*----- EL CLIENTE SE VA POR QUE ESTA LLENO EL LUGAR -----*/
        else {
            printf("-CLIENTE- Chau $ chau $ \n");
        }

	pthread_mutex_unlock(&mutex);

        sem_post(&semBarbero);
    }
}

void *main(){
    printf("Comienza: \n");
    printf("\n");

    sem_init(&semBarbero,0,1); // 1 es el barbero durmiendo 
    sem_init(&semCliente,0,0);

    pthread_mutex_init(&mutex, NULL);
    pthread_t t1,t2,t3,t4,t5,t6,t7;

    pthread_create(&t1, NULL, BarberoDormilon, NULL);
    pthread_create(&t2, NULL, Clientes, NULL);
    pthread_create(&t3, NULL, Clientes, NULL);
    pthread_create(&t4, NULL, Clientes, NULL);
    pthread_create(&t5, NULL, Clientes, NULL);
    pthread_create(&t6, NULL, Clientes, NULL);
    pthread_create(&t7, NULL, Clientes, NULL);


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);
    pthread_join(t7, NULL);
}
