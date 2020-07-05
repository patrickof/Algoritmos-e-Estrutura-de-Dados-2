#include <stdio.h>
#include <stdio.h>
#include "grafo.h"



int main(){


    int num_vertices = 4;

    tgrafo *grafo = (tgrafo*)malloc(sizeof(tgrafo));

    iniciarGrafo(grafo, num_vertices);

    inserirVertice(grafo, 0, 1, 1);
    inserirVertice(grafo, 0, 2, 1);
    inserirVertice(grafo, 0, 3, 1);

    inserirVertice(grafo, 1, 2, 1);
    inserirVertice(grafo, 1, 3, 1);
    inserirVertice(grafo, 1, 4, 1);

    inserirVertice(grafo, 2, 3, 1);
    inserirVertice(grafo, 2, 4, 1);
    inserirVertice(grafo, 2, 5, 1);

    inserirVertice(grafo, 3, 4, 1);
    inserirVertice(grafo, 3, 5, 1);

    inserirVertice(grafo, 4, 5, 1);



    return 0;
}