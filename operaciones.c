#include  <stdio.h>
#include <limits.h>
#include <unistd.h> 	// para hacer sleep

int main(void)
{
    //creamos un puntero a un archivo
    FILE *fp;

    //abrimos el archivo
    fp = fopen("/tmp/proceso.log", "w+");

    int cuantos=0, num=0, resultado=0,operacion,dividendo=0,producto,divisor=0, i;
    int i_max = INT_MAX/100;

    printf("Elija la operacion a realizar\n");
    printf("(1) Suma\n");
    printf("(2) Resta\n");
    printf("(3) Multiplicacion\n");
    printf("(4) Division\n");

    scanf("%d", &operacion);
    
    if(operacion != 4){

	printf("¿Cuántos números querés usar? (en este punto el proceso esta en Estado Bloqueado(S))\n");
	printf("\n");
	scanf(" %d", &cuantos);

	for (i=0; i<cuantos; i++){
            printf("\nTeclea el número: (en este punto el proceso esta en Estado Bloqueado(S))\n");
            scanf(" %d", &num);
	    
	    if(operacion == 1){
		resultado = resultado + num;
	    }else if(operacion == 2){
		resultado = resultado - num;
	    }else{
		if(i==0){
		   producto=num;
		}else{
		   producto = producto * num;
		}
		resultado = producto;
	    }
	    
            
	}
    }else{
 	printf("\nTeclea el Dividendo: (en este punto el proceso esta en Estado Bloqueado(S))\n");
	scanf(" %d", &dividendo);
	printf("\nTeclea el Divisor: (en este punto el proceso esta en Estado Bloqueado(S))\n");
	scanf(" %d", &divisor);
 	resultado = dividendo/divisor;
    }

    printf("\n\nRealizando cálculos... (en este punto el proceso esta en Estado de Ejecucion (R))\n\n");
    int contador=0;

    while(contador < i_max){
	contador++;	 
	//escribo la variable contador en fp   		 
   	fprintf(fp, "Linea...%d \n",contador);   
    }
    printf("\nEl resultado es: %d", resultado);
    printf("\n\nPresione una tecla para salir...");
    fclose(fp);
    getchar();
    getchar();
    return 0;
}
