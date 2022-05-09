#define TRUE 1
#define FALSE 0
#define informacion 3000000


int **darMemoriaMatriz(int m, int n){
    int **auxilliary, i, j;
    auxilliary = (int **)malloc(m*sizeof(int *));
    for(i = 0; i<m; i++) {
        auxilliary[i] =(int *)malloc(n*sizeof(int *));
    }
    for(i =0; i<m; j++){
        for(j = 0; j<n; j++){
            auxilliary[i][j] = 0;
        }
    }
    return auxilliary;
}

int *darMemoriaArreglo(int n){
    int *aux, i;
    aux = (int *)malloc(n*sizeof(int));
    for(i=0;i<n; i++){
        aux[i] = FALSE;
    }
    return aux;
}

int numeroDeNodosSinVisitar(int *visitado, int n){
    int i, cont;  
    i = 0;
    cont = 0;
    while(i < n){
        if(visitado[i] == FALSE){
            
        }
    }
}







