#include <stdio.h>
#include <stdlib.h>


int **leerEntrada(int *n){
    FILE *archivoEntrada = fopen("entrada2.in", "r");
    int primerNum = 0;
    fscanf(archivoEntrada, "%d", &primerNum);

    int **mapa = malloc(sizeof(int *)*primerNum);
    for (int i = 0; i < primerNum; i++)
    {
        mapa[i] = malloc(sizeof(int)*primerNum);
    }
    
    for(int i = 0; i < primerNum; i++)
    {
        for (int j = 0; j < primerNum; j++)
        {
            fscanf(archivoEntrada, "%d", &mapa[i][j]);
        }
        
    }
    fclose(archivoEntrada);

    *n = primerNum; // Para poder ocupar este numero fuera de la funcion
    return mapa;
}