#define TRUE 1
#define FALSE 0
#define inf 3000000

typedef int BOOL;
/*

*/
int **DarMemoriaMatriz(int cantidadDeDatosEnFila, int cantidadDeDatosEnColumna) {
    int **matriz, fila, columna;

    matriz = (int **)malloc(cantidadDeDatosEnFila*sizeof(int *));
    for(fila = 0; fila < cantidadDeDatosEnFila; fila++)
        matriz[fila] = (int *)malloc(cantidadDeDatosEnColumna*sizeof(int));
    for(fila = 0; fila < cantidadDeDatosEnFila; fila++)
        for(columna = 0; columna < cantidadDeDatosEnColumna; columna++)
            matriz[fila][columna] = 0;
    return matriz;
}
/*

*/
int *DarMemoriaArreglo(int numeroDeFilas) {
    int *unidimencionalidadDeLaMatriz, posicionDeLaFila;

    unidimencionalidadDeLaMatriz = (int *)malloc(numeroDeFilas*sizeof(int));
    for(posicionDeLaFila = 0; posicionDeLaFila < numeroDeFilas; posicionDeLaFila++)
        unidimencionalidadDeLaMatriz[posicionDeLaFila] = FALSE;
    return unidimencionalidadDeLaMatriz;
}

/*

*/
int numeroDeNodosSinVisitar(int *Visitado, int CantidadDeDatosEnFilaNoVistos) {
    int posicion, contador;

    posicion = 0;
    contador = 0;

    while (posicion < CantidadDeDatosEnFilaNoVistos) {
        if (Visitado[posicion] == FALSE) {
            contador++;
        }
        posicion++;
    }
   return contador;
}

/*

*/
int nodoMinimoCostoSinVisitar(int *Visitado, int *Costo, int n) {
    int posicionEnLaFila, nodo, minimo;
    BOOL esElPrimero;

    esElPrimero = TRUE;
    posicionEnLaFila = 0;
    while(posicionEnLaFila < n) {
        if (Visitado[posicionEnLaFila] == FALSE) {
            if (esElPrimero) {
                minimo = Costo[posicionEnLaFila];
                nodo = posicionEnLaFila;
                esElPrimero = FALSE;
            } else {
                if (Costo[posicionEnLaFila] < minimo) {
                    minimo = Costo[posicionEnLaFila];
                    nodo = posicionEnLaFila;
                }
            }
        }
        posicionEnLaFila++;
    }
    return nodo;
}

