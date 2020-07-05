#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"


int main(){


    int num_vertices = 6;

    tgrafo *grafo = (tgrafo*)malloc(sizeof(tgrafo));

    iniciarGrafo(grafo, num_vertices);

    inserirAresta(grafo, 0, 1, 1);
    inserirAresta(grafo, 0, 4, 1);

    inserirAresta(grafo, 1, 2, 1);
    inserirAresta(grafo, 1, 4, 1);

    inserirAresta(grafo, 2, 5, 1);

    inserirAresta(grafo, 3, 0, 1);
    inserirAresta(grafo, 3, 4, 1);

    inserirAresta(grafo, 4, 5, 1);

    inserirAresta(grafo, 5, 1, 1);

    printarMatrizAdj(grafo);
    printf("\n");
    dfs_recursivo(grafo);
    printf("\n");
    bfs_iterativo(grafo);
    printf("\n");
    liberarGrafo(grafo);

    return 0;
}