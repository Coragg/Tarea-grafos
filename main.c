#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manejoMatriz.h"

// constantes globales
#define name 45

//variables globales
BOOL *Visitado = NULL;
int **Grafo = NULL;
int n;
int m;
int Inicio;
int Destino;
int *Costo;
int *NodoAnterior;

/* da comienzo al recorrido de las filas */
void InicializaVisitados() 
{
    int posicionFila;
    for (posicionFila = 0; posicionFila < n; posicionFila++)
        Visitado[posicionFila] = FALSE;
}
/* va cambiando los nodos y los va cambiando hasta imprimirlos */
void imprimirCamino(int *NodoAnterior, int *Costo, int n, int v0)
{
    int *Camino, i, columna, nodo, nodo1, nodo2;
    Camino = DarMemoriaArreglo(n);

    columna = 0;
    Camino[columna] = Destino;
    columna++;
    nodo = NodoAnterior[Destino];
    while (nodo != Inicio)
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
/* va revisando los arcos y los va quitando */
void buscarYQuitarArcos(int *NodoAnterior, int *Costo, int numeroDeNodo, int v0)
{
    int *Camino, i, columna, nodo, nodo1, nodo2;

    Camino = DarMemoriaArreglo(numeroDeNodo);

    columna = 0;
    Camino[columna] = Destino;
    columna++;
    nodo = NodoAnterior[Destino];
    while (nodo != Inicio)
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
        columna--;
    }
}
/*busca los caminos mas eficientes dentro de un grafo*/
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
/*solo lee el archivo que contiene la matriz para luego crear el grafo*/
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
    fscanf(pArchivo, "%d", &Inicio);
    fscanf(pArchivo, "%d", &Destino);
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
/* este aplica dijkstra cuando ya encotro el casi mas corto y busca los otros caminos que son similares 
y tambien ve si no encuetra caminos casi mas cortos */
void caminoCasiMasCorto()
{
    int caminoCortoDescartado, caminoCasiCorto;
    DIJKSTRA(Grafo, Inicio);
    buscarYQuitarArcos(NodoAnterior, Costo, n, Inicio);
    caminoCortoDescartado = Costo[Destino];
    caminoCasiCorto = caminoCortoDescartado;
    while (caminoCasiCorto == caminoCortoDescartado)
    {
        DIJKSTRA(Grafo, Inicio);
        buscarYQuitarArcos(NodoAnterior, Costo, n, Inicio);
        caminoCasiCorto = Costo[Destino];
    }
    if (caminoCasiCorto == inf)
    {
        printf("NO existe camino casi mas corto.");
        return;
    }
    int otrasOpcionesDeCamino = caminoCasiCorto;
    printf("Distancia total: %d", caminoCasiCorto);

    while (otrasOpcionesDeCamino == caminoCasiCorto)
    {
        printf("\nCamino casi mas corto:");
        imprimirCamino(NodoAnterior, otrasOpcionesDeCamino, n, Inicio);
        DIJKSTRA(Grafo, Inicio);
        buscarYQuitarArcos(NodoAnterior, Costo, n, Inicio);
        otrasOpcionesDeCamino = Costo[Destino];
    }
}
/* pregunta el nombre del archivo y luego ejecuta las funciones previamente creadas */
void preProcesamiento()
{
    char nomArchivo[20];
    int v0;
    //int i;

    printf("Ingrese nombre del archivo: ");
    gets(nomArchivo);
    LeeGrafo(nomArchivo);

    InicializaVisitados();

    caminoCasiMasCorto();
}
/* ejecuta el programa */
int main()
{
    preProcesamiento();
    printf("\n\n");
    return 0;
}
