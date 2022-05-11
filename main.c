#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manejoMatriz.h"

//constantes
#define name 45
BOOL *Visitado = NULL;
int **Grafo = NULL;
int n;
int m;
int I;
int D;

void InicializaVisitados()
{
    int i;
    for(i=0;i<n;i++)
        Visitado[i] = FALSE;
}

void imprimirCamino(int *NodoAnterior, int *Costo, int n, int v0){
    int *Camino, i, j, nodo;

    printf("\nLos caminos son: ");
    Camino = DarMemoriaArreglo(n);
    for(i=0;i<n;i++) {
        if (i != v0) {
            j = 0;
            Camino[j] = i;
            j++;
            nodo = NodoAnterior[i];
            while(nodo != v0) {
                Camino[j] = nodo;
                j++;
                nodo = NodoAnterior[nodo];
            }
            Camino[j] = nodo;

            printf("\n\t%2d -> %2d ($%3d): ", v0, i, Costo[i]);

            while (j >= 0) {
                printf("%3d", Camino[j]);
                j--;
            }
        }
    }
}

void DIJKSTRA(int **Grafo, int v0) {
    BOOL *Visitado;
    int *Costo;
    int *NodoAnterior;
    int i, j, w=v0;

    Visitado = DarMemoriaArreglo(n);
    Costo = DarMemoriaArreglo(n);
    NodoAnterior = DarMemoriaArreglo(n);

    Visitado[v0] = TRUE;
    for(i=0;i<n;i++) {
        if (Grafo[v0][i] == 0)
            Costo[i] = inf;
        else
            Costo[i] = Grafo[v0][i];
        NodoAnterior[i] = v0;
    }
    while (numeroDeNodosSinVisitar(Visitado, n)>1) {
        w = nodoMinimoCostoSinVisitar(Visitado, Costo, n);
        Visitado[w] = TRUE;
        for(j=0;j<n;j++)
        {
            if ((Grafo[w][j] != 0) && (!Visitado[j])) {
                if (Costo[w] + Grafo[w][j] < Costo[j]) {
                    NodoAnterior[j] = w;
                    Costo[j] = Costo[w] + Grafo[w][j];
                }
            }
        }
    }
    imprimirCamino(NodoAnterior, Costo, n, v0);
}

void LeeGrafo(char nomArchivo[20]) {
    FILE *pArchivo;
    int i, u, v, c;

    pArchivo = fopen(nomArchivo, "r");
    if (pArchivo == NULL) {
        printf("\n\n\tERROR: Archivo no encontrado.");
        exit(1);
    }

    fscanf(pArchivo, "%d", &n);
    Grafo = DarMemoriaMatriz(n,n);
    fscanf(pArchivo, "%d",& m);
    fscanf(pArchivo, "%d",& I);
    fscanf(pArchivo, "%d",& D);
    i= 1;

    while (i<=m)
    {
        fscanf(pArchivo, "%d",&u);
        fscanf(pArchivo, "%d",&v);
        fscanf(pArchivo, "%d",&c);
        Grafo[u][v] = c;
        i++;
    }

    Visitado = DarMemoriaArreglo(n);
    fclose(pArchivo);
}

void preProcesamiento() {
    char nomArchivo[20];
    int v0;

    printf("Ingrese nombre del archivo: ");
    gets(nomArchivo);
    LeeGrafo(nomArchivo);

    InicializaVisitados();
    printf("Ingrese nodo inicial para buscar los caminos en el grafo (entre 0 y %d): ", n-1);
    scanf("%d", &v0);
    DIJKSTRA(Grafo, v0);
}



int main() {
    preProcesamiento();
    printf("\n\n");
    return 0;
}

