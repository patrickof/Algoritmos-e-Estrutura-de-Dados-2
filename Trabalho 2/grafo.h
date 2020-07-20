/*  nome: Patrick Oliveira Feitosa          */
/*  nusp: 10276682                          */
/*  disciplina: Alg. e Estrutura de dados 2 */
/*  atividade: Trabalho 2 - Grafos          */

#ifndef GRAFO_H
#define GRAFO_H

#define MAXVERTICES 10000
#define TAMBUFFER 3000

#define TAM_NOME 40
#define TAM_FILME 100


/* o vertice guarda o nome do artista*/
typedef char tvertice[TAM_NOME];


/* Estrutura da Aresta */
typedef struct { 
    char **filmes;     /* Filmes que eles atuaram juntos */
    int qtd_filmes;    /* controle de quantos filmes eles ja atuaram juntos */
    int KB;            /* menor valor de KB se ele for por esse caminho */

}taresta;


/* Estrutuda do NO da lista de adj */
typedef struct ADJ{
    taresta *info;       /* guarda o filme que eles contracenaram juntos e o KB*/
    tvertice nome;       /* Nome do artista com qual ele contracenou */
    struct ADJ *prox;    /* referencia para o proximo da lista */

} adj;

/* apontador para um no da lista de adjacencia */
typedef adj *tapontador;

/* Lista de Adjacencia*/
typedef struct {
    tvertice nome;    /* Nome do artista */
    adj *inicio;      /* Inicio da lista com as pessoas que contracenaram com ele*/
    
}lista_Adj;

/* Estrutura do Grafo */
typedef struct {
    lista_Adj *vet;      /* lista de adjacencia */
    int num_vertices;    /* qtd de vertices */
} tgrafo;

/* ===== Conjunto de operacoes requisitadas ===== */

/* retorna uma referência para o vértice oposto a v na aresta e*/
lista_Adj *oposto(tgrafo *grafo, tvertice v, taresta e);

/* verdadeiro se os vértices v e w forem adjacentes, falso, caso contrário;*/
int verificarAresta(tgrafo *grafo, tvertice v,  tvertice u);

/*insere um novo vértice isolado, armazenando nele o elemento v, e retorna uma referência para esse vértice*/
lista_Adj* inserirVertice(tgrafo *grafo, tvertice v);

/*insere uma aresta (v, w), armazenando nela o elemento o, e retorna uma referência para essa aresta */
adj* inserirAresta(tgrafo *grafo, tvertice v, tvertice u, taresta o);

/*substitui o elemento da aresta e por o*/
void substituirAresta(tgrafo *grafo, taresta *e, taresta o);

/*substitui o elemento do vértice v por o;*/
void substituirVertice(tgrafo *grafo, tvertice v, tvertice o);


/* ===== Conjunto de operacoes do grafo =====  */

/* inicializa o grafo setando a quantidade de vertices e zerando as aretas */
tgrafo* iniciarGrafo(int num_vertices);

/* adiciona uma aresta de v para u com a sua aresta e*/
int inserirArestaFilme(tgrafo *grafo, tvertice v, tvertice u, taresta e);

/* verificar se o vertice v existe se sim retorna sua referencia */
lista_Adj *verificarVertice(tgrafo *grafo, tvertice v);

/* retorna o primeiro adjacente do vertice v*/
tapontador primeiro_adj(tvertice v,tgrafo *grafo);

/* printa o grafo */
void printarListaAdj(tgrafo *grafo);

/* free na aresta e */
void liberarAresta(taresta *e);

/* free no grafo */
void liberarGrafo(tgrafo *grafo);


/* ===== Conjunto de operacoes auxiliares =====  */

/* printa as informacoes do menu */
void menu();

/* quebra a linha lida do aquivo em um vetor de strings - split("/") */
char **quebra_entradas(char buffer[]);

/* percorre o grafo e printa o menor caminho com as informacoes de filmes e atores */
void pesquisarArtista(tgrafo *grafo);

/* percorre o arquivo adicionando as arestas e vertices */
void inserirArtistas(tgrafo *grafo, FILE *fp);

/* calcula o Desvio Padrao das arestas do Mundo de Kevin Bacon */
double calculoDP(tgrafo *grafo, double media);

/* calcula o Media das areastas do Mundo de Kevin Bacon */
double calculoMedia(tgrafo *grafo);

/* percorre o grafo atribuindo os valores de KB*/
void calculoKB(tgrafo *grafo);

/* verifica se o vertice v existe no vetor artistas*/
int existe(tvertice artistas[], tvertice v);

/* remove o primeiro artista do vetor artistas*/
void removePrim(tvertice artistas[]);

/* adiciona v no fim do vetor artistas*/
void adicionaFim(tvertice artistas[], tvertice v);


#endif