/*  TAD GRAFO - MATRIZ DE ADJACENCIA  */
/*  autor: Patrick Oliveira Feitosa   */
/*  disciplina: Alg. e Estrutura de dados 2*/
#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include <queue>



#define NULO -1



void iniciarGrafo(tgrafo *grafo, int num_vertices){
    
    int i, j;

    /* seta os nos */
    grafo->num_vertices = num_vertices;

    /* seta os nos sem vertices */
    for(i = 0; i<num_vertices;i++)
        for(j = 0; j<num_vertices;j++)
            grafo->mat[i][j] = 0;


}

void inserirAresta(tgrafo *grafo, tvertice v, tvertice u, tpeso peso){

    grafo->mat[v][u] = peso;

}

int verificarAresta(tgrafo *grafo, tvertice v,  tvertice u){

    return grafo->mat[v][u] != 0;
}

void printarMatrizAdj(tgrafo *grafo){

    int i,j;
    for(i=0; i<grafo->num_vertices; i++){
        for(j=0; j<grafo->num_vertices; j++)
            printf("%d ", grafo->mat[i][j]);

        printf("\n");
    }

}

void liberarGrafo(tgrafo *grafo){

    free(grafo);    

}

tapontador primeiro_adj(tvertice v, tgrafo *grafo){

    tapontador aux;

    for(aux=0; aux < grafo->num_vertices; aux++)
        if(grafo->mat[v][aux] != 0)
            return aux;
    
    return NULO;

}

tapontador proximo_adj(tvertice v, tapontador aux, tgrafo *grafo){

    for(aux++; aux < grafo->num_vertices; aux++){
        if(grafo->mat[v][aux] != 0)
            return aux;
    }
    return NULO;

}

void recuperar_adj(tvertice v, tapontador p, tvertice *u, tpeso *peso, tgrafo *grafo){

    *u = p;
    *peso = grafo->mat[v][p];

}

 

void dfs_recursivo(tgrafo *grafo){

    tvertice v;
    int cor[grafo->num_vertices];

    for(v = 0; v < grafo->num_vertices; v++)
        cor[v] = BRANCO;
    
    for(v = 0; v < grafo->num_vertices; v++){
        if(cor[v] == BRANCO)
            dfs_recursivo_aux(v,cor,grafo);
    }

}


void dfs_recursivo_aux(tvertice v, int cor[], tgrafo *grafo){

    tvertice w;
    tapontador p;
    tpeso peso;

    cor[v] = CINZA;

    printf("%d ", v);

    p = primeiro_adj(v, grafo);

    while(p != NULO){
        recuperar_adj(v, p, &w, &peso, grafo);
        
        if(cor[w] == BRANCO)
            dfs_recursivo_aux(w, cor, grafo);
        
        p = proximo_adj(v, p, grafo);
    }

    cor[v] = PRETO;
    


}

void bfs_iterativo(tgrafo *grafo){

    tvertice v;
    int cor[grafo->num_vertices];

    for(v = 0; v < grafo->num_vertices; v++)
        cor[v] = BRANCO;
    
    for(v = 0; v < grafo->num_vertices; v++){
        if(cor[v] == BRANCO)
            bfs_iterativo_aux(v,cor,grafo);
    }
    
}

void bfs_iterativo_aux(tvertice v, int cor[], tgrafo *grafo ){

    tapontador p;
    tpeso peso;
    tvertice w;
    std::queue<tvertice> q;

    cor[v] = CINZA;

    q.push(v);

    printf("%d ", v);

    while(!q.empty()){

        /* pop da "pilha" */
        v = q.front();
        q.pop();

        p = primeiro_adj(v,grafo);

        while(p != NULO){
            recuperar_adj(v,p,&w,&peso, grafo);
            
            if(cor[w] == BRANCO){
                cor[w] = CINZA;
                q.push(w);
                printf("%d ", w);

            }

            p = proximo_adj(v,p,grafo);

        }

        cor[v] = PRETO;


    }




}


void dfs_iterativo(tgrafo *grafo){

    tvertice v;
    int cor[grafo->num_vertices];

    for(v = 0; v < grafo->num_vertices; v++)
        cor[v] = BRANCO;
    
    for(v = 0; v < grafo->num_vertices; v++){
        if(cor[v] == BRANCO)
            dfs_iterativo_aux(v,cor,grafo);
    }
    
}

void dfs_iterativo_aux(tvertice v, int cor[], tgrafo *grafo ){

    tapontador p;
    tpeso peso;
    tvertice w;
    std::queue<tvertice> q;

    cor[v] = CINZA;

    q.push(v);

    printf("%d ", v);

    while(!q.empty()){

        /* pop da "pilha" */
        v = q.front();
        q.pop();

        p = primeiro_adj(v,grafo);

        while(p != NULO){
            recuperar_adj(v,p,&w,&peso, grafo);
            
            if(cor[w] == BRANCO){
                cor[w] = CINZA;
                q.push(w);
                printf("%d ", w);
                v = w;

            }

            p = proximo_adj(v,p,grafo);

        }

        cor[v] = PRETO;


    }




}




