#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int numero = 3;
    for (int i = 0; i < numero; i++)
    {
        fork();
        printf("Hola Mundo! \n");
    }
    return 0;
}