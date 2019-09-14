#include <stdio.h>
#include <stdlib.h> 


int main() { 

	int opcion;
	int op1, op2;
	int resultado;

	printf ("\n Introduzca la operacion que desea realizar");
	printf ("\n 1 - Suma");
	printf ("\n 2 - resta");
	printf ("\n 3 - multiplicacion");
	printf ("\n 4 - division");
	printf ("\n 5 - division con resto");
	printf ("\n");

	scanf("%d", &opcion);
	
	if (opcion == 1){
		printf ("\n Introdusca el primer valor \n");
		scanf ("%d", &op1);
		printf ("\n Introdusca el segundo valor \n");
		scanf ("%d", &op2);
		
		resultado = op1 + op2;
		printf ("\n La suma de %d y %d es: %d", op1, op2, resultado);

	}else if (opcion == 2){

		printf ("\n Introdusca el primer valor \n");
		scanf ("%d", &op1);
		printf ("\n Introdusca el segundo valor \n");
		scanf ("%d", &op2);
		
		resultado = op1 - op2;
		printf ("\n La resta de %d y %d es: %d", op1, op2, resultado);

	}else if (opcion == 3){

		printf ("\n Introdusca el primer valor \n");
		scanf ("%d", &op1);
		printf ("\n Introdusca el segundo valor \n");
		scanf ("%d", &op2);
		
		resultado = op1 * op2;
		printf ("\n El producto de %d y %d es: %d", op1, op2, resultado);

	}else if (opcion == 4){
		
		printf ("\n Introdusca el primer valor \n");
		scanf ("%d", &op1);
		printf ("\n Introdusca el segundo valor \n");
		scanf ("%d", &op2);
		
		if (op2 == 0){
			printf ("\n El divisor no puede ser 0");
		}else{
			resultado = op1 / op2;
			printf ("\n La division de %d y %d es: %d", op1, op2, resultado);
		}
	}

	printf ("\n");
	return 0; 
}
