/*  nome: Patrick Oliveira Feitosa          */
/*  nusp: 10276682                          */
/*  disciplina: Alg. e Estrutura de dados 2 */
/*  atividade: Trabalho 2 - Grafos          */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"


int main(){

    FILE *fp;
    tgrafo *grafo;
    int com = 1, iniciado = 0;
    double media,dp;

    fp = fopen("teste.txt", "r");
    /*fp = fopen("input-top-grossing.txt", "r");*/

    if(fp == NULL)
        return 1;

    while(com != 4){

        menu();

        scanf("%d", &com);


        switch (com){

            case 1: /*inicializacao do grafo/aresta/vertices*/
               
               if(!iniciado){
                    grafo = iniciarGrafo(0);
                    inserirArtistas(grafo,fp);
                   /* calculoKB(grafo,1,"Bacon, Kevin","");*/
                    calculoKB(grafo);
                    iniciado = 1;

                    printf("qtd_vertices: %d",grafo->num_vertices);
                }
               break;
            
            case 2:/*Kb*/
                if(!iniciado)
                    printf("\nErro: Inicie o grafo\n");
                else
                    pesquisarArtista(grafo);
                break;
            
            case 3: /* media/dp */
                if(!iniciado)
                    printf("\nErro: Inicie o grafo\n");
                else{
                    media = calculoMedia(grafo);
                    dp = calculoDP(grafo,media);
                    printf("\nMundo de Kevin Bacon:\nMedia: %f\nDesvio Padrao: %f\n", media,dp);
                }
                break;
            
            case 4: /*finalizando*/
                break;

            case 5: /*finalizando*/
                if(!iniciado)
                    printf("\nErro: Inicie o grafo\n");
                else
                    printarListaAdj(grafo);

                break;

            default:
                printf("\nOpcao invalida\n");
            
        }

    }

    if(iniciado)
        liberarGrafo(grafo);
    fclose(fp);
    return 0;
}