#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int cantClientes = 0;
int sillasTotales = 3;
int duermeBarbero; //0 esta durmiendo y 1 esta despierto
//int ubicacionDisponible = 3; //Cantidad de sillas contando la del barbero

sem_t semBarbero, semCliente;

pthread_mutex_t atendiendo;
pthread_mutex_t ingresando;

/*------------------ ESTA SECCION PERTENECE AL BARBERO -------------------*/

void *BarberoDormilon(){
    
    while(1){

        sem_wait(&semBarbero);
        pthread_mutex_lock(&atendiendo);
        fflush(stdout);

        if(cantClientes == 0){
            duermeBarbero = 0; //Usar true o false para el estado del barbero
            printf("-BARBERO- ZZZZZZZ \n");

	    
        }

	   else{

		cantClientes--;
		duermeBarbero = 1;

		printf("-BARBERO- XXXXX \n"); 
		printf("-BARBERO- Cliente en espera: %d \n Ubicaciones: %d \n", cantClientes, sillasTotales-cantClientes);
        printf("\n");
		
	   }

       pthread_mutex_unlock(&atendiendo);
    }
}

/*------------------ ESTA SECCION PERTENECE AL CLIENTE -------------------*/

void *Cliente(){

    while (1){

        //inicializar la semilla del generador random:
        int microseconds; srand (time(NULL));

        //generar un numer random entre 1 y 5:
        microseconds = rand() % 5 + 1;

        //dormir el thread, simula que esta haciendo alguna tarea
        sleep(microseconds);

        //muestra los print de la funcion a medida que se ejecuta la funcion, 
        //se necesita usar para cuando se usan sleeps, de lo contrario los prints se muestran cuando termina la ejecucion de la funcion
        //y una funcion puede empezar antes y terminar su ejecucion despues de otro hilo y confundirse los mensajes
        fflush(stdout);
        pthread_mutex_lock(&ingresando);

	if (cantClientes < sillasTotales){
         
        /*----- EL CLIENTA ESTA EN ESPERA -----*/
		if (duermeBarbero == 1){
            printf("-Llego cliente- Leyendo revista...\n");
            printf("Cliente en espera: %d \n Ubicaciones: %d \n", cantClientes, sillasTotales-cantClientes-1);
        }

            /*----- EL PRIMER CLIENTE DESPIERTA AL BARBERO -----*/
		else if (duermeBarbero == 0){

            fflush(stdout);
            duermeBarbero = 1;
            printf("-Llego cliente- ejem, ejem..., cof, cof... \n");
        }
 
        cantClientes ++; 	

        }   
    
        /*----- EL CLIENTE SE VA POR QUE ESTA LLENO EL LUGAR -----*/
    else {
            printf("-Llego cliente- Chau $ chau $ \n");
        }

    printf("\n");

    sem_post(&semBarbero);
	pthread_mutex_unlock(&ingresando);
    pthread_exit(NULL);

    }
}

void *main(){

    printf("Comienza: \n");
    printf("\n");

    sem_init(&semBarbero,0,1); // 1 es el barbero durmiendo 
    sem_init(&semCliente,0,0);

    pthread_mutex_init(&atendiendo, NULL);
    pthread_mutex_init(&ingresando, NULL);

    pthread_t hilo1,hilo2,hilo3,hilo4,hilo5,hilo6,hilo7;

    pthread_create(&hilo1, NULL, BarberoDormilon, NULL);

    pthread_create(&hilo2, NULL, Cliente, NULL);
    pthread_create(&hilo3, NULL, Cliente, NULL);
    pthread_create(&hilo4, NULL, Cliente, NULL);
    pthread_create(&hilo5, NULL, Cliente, NULL);
    pthread_create(&hilo6, NULL, Cliente, NULL);
    pthread_create(&hilo7, NULL, Cliente, NULL);


    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    pthread_join(hilo3, NULL);
    pthread_join(hilo4, NULL);
    pthread_join(hilo5, NULL);
    pthread_join(hilo6, NULL);
    pthread_join(hilo7, NULL);


}
