/*  TAD GRAFO - MATRIZ DE ADJACENCIA  */
/*  autor: Patrick Oliveira Feitosa   */
/*  disciplina: Alg. e Estrutura de dados 2*/
/* arquivo: grafo.h */

#ifndef GRAFO_H
#define GRAFO_H


/* inicializa o grafo setando a quantidade de vertices e zerando as aretas */
void iniciarGrafo(tgrafo *grafo, int num_vertices);
/* adiciona uma aresta de v para u com o seu peso */
void inserirAresta(tgrafo *grafo, tvertice v, tvertice u, tpeso peso);
/* verifica se tem uma aresta do vertice v para o u e o retorna */
int verificarAresta(tgrafo *grafo, tvertice v,  tvertice u);
/* da free no grafo */
void liberarGrafo(tgrafo *grafo);


#endif