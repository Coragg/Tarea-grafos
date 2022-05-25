#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manejoMatriz.h"

// constantes
#define name 45
BOOL *Visitado = NULL;
int **Grafo = NULL;
int n;
int m;
int I;
int D;
int *Costo;
int *NodoAnterior;
int g = 1;
int existeSegundo = 0;

void InicializaVisitados()
{
    int posicionFila;
    for (posicionFila = 0; posicionFila < n; posicionFila++)
        Visitado[posicionFila] = FALSE;
}

void imprimirCamino(int *NodoAnterior, int *Costo, int n, int v0)
{
    int *Camino, i, columna, nodo, nodo1, nodo2;
    Camino = DarMemoriaArreglo(n);

    columna = 0;
    Camino[columna] = D;
    columna++;
    nodo = NodoAnterior[D];
    while (nodo != I)
    {
        Camino[columna] = nodo;
        columna++;
        nodo = NodoAnterior[nodo];
    }
    Camino[columna] = nodo;


    for (i = 0; i < columna; i++)
    {
        nodo1 = Camino[i];
        nodo2 = Camino[i + 1];
        Grafo[nodo2][nodo1] = 0;
    }

    while (columna >= 0)
    {
        printf("%3d", Camino[columna]);
        columna--;
    }
}

void buscarYQuitarArcos(int *NodoAnterior, int *Costo, int numeroDeNodo, int v0)
{
    int *Camino, i, columna, nodo, nodo1, nodo2;

    Camino = DarMemoriaArreglo(numeroDeNodo);

    columna = 0;
    Camino[columna] = D;
    columna++;
    nodo = NodoAnterior[D];
    while (nodo != I)
    {
        Camino[columna] = nodo;
        columna++;
        nodo = NodoAnterior[nodo];
    }
    Camino[columna] = nodo;

    if(Costo[D] == inf && g == 1) {
        existeSegundo = 1;
    }
    

    for (i = 0; i < columna; i++)
    {
        nodo1 = Camino[i];
        nodo2 = Camino[i + 1];
        Grafo[nodo2][nodo1] = 0;
    }
    while (columna >= 0)
    {
        columna--;
    }
}

void DIJKSTRA(int **Grafo, int v0)
{
    int i, j, w = v0;

    Visitado = DarMemoriaArreglo(n);
    Costo = DarMemoriaArreglo(n);
    NodoAnterior = DarMemoriaArreglo(n);

    Visitado[v0] = TRUE;
    for (i = 0; i < n; i++)
    {
        if (Grafo[v0][i] == 0)
            Costo[i] = inf;
        else
            Costo[i] = Grafo[v0][i];
        NodoAnterior[i] = v0;
    }
    while (numeroDeNodosSinVisitar(Visitado, n) > 1)
    {
        w = nodoMinimoCostoSinVisitar(Visitado, Costo, n);
        Visitado[w] = TRUE;
        for (j = 0; j < n; j++)
        {
            if ((Grafo[w][j] != 0) && (!Visitado[j]))
            {
                if (Costo[w] + Grafo[w][j] < Costo[j])
                {
                    NodoAnterior[j] = w;
                    Costo[j] = Costo[w] + Grafo[w][j];
                }
            }
        }
    }
}

void LeeGrafo(char nomArchivo[20])
{
    FILE *pArchivo;
    int i, u, v, c;

    pArchivo = fopen(nomArchivo, "r");
    if (pArchivo == NULL)
    {
        printf("\n\n\tERROR: Archivo no encontrado.");
        exit(1);
    }

    fscanf(pArchivo, "%d", &n);
    Grafo = DarMemoriaMatriz(n, n);
    fscanf(pArchivo, "%d", &m);
    fscanf(pArchivo, "%d", &I);
    fscanf(pArchivo, "%d", &D);
    i = 1;

    while (i <= m)
    {
        fscanf(pArchivo, "%d", &u); // u es igual a la fila
        fscanf(pArchivo, "%d", &v); // v es la columna
        fscanf(pArchivo, "%d", &c);
        Grafo[u][v] = c;
        i++;
    }

    Visitado = DarMemoriaArreglo(n);
    fclose(pArchivo);
}

void caminoCasiMasCorto()
{
    int x, y;
    DIJKSTRA(Grafo, I);
    buscarYQuitarArcos(NodoAnterior, Costo, n, I);
    x = Costo[D];
    y = x;
    while (y == x)
    {
        DIJKSTRA(Grafo, I);
        buscarYQuitarArcos(NodoAnterior, Costo, n, I);
        y = Costo[D];
    }
    if(y == inf){
        printf("NO existe camino casi mas corto.");
        return;
    }
    int z = y;
    printf("Distancia total: %d", y);

    while (z == y)
    {
        printf("\nCamino casi mas corto:");
        imprimirCamino(NodoAnterior, z, n, I);
        DIJKSTRA(Grafo, I);
        buscarYQuitarArcos(NodoAnterior, Costo, n, I);
        z = Costo[D];
    }


}

void preProcesamiento()
{
    char nomArchivo[20];
    int v0;
    int i;

    printf("Ingrese nombre del archivo: ");
    gets(nomArchivo);
    LeeGrafo(nomArchivo);

    InicializaVisitados();

    caminoCasiMasCorto();
}

int main()
{
    preProcesamiento();
    printf("\n\n");
    return 0;
}
