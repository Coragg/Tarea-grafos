#define TRUE 1
#define FALSE 0
#define inf 3000000

typedef int BOOL;

int **DarMemoriaMatriz(int m, int n) {
    int **aux, i, j;

    aux = (int **)malloc(m*sizeof(int *));
    for(i=0;i<m;i++)
        aux[i] = (int *)malloc(n*sizeof(int));
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            aux[i][j] = 0;
    return aux;
}
int *DarMemoriaArreglo(int n) {
    int *aux, i;

    aux = (int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
        aux[i] = FALSE;
    return aux;
}

int numeroDeNodosSinVisitar(int *Visitado, int n) {
    int i, cont;

    i = 0;
    cont = 0;

    while (i < n) {
        if (Visitado[i] == FALSE) {
            cont++;
        }
        i++;
    }
   return cont;
}
int nodoMinimoCostoSinVisitar(int *Visitado, int *Costo, int n) {
    int i, nodo, minimo;
    BOOL esElPrimero;

    esElPrimero = TRUE;
    i = 0;
    while(i < n) {
        if (Visitado[i] == FALSE) {
            if (esElPrimero) {
                minimo = Costo[i];
                nodo = i;
                esElPrimero = FALSE;
            } else {
                if (Costo[i] < minimo) {
                    minimo = Costo[i];
                    nodo = i;
                }
            }
        }
        i++;
    }
    return nodo;
}










