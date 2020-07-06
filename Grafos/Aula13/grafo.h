/*  TAD GRAFO - MATRIZ DE ADJACENCIA  */
/*  autor: Patrick Oliveira Feitosa   */
/*  disciplina: Alg. e Estrutura de dados 2*/
/* arquivo: grafo.h */

#ifndef GRAFO_H
#define GRAFO_H


#define MAXVERTICES 100

#define BRANCO 0
#define CINZA 1
#define PRETO 2


/* peso da aresta */
typedef int tpeso;
/* vertice */
typedef int tvertice;

typedef int tapontador;


typedef struct {
    tpeso mat[MAXVERTICES][MAXVERTICES]; /* matriz de adjacencia*/
    int num_vertices; /*qtd de vertices*/
} tgrafo;


/* inicializa o grafo setando a quantidade de vertices e zerando as aretas */
void iniciarGrafo(tgrafo *grafo, int num_vertices);
/* adiciona uma aresta de v para u com o seu peso */
void inserirAresta(tgrafo *grafo, tvertice v, tvertice u, tpeso peso);
/* verifica se tem uma aresta do vertice v para o u e o retorna */
int verificarAresta(tgrafo *grafo, tvertice v,  tvertice u);
/* printa a matriz de adjacencia */
void printarMatrizAdj(tgrafo *grafo);

tapontador primeiro_adj(tvertice v, tgrafo *grafo);

tapontador proximo_adj(tvertice v, tapontador aux, tgrafo *grafo);

void dfs_recursivo(tgrafo *grafo);

void dfs_recursivo_aux(tvertice v, int cor[], tgrafo *grafo);

void dfs_iterativo(tgrafo *grafo);

void dfs_iterativo_aux(tvertice v, int cor[], tgrafo *grafo );

void bfs_iterativo(tgrafo *grafo);

void bfs_iterativo_aux(tvertice v, int cor[], tgrafo *grafo );

void recuperar_adj(tvertice v, tapontador p, tvertice *u, tpeso *peso, tgrafo *grafo);

/* da free no grafo */
void liberarGrafo(tgrafo *grafo);


#endif