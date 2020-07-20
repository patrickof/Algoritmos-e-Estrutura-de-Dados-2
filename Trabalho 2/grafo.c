/*  nome: Patrick Oliveira Feitosa          */
/*  nusp: 10276682                          */
/*  disciplina: Alg. e Estrutura de dados 2 */
/*  atividade: Trabalho 2 - Grafos          */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grafo.h"


lista_Adj *oposto(tgrafo *grafo, tvertice v, taresta e){

    if(grafo == NULL)
        return NULL;

    lista_Adj *posv = verificarVertice(grafo,v);

    adj *aux;

    aux = posv->inicio;


    while (aux != NULL){

        if(strcmp(aux->info->filmes[0],e.filmes[0])==0 && aux->info->KB == e.KB )
            break;

        aux = aux->prox;
    }
    
    return verificarVertice(grafo, aux->nome);


}

int verificarAresta(tgrafo *grafo, tvertice v,  tvertice u){

    tapontador inicio = primeiro_adj(v,grafo);

    tapontador aux;

    if(inicio == NULL)
        return 0;
    else
        aux = inicio;


    while (aux != NULL){
        
        if(strcmp(aux->nome,u) == 0)
            return 1;

        aux = aux->prox;
    }
    return 0;
}

lista_Adj *inserirVertice(tgrafo *grafo, tvertice v){

    
    if(grafo == NULL)
        return NULL;
    
    lista_Adj *aux;


    if(grafo->num_vertices == 0){

        aux = (lista_Adj*)malloc(sizeof(lista_Adj));

        if(aux == NULL)
            return aux;
        
        strcpy(aux->nome,v);
        
        aux->inicio = NULL;


        grafo->vet = aux;

        grafo->num_vertices++;

        


    }
    else{ /* ira pesquisar se o vertice ja existes, caso n exista, adiciona ordenado */

        int encontrou = 0;

        /* binary search*/
        int inicio = 0;
        int fim = grafo->num_vertices- 1;
        int meio = (inicio+fim)/2;
    

        while(inicio <= fim){

            if(strcmp(grafo->vet[meio].nome,v)==0){
                encontrou = 1;
                break;/* como trata-se de uma insercao, algo errado ocorreu */

            }
            else if(strcmp(grafo->vet[meio].nome,v)>  0){

                if(meio != 0){
                    if(strcmp(grafo->vet[meio-1].nome,v) < 0)
                        break;
                }

                fim = meio-1;
            }else{ /* indices[meio].chave < chave*/

                if(meio < grafo->num_vertices-1){
                    if(strcmp(grafo->vet[meio+1].nome,v)>0){
                        meio+=1;
                        break;
                    }
                }else if(meio == fim){
                    meio+=1;
                    break;
                }

                inicio = meio+1;

            }
            meio = (inicio+fim)/2;

        }

        /*printf("\nVertice: %s Pos: %d\n Enc: %d", v, meio, encontrou);*/
    
        /* caso n encontre */
        if(!encontrou){


            aux = grafo->vet;

            aux = (lista_Adj*)realloc(aux, (grafo->num_vertices+1)*sizeof(lista_Adj));

            int i;

            for(i = grafo->num_vertices; i> meio; i--)
                aux[i] = aux[i-1];

            strcpy(aux[meio].nome, v);
            aux[meio].inicio = NULL;

            grafo->vet = aux;
            grafo->num_vertices++;

            
            aux = &aux[meio];


        }



    }

    return aux;

}

adj* inserirAresta(tgrafo *grafo, tvertice v, tvertice u, taresta o){

    lista_Adj *posv = verificarVertice(grafo, v);
    
    lista_Adj *posu = verificarVertice(grafo, u);

    /* caso os vertices n existam*/
    if(posv == NULL || posu == NULL || o.filmes == NULL){
        printf("Erro");
        return NULL;
    
    }
    /* v->u*/
    long unsigned int tam; /* tamanho da string do filme*/
    adj *adj_u;
    /* verificar se aquele vertice ja existe */
    /* se sim, procura o aresta e adiciona apenas o filme na lista de filmes */
    /* se não, criar uma aresta e adiciona normalmente*/
    if(verificarAresta(grafo,v,u)){

        tapontador aux = posv->inicio;

        while (strcmp(aux->nome,u) != 0){
            aux = aux->prox;
        }

        char **aux_filmes = (char**)realloc(aux->info->filmes,(aux->info->qtd_filmes+1)*sizeof(char*));

        if(aux_filmes == NULL)
            return NULL;
        
        tam = strlen(o.filmes[0]);
        char *aux_filme = (char*)malloc(sizeof(char)*(tam+1));

        if(aux_filme == NULL)
            return NULL;

        strcpy(aux_filme,o.filmes[0]);

        aux_filmes[aux->info->qtd_filmes] = aux_filme;

        aux->info->filmes = aux_filmes;

        aux->info->qtd_filmes++;
        
        adj_u = aux;
    }
    else{   /* se não, criar uma aresta e adiciona normalmente*/

        adj_u = (adj*)malloc(sizeof(adj));

        if(adj_u == NULL)
            return NULL;

        /* criando aresta*/
        taresta *info_u = (taresta*)malloc(sizeof(taresta));

        if(info_u == NULL)
            return NULL;

        /* vetor de filmes */
        char **filmes = (char**)malloc(sizeof(char*));
        
        if(filmes == NULL)
            return NULL;

        /* adicionando o primeiro filme */
        tam = strlen(o.filmes[0]);
        filmes[0] = (char*)malloc((tam+1)*sizeof(char));

        if(filmes[0] == NULL)
            return NULL;


        strcpy(filmes[0],o.filmes[0]);

        
        /* iniciando aresta*/
        info_u->filmes = filmes;
        info_u->KB = o.KB;
        info_u->qtd_filmes = 1;

        /*printf("%s\n",info_u->filmes[0])*/;


        /*adicionando a informaçoes da aresta*/
        adj_u->info = info_u;
        strcpy(adj_u->nome,u);


        /* adiciona no inicio sempre deixando o Kevin no inicio */
        if(posv->inicio != NULL && strcmp("Bacon, Kevin",posv->inicio->nome) == 0){
            
            adj_u->prox = posv->inicio->prox ;
            posv->inicio->prox = adj_u;

        }else{
            adj_u->prox = posv->inicio;
            posv->inicio = adj_u;

            }


    }
    return adj_u;



}

void substituirAresta(tgrafo *grafo, taresta *e, taresta o){

    if(grafo == NULL && e == NULL){
        return;
    }

    char **aux;
    aux = e->filmes;
    
    e->filmes = o.filmes;
    e->KB = o.KB;
    e->qtd_filmes = o.qtd_filmes;


    free(aux);


}

void substituirVertice(tgrafo *grafo, tvertice v, tvertice o){

    if(grafo == NULL)
        return;

    lista_Adj *pos_aux,*pos = verificarVertice(grafo,v);


    if(pos == NULL)
        return;

    strcpy(pos->nome,o);

    adj *aux1,*aux2;

    aux1 = pos->inicio;

    while(aux1 != NULL){

        pos_aux = verificarVertice(grafo,aux1->nome);
        aux2 = pos_aux->inicio;

        while(aux2 != NULL){
            
            if(strcmp(aux2->nome,v) == 0){
                strcpy(aux2->nome,o);
                break;
            }

            aux2 = aux2->prox;

        }

        aux1 = aux1->prox;

    }

}



tgrafo *iniciarGrafo(int num_vertices){
    
    tgrafo *aux;
    
    aux = (tgrafo*)malloc(sizeof(tgrafo));

    if(aux != NULL){
       aux->vet = NULL;
       aux->num_vertices = num_vertices; /* 0 */

    }else
        printf("Erro de alocacao");

    return aux;

}

int inserirArestaFilme(tgrafo *grafo, tvertice v, tvertice u, taresta info){

    adj* arestaVU = inserirAresta(grafo,v,u,info);

   /* adj *arestaUV = inserirAresta(grafo,u,v,info);
*/
    if(arestaVU == NULL)
        return 0;
    else
        return 1;
    

}

lista_Adj *verificarVertice(tgrafo *grafo, tvertice v){

    int encontrou = 0;

    /* binary search*/
    int inicio = 0;
    int fim = grafo->num_vertices- 1;
    int meio = (inicio+fim)/2;

    lista_Adj *retorno;

    while(inicio <= fim){

        if(strcmp(grafo->vet[meio].nome,v)==0){
            encontrou = 1;
            break;/* como trata-se de uma insercao, algo errado ocorreu */

        }
        else if(strcmp(grafo->vet[meio].nome,v)>  0){
            fim = meio-1;
        
        }else{ /* indices[meio].chave < chave*/

            inicio = meio+1;

        }
        meio = (inicio+fim)/2;

    }



    if(encontrou){
        retorno = &(grafo->vet[meio]);
    }else{
        retorno = NULL;
    }

        
    return retorno;
    



}

tapontador primeiro_adj(tvertice v,tgrafo *grafo){

    lista_Adj *pos;

    pos = verificarVertice(grafo,v);

    if(pos != NULL)
        return pos->inicio;


    return NULL;

}

void printarListaAdj(tgrafo *grafo){

    if(grafo == NULL)
        return;
    
    int i;
    adj *aux;

    for(i=0; i<grafo->num_vertices; i++){

    
        printf("[%s]: ", grafo->vet[i].nome);

        aux = grafo->vet[i].inicio;
        if(aux == NULL)
            printf(" NULL");

        while(aux!=NULL){
            
            printf("-> |%d|[%s] ", aux->info->KB,aux->nome);
    /*
            printf("-> %d|%s ",aux->info->qtd_filmes,aux->nome);
*/
            aux=aux->prox;

        }


        printf("\n\n");
        
    }

}

void liberarAresta(taresta *info){

    int i;
    /* percorre todos os filmes presentes na aresta*/
    for ( i = 0; i < info->qtd_filmes; i++){
        /* free nas strings de filme*/
        free(info->filmes[i]);

    }
    /* free no vetor de filmes */
    free(info->filmes);
    /* free na aresta */
    free(info);

}

void liberarGrafo(tgrafo *grafo){

    int i;

    adj *aux;
    adj *aux_pr;

    for(i = 0; i<grafo->num_vertices; i++){

        aux = grafo->vet[i].inicio;

        while(aux != NULL){  
            aux_pr = aux->prox;

            liberarAresta(aux->info);

            free(aux);
            aux = aux_pr;
        }

    }

    free(grafo->vet);


    free(grafo);    

}



void menu(){

    printf("\n===== MUNDO DE KEVIN BACON =====\n");
    printf("\nOperacoes: \n");
    printf("1 - Iniciar grafo\n");
    printf("2 - Numero de Kevin Bacon(KB)\n");
    printf("3 - Media e DP do mundo\n");
    printf("4 - Finalizar operacoes\n");
    printf("Opcao: ");
}

char **quebra_entradas(char buffer[]){

   char* temp;
   char** result;
   unsigned int tamanho = 1;
   char tam[6];

    /* primeiro split*/
   temp = strtok(buffer,"/");
   if(temp != NULL){

   		result = (char**)malloc((tamanho+1)*sizeof(char**));
   		result[tamanho++] = temp;

   }

    /* slipts seguintes */
	while((temp = strtok(NULL, "/")) != NULL){

   		result = (char**)realloc(result,(tamanho+1)*sizeof(char**));
   	    result[tamanho++] = temp;   

   }
    /* adiciona o tamanho do vetor na primeira posicao*/
	sprintf(tam,"%d",tamanho);
	long unsigned int t = strlen(tam);
	temp = (char*)malloc((t+1)*sizeof(char));
	strcpy(temp,tam);
   	result[0] = temp;
	
    /*retorna o vetor com as strings dos nomes(artista e filme)*/
	return result;

}

void pesquisarArtista(tgrafo *grafo){

    tvertice nome;
    lista_Adj *pos;
    int primeiro = 1;
    long unsigned int t;
    printf("\nDigite o ator/atriz que deseja procurar: ");
    
    setbuf(stdin, NULL);
    fgets(nome, TAM_NOME, stdin);
    
    /*trata a string de entrada, removendo o '\n'*/
    t = strlen(nome);
    if(nome[t-1] == '\n')
        nome[t-1] = '\0'; 

    printf("\n");

    /* nao para enquanto n enquanto n encontrar o Kevin Bacon*/
    while(strcmp("Bacon, Kevin",nome)!=0){

        pos = verificarVertice(grafo,nome);

        if(pos == NULL){
            printf("Ator/Atriz nao econtrado\n");
            break;
    
        }else{
        
            adj *aux, *aux_menor;

            aux = pos->inicio;
            aux_menor = aux;

            /* percorre a lista de adjacencia e encontra o vertice com menor KB*/
            while(aux != NULL){

                if(strcmp("Bacon, Kevin", aux->nome) == 0)
                    break;
                if(aux_menor->info->KB > aux->info->KB)
                    aux_menor = aux;

                aux = aux->prox;
            }

            /* se for o primeiro print*/
            if(primeiro){
                printf("%s tem KB = %d\n", nome, aux_menor->info->KB);
                primeiro = 0;
            }

            printf("%s atuou em %s com %s\n", nome, aux_menor->info->filmes[0],aux_menor->nome);
            
            /*atualiza o vertice seguinte que sera percorrido*/
            strcpy(nome,aux_menor->nome);
        }
               
    
    }

        return;


}

void inserirArtistas(tgrafo *grafo, FILE *fp){

    long unsigned int t, tam_f;
    int i, tam, j, retAresta;
    /* Buffer de leitura de linha */
    char buffer[TAMBUFFER];
    /* linha quebrada por '/' */
	char **linha;
    /* filmes */
    char **filmes = (char**)malloc(sizeof(char*));

    taresta info;
    info.KB = -1;

    /* leitura das linha */
    while(fgets(buffer,TAMBUFFER,fp)!=NULL){
        
        /* remover \n */
        t = strlen(buffer);
        if(buffer[t-1] == '\n')
            buffer[t-1] = '\0';

		linha = quebra_entradas(buffer);

        /*qtd de elementos*/
		tam = atoi(linha[0]);
       
        /* tratando nome do filme a ser adicionado na aresta */
        tam_f     = strlen(linha[1]);
        filmes[0] = (char*)malloc((tam_f+1)*sizeof(char));

        if(filmes[0] == NULL)
            return;

        strcpy(filmes[0],linha[1]);
        info.filmes = filmes;


		/*printf("%s\n",info.filmes[0]);*/


        /* insere vertices */
        for(i = 2; i<tam; i++)
            inserirVertice(grafo,linha[i]);
        
        
        /* insere arestas */
        for(j = 2; j<tam; j++){
            for(i = 2; i<tam; i++){
                if(i != j){
                    retAresta = inserirArestaFilme(grafo,linha[j],linha[i],info);
            
                    if(!retAresta)
                        printf("\nProblema na insercao de aresta\n");
                    }
            }
        }


        

        /*liberarLinha(linha,tam);*/
        free(filmes[0]);
        free(linha[0]);
        free(linha);
	}

    free(filmes);


}

double calculoDP(tgrafo *grafo, double media){


    int i, soma = 0, minino_KB;

    adj *aux;

    /*percorre todas as listas de adjacencias presente em v e pega o menor KB e realiza a soma do quadrado da dif entre a media*/
    /* desconsidera o vertice do KB */
    for(i=0; i<grafo->num_vertices;i++){

        if(strcmp(grafo->vet[i].nome,"Bacon, Kevin")!=0){

            aux = grafo->vet[i].inicio;

            minino_KB = 1000000;

            while(aux != NULL){

                if(minino_KB>aux->info->KB)
                    minino_KB = aux->info->KB;

                aux = aux->prox;
            }

            soma+=pow(minino_KB-media,2);
        }
    }

    /*printf("%f", (double)soma/(grafo->num_vertices-1));
    */
    return sqrt((double)soma/(grafo->num_vertices-1));



}

double calculoMedia(tgrafo *grafo){

    int i;

    adj *aux;

    double soma = 0;

    int minino_KB;

    /*percorre todas as listas de adjacencias presente em v e pega o menor KB e soma*/
    /* desconsidera o vertice do KB */
    for(i=0; i<grafo->num_vertices;i++){

        if(strcmp(grafo->vet[i].nome,"Bacon, Kevin")!=0){

            aux = grafo->vet[i].inicio;
            minino_KB = 1000000;
            while(aux != NULL ){

                if(minino_KB>aux->info->KB)
                    minino_KB = aux->info->KB;

                aux = aux->prox;
            }
           /* printf("%d ", minino_KB);*/
            soma+=minino_KB;
        }
    
    }


    /*retorna a media*/
    return (double)soma/(grafo->num_vertices-1);



}

void calculoKB(tgrafo *grafo){

    if(grafo == NULL)
        return;

    int i, grau;

    tvertice atual;
    tvertice anterior;

    adj *aux;

    /* guardara os artistas que ja foram percorridos */
    tvertice artistasEnc[MAXVERTICES];
    /* guardara os artitas que necessitam ser percorridos */
    tvertice artistasAPer[MAXVERTICES];
    /*guardara os artistas anteriores aquele que ta sendo analisado*/
    tvertice artistasAnter[MAXVERTICES];
    /* guardara o grau de distancia a serem adicionados */
    int KBs[MAXVERTICES];

    /* a primeira posicao dos vetores guarda a qtd de elementos no vetor*/

    /* Iniciando os vetores com as informacoes iniciais */
    strcpy(artistasEnc[1],"Bacon, Kevin");
    strcpy(artistasEnc[0],"2");

    strcpy(artistasAPer[1],"Bacon, Kevin");
    strcpy(artistasAPer[0], "2");
    
    strcpy(artistasAnter[1],"");
    strcpy(artistasAnter[0],"2");

    KBs[0] = 2;
    KBs[1] = 1;

    /* quantidade de artistas a serem percorridos */
    int tam = atoi(artistasAPer[0]);

    /* enquanto tiver artista para ser percorrido*/
    /* percorre na listas de adjacencia seguindo uma logica BFS */
    while(tam>1){

        /* pop da "fila" de artista a percorrer*/
        strcpy(atual, artistasAPer[1]);
        removePrim(artistasAPer);

        /* pop da "fila" do KB referente a esse artista */
        grau = KBs[1];
        for(i = 1; i<(KBs[0]-1);i++)
            KBs[i] = KBs[i+1];
        KBs[0]--;

        /*pop da "fila" de artista anterior*/
        strcpy(anterior, artistasAnter[1]);
        removePrim(artistasAnter);        

        
        /* percorre na lista de adjacencia referente ao tvertice atual*/
        aux = primeiro_adj(atual, grafo);
        
        while(aux!=NULL){
            
            /* se ainda n foi preenchido */
            if(aux->info->KB == -1){

                /* se for o no for referente ao tvertice anterior atribui grau-1*/
                if(strcmp(aux->nome,anterior) == 0)
                    aux->info->KB = grau-1;
                else{
                    aux->info->KB = grau;

                    /*se esse artista ainda n foi econtrado*/
                    if(!existe(artistasEnc,aux->nome)){
                        
                        /*adiciona na fila(no fim) */
                        adicionaFim(artistasAPer,aux->nome);                
                        adicionaFim(artistasAnter,atual);
                        adicionaFim(artistasEnc,aux->nome);
                        KBs[KBs[0]] = grau+1;
                        KBs[0]++;

                    }
               
                }


            }

            aux = aux->prox;
        }
        /* atualiza o tam */
        tam = atoi(artistasAPer[0]);
/*
        for(i=0; i<tam; i++)
            printf("%s| ",artistasAPer[i]);
        
        printf("\n");
*/
    }

}

int existe(tvertice artistas[], tvertice v){

    int i, tam = atoi(artistas[0]);

    for (i = 1; i < tam; i++){
        if(strcmp(artistas[i],v) == 0)
            return 1;
    }
    
    return 0;

}

void removePrim(tvertice artistas[]){

    int i, tam;

    tam = atoi(artistas[0]);

    for(i = 1; i<tam-1; i++){
        strcpy(artistas[i], artistas[i+1]);
    }

    
    sprintf(artistas[0],"%d",tam-1);


}

void adicionaFim(tvertice artistas[], tvertice v){

    int tam = atoi(artistas[0]);

    strcpy(artistas[tam], v);

	sprintf(artistas[0],"%d",tam+1);



}
