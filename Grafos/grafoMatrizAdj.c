/*  TAD GRAFO - MATRIZ DE ADJACENCIA  */
/*  autor: Patrick Oliveira Feitosa   */
/*  disciplina: Alg. e Estrutura de dados 2*/
#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

#define MAXVERTICES 100

/* peso da aresta */
typedef int tpeso;
/* vertice */
typedef int tvertice;

/* estrutura do grafo*/
typedef struct{
    tpeso mat[MAXVERTICES][MAXVERTICES]; /* matriz de adjacencia*/
    int num_vertices; /*qtd de vertices*/
}tgrafo;


void iniciarGrafo(tgrafo *grafo, int num_vertices){
    
    int i, j;

    /* seta os nos */
    grafo->num_vertices = num_vertices;

    /* seta os nos sem vertices */
    for(i = 0; i<num_vertices;i++)
        for(j = 0; j<num_vertices;j++)
            tgrafo->mat[i][j] = 0;


}

void inserirAresta(tgrafo *grafo, tvertice v, tvertice u, tpeso peso){

    grafo->mat[v][u] = peso;

}

int verificarAresta(tgrafo *grafo, tvertice v,  tvertice u){

    return grafo->mat[v][u] != 0;
}

void liberarGrafo(tgrafo *grafo){

    free(grafo);    

}