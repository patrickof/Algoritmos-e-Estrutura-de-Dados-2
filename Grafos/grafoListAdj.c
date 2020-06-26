/*  TAD GRAFO - LISTA DE ADJACENCIAS  */
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

/* no da lista adjacente*/
typedef struct {

    tvertice vertice;
    tpeso peso;
    struct taresta *prox;

} taresta;

typedef taresta* tapontador;

/* estrutura do grafo*/
typedef struct{
    tapontador vet[MAXVERTICES]; /* vetor com as lista de adjacencia*/
    int num_vertices; /*qtd de vertices*/
}tgrafo;


void iniciarGrafo(tgrafo *grafo, int num_vertices){
    
    int i;
    /* seta os nos */
    grafo->num_vertices = num_vertices;

    /* aloca e seta as arestas sem vertices */
    for(i=0; i<num_vertices; i++){
        grafo->vet[i] = NULL;
}

void inserirAresta(tgrafo *grafo, tvertice v, tvertice u, tpeso peso){

    if(v > (grafo->num_vertices-1)){
        printf("Erro: vertice de insercao nao existe")
        return;
    }
    
    int i;
    
    tapontador aux, novaAresta;    

    /* cria a aresta u na lista de v */
    novaAresta = (tapontador)malloc(sizeof(taresta));

    if(tapontador == NULL){
        printf("Erro: alocacao de uma aresta");
        return;
    }

    /* setando os valores */
    novaAresta->vertice = u;
    novaAresta->peso = peso;


    /* adicionando ao inicio da lista */
    aux = grafo->vet[i];
    grafo->vet[i] = novaAresta;
    novaAresta->prox = aux;

    return;

}

int verificarAresta(tgrafo *grafo, tvertice v,  tvertice u){

    if(v > (grafo->num_vertices-1)){
        printf("Erro: vertice de insercao nao existe")
        return -1;
    }

    tapontador aux;

    /* percorrer o vetor até encontrar o vertice v*/
    aux = grafo->vet[i]

    /*lista vazia*/
    
    while(aux != NULL){
    
        /* se encontrou retorna o peso */
        if(aux->vertice == u)
            return aux->peso;

        aux = aux->prox;
    }

    /* caso nao tenha encontrado a aresta*/
    return -1;

}

void liberarGrafo(tgrafo *grafo){

    int i;
    tapontador atual, prox;

    /*percorrer o vetor lista*/
    for(i = 0; i<grafo->num_vertices;i++){

        atual = grafo->vet[i];
           
        /* percorre a lista dando free*/
        while(atual != NULL){

            prox = atual->prox;
            free(atual);
            atual = prox;

        }


    }

    free(grafo);    

}