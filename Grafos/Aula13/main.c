/* Desenvolvido por Patrick Feitosa*/
/* Numero USP: 10276682 */
#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"


int main(){


    int num_vertices = 6;

    tgrafo *grafo = (tgrafo*)malloc(sizeof(tgrafo));

    iniciarGrafo(grafo, num_vertices);

    inserirAresta(grafo, 0, 1, 1);
    inserirAresta(grafo, 0, 2, 1);
    inserirAresta(grafo, 0, 3, 1);


    inserirAresta(grafo, 1, 2, 1);
    inserirAresta(grafo, 1, 3, 1);
    inserirAresta(grafo, 1, 4, 1);

    inserirAresta(grafo, 2, 3, 1);
    inserirAresta(grafo, 2, 4, 1);
    inserirAresta(grafo, 2, 5, 1);

    inserirAresta(grafo, 3, 4, 1);
    inserirAresta(grafo, 3, 5, 1);

    inserirAresta(grafo, 4, 5, 1);

    printf("\n");
    printf("Matriz de Adjacencia:\n");
    printarMatrizAdj(grafo);
    printf("\n");
    printf("DFS recursivo:\n");    
    dfs_recursivo(grafo);
    printf("\n");
    printf("BFS recursivo:\n");    
    bfs_iterativo(grafo);
    printf("\n");
    printf("DFS iterativo:\n");    
    dfs_iterativo(grafo);
    printf("\n");
    liberarGrafo(grafo);

    return 0;
}