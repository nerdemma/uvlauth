#include <stdio.h>
#include <stdlib.h>
#include "../lib/signer.h"
/*
este codigo  me tira error

main.c:7:22: warning: implicit declaration of function 'generar_cadena' is invalid in C99 [-Wimplicit-function-declaration]
    char *mi_firma = generar_cadena("Hola Avalanche");
                     ^
main.c:7:11: warning: incompatible integer to pointer conversion initializing 'char *' with an expression of type 'int' [-Wint-conversion]
    char *mi_firma = generar_cadena("Hola Avalanche");
          ^          ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


*/

int main() {
    char *mi_firma = generar_cadena("Hola Avalanche");

    if (mi_firma) {
        printf("Resultado para el otro programa: %s\n", mi_firma);
        free(mi_firma); 
    }

    return 0;
}
