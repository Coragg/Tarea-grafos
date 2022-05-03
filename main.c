#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//constantes
#define name 45



void readFile(char nameFile[name]){
    FILE *archivo;
    archivo = fopen(name, "r");
    if(archivo == NULL){
        printf("No se puede abrir el archivo %s", nameFile);
        exit(1);
    }

    fclose(archivo);
}

int main(){
    printf("Hello world!\n");
    return 0;
    return 0;
}
