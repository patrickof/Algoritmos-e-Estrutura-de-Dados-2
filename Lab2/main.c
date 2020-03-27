// NOME: Patrick Oliveira Feitosa
// NUSP: 10276682
// DISCIPLINA: ALGORITMOS E ESTRUTURA DE DADOS 2
// TRABALHO: LABORATORIO 2

//Inclusao de bibliotecas necessarias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

//Definicao de constantes
#define TAM 16
#define DEL '*'



typedef int tipoChave;


//Estrutura dos registradores do arquivo
typedef struct{
    tipoChave n_usp;
    char nome[10];
    char sobrenome[10];
    char curso[20];
    float nota;

}tipoAluno;

//Estrutura dos registradores do indices
typedef struct{
    tipoChave chave;
    int pos;

}index;

// ======= FUNCOES DESENVOLVIDAS =======
void menu(); // Printa o menu no terminal
void criaArquivos(FILE *fp, FILE *fpi);// Cria os arquivos de dados e indices
void leituraAlunos(FILE *fp); //Le os alunos presentes no arquivo de dados
void cadastrarAluno(FILE *fp, index *indices, int *p_qtd); //Cadastra um aluno arquivo de dados e no vetor de indices
void pesquisarAluno(FILE *fp, index *indices, int *p_qtd); //Pesquisa um aluno no arquivo de dados
void removerAluno(FILE *fp,index *indices ,int *p_qtd); // Remove um aluno do arquivo de dados
void finalizarExecucao(FILE *fp, FILE *fpi, index *indices, int qtd, int flag); // Finaliza os ponteiros de arquivos e atualiza o arquivo de indices

index *lerIndices(FILE *fpi, int *p_qtd); //Le o arq de indices
int pesquisarIndices(index *indices, int qtd, int *pos_arq); //Pesquisa uma chave no vetor de indices
int inserirIndices(index *indices, index indice, int *p_qtd);// Inseri um indices no vetor de indices
int removerIndices(index *indices,int qtd, int pos_ind); // Remove um indice do vetor de indices
void gravarIndices(FILE *fpi, index *indices, int qtd, int flag); //Grava o vetor de indices no arq de indices

void menu(){

    printf("\n===== REGISTRO DE ALUNOS =====\n");
    printf("\nOperacoes: \n");
    printf("1 - Cadastrar novo aluno\n");
    printf("2 - Pesquisar um aluno\n");
    printf("3 - Mostrar alunos cadastrados\n");
    printf("4 - Remover aluno\n");
    printf("5 - Finalizar operacoes\n");
    printf("Opcao: ");
}

void criaArquivos(FILE *fp, FILE *fpi){

    //cria os arquivos
    fp  = fopen("alunos.dad", "w");
    fpi = fopen("indices.dad", "w");

    fclose(fp);
    fclose(fpi);

    fp = NULL;
    fpi = NULL;
}

void leituraAlunos(FILE *fp){

    tipoAluno al_aux;
    char aux;

    //move o ponteiro para a posicao inicial do arquivo
    fseek(fp,0,SEEK_SET);

    printf("\n===== ALUNOS CADASTRADOS =====\n");
    //percorre o arquivo enquanto houver registros e pula os que foram deletados
    while(fread(&aux, sizeof(char),1,fp)!=0){
        if(aux != DEL){
            fseek(fp, -sizeof(char),SEEK_CUR);
            fread(&al_aux,sizeof(tipoAluno),1,fp);
            printf("Numero USP: %d\nNome: %s\nSobrenome: %s\nCurso: %s\nNota: %.2f\n\n", al_aux.n_usp, al_aux.nome, al_aux.sobrenome,al_aux.curso,al_aux.nota);
        }else
            fseek(fp, sizeof(tipoAluno)- sizeof(char),SEEK_CUR);
    }
}
void cadastrarAluno(FILE *fp, index *indices, int *qtd){

    tipoAluno al_aux;
    index indice;

    //move o ponteiro par o final do arquivo
    fseek(fp,0,SEEK_END);

    //recebe os dados
    printf("\n===== CADASTRO DE ALUNO =====\n");
    printf("\nDigita o numero USP do aluno: ");
    scanf("%d", &al_aux.n_usp);
    printf("\nDigite o nome do aluno: ");
    scanf("%s", &al_aux.nome);
    printf("\nDigita o sobrenome do aluno: ");
    scanf("%s", &al_aux.sobrenome);
    printf("\nDigita o curso do aluno: ");
    scanf("%s", &al_aux.curso);
    printf("\nDigita a nota do aluno: ");
    scanf("%f", &al_aux.nota);

    //cria uma indice
    indice.chave = al_aux.n_usp;
    indice.pos = (ftell(fp)/sizeof(tipoAluno));


    //se o registro foi escrito no arq de dados e nos indices
    if(fwrite(&al_aux,sizeof(tipoAluno),1,fp) && inserirIndices(indices,indice, qtd)){
        printf("\nAluno gravado com sucesso !\n");
        (*qtd)++;
        }
}

void pesquisarAluno(FILE *fp, index* indices, int *p_qtd){

    //variaveis auxiliares:
    //pos_ind -> pos no arquivo de indices
    //pos_arq -> pos no arquivo de dados
    int pos_ind, *pos_arq;

    pos_arq = (int*)malloc(sizeof(int));

    if(pos_arq == NULL){
        printf("\n ERRO DE ALOCACAO \n");
        return;
    }

    printf("\n===== PESQUISA DE ALUNO =====\n");
    printf("\nDigite o numero USP que deseja pesquisar: ");

    pos_ind = pesquisarIndices(indices, *p_qtd, pos_arq);


    if(pos_ind == -1){//nao foi encotrado no vetor de indices
        printf("\nNenhum aluno foi encontrado\n");
        return;
    }else{

        fseek(fp,sizeof(tipoAluno)*(*pos_arq),SEEK_SET);

        tipoAluno al_encontrado;
        fread(&al_encontrado, sizeof(tipoAluno), 1, fp);//leitura do reg do aluno

        printf("\n\n------Aluno Encontrado-----\n");
            printf("Numero USP: %d\nNome: %s\nSobrenome: %s\nCurso: %s\nNota: %.2f\n", al_encontrado.n_usp, al_encontrado.nome, al_encontrado.sobrenome,al_encontrado.curso,al_encontrado.nota);
    }

    return;
}

void finalizarExecucao(FILE *fp,FILE *fpi, index *indices, int qtd, int flag){

    //grava os indices no arq de indices
    gravarIndices(fpi,indices,qtd,flag);

    //Fecha os arquivos
    fclose(fp);
    fclose(fpi);

    free(indices);

    fpi = NULL;
    fp = NULL;

    return;
}
void removerAluno(FILE *fp, index* indices, int *p_qtd){

    //variaveis auxiliares
    int *pos_arq, pos_ind;

    pos_arq = (int*)malloc(sizeof(int));

    if(pos_arq == NULL){
        printf("\n ERRO DE ALOCACAO \n");
        return;
    }

    printf("\n===== REMOCAO DE ALUNO =====\n");
    printf("\nDigite o numero USP que deseja remover: ");

    pos_ind = pesquisarIndices(indices,*p_qtd,pos_arq);

    fseek(fp, (*pos_arq)*sizeof(tipoAluno), SEEK_SET);

    char aux = DEL;

    if(fwrite(&aux,sizeof(char), 1, fp)!=0 && removerIndices(indices,*p_qtd,pos_ind)){
        printf("\nAluno removido com sucesso !\n");
        (*p_qtd)--;
        }

}
index *lerIndices(FILE *fpi, int *p_qtd){

    //alocacao dos indices
    index *indices = (index*)malloc(TAM*sizeof(index));

    if(indices == NULL){
        printf("\n ERRO DE ALOCACAO \n");
        return indices;
    }

    //variaveis auxiliares
    int qtd_aux = 0; // contador de indices
    char ver_aux; // verificador de indices

    //seta o ponteiro no inicio do arquivo
    fseek(fpi,0,SEEK_SET);

    while(fread(&ver_aux, sizeof(char),1,fpi)!=0){
        if(ver_aux != DEL){
            fseek(fpi, -sizeof(char),SEEK_CUR);
            fread(&indices[qtd_aux],sizeof(index),1,fpi);
            qtd_aux++;
        }
        else
            break;
    }

    *p_qtd = qtd_aux;

    return indices;

}
int pesquisarIndices(index *indices, int qtd, int* pos_arq){//retorna a posicao no vetor de indices e a posicao nos registros


    tipoChave chave_aux;
    scanf("%d", &chave_aux);

    //busca binaria
    int inicio = 0;
    int fim = qtd - 1;
    int meio = (inicio+fim)/2;

    while(inicio <= fim){

        if(indices[meio].chave == chave_aux){

            *pos_arq = indices[meio].pos; //posicao que o aluno está arquivo

            return meio;//retorna a posicao no vetor de indice

        }else if(indices[meio].chave > chave_aux)
            fim = meio-1;
        else
            inicio = meio+1;

        meio = (inicio+fim)/2;

    }

    return -1; //Se nenhuma chave for encontrada retorna -1
}
int inserirIndices(index *indices, index indice, int *qtd){

    //Insercao ordenada
    if(*qtd == 0){
        indices[0] = indice;
        return 1;

    }else{
        int i;
        for(i = 0; i<(*qtd); i++){
            if(indice.chave < indices[i].chave){
                for(int j = *qtd; j>i;j--){//shifto pra direita
                    indices[j] = indices[j-1];
                }
                break;
            }
        }
            indices[i] = indice;
            return 1;
    }
    return 0;
}
int removerIndices(index *indices,int qtd, int pos_ind){

    //shifta todos os indices para a esquerda sobrepondo o indice eliminado
    for(int i = pos_ind; i<qtd-1; i++)
        indices[i] = indices[i+1];

    return 1;
}

void gravarIndices(FILE *fpi,index*indices,int qtd,int flag){

    int del = DEL;
    fseek(fpi,0,SEEK_SET);

    fwrite(indices,sizeof(index),qtd,fpi);

    if(flag == 1) //se a qtd de indices atuaiz for "<" que a qtd inicial e adciona um "*" no fim do arq de indices
        fwrite(&del,sizeof(char),1,fpi);


}

int main(){
    FILE *fp, *fpi;//dados e indices
    index *indices; // guardara os indices

    int qtd = 0;//qtd atual de alunos
    int qtd_i; //qtd inicial de alunos
    int *p_qtd = &qtd;//ponteiro para altera a qtd de alunos
    int com = 1; // controle das opcoes
    int flag = 0; // controle a respeito da qtd de indices

    do{
        fp  = fopen("alunos.dad", "r+");
        fpi = fopen("indices.dad", "r+");

        if(fp == NULL) criaArquivos(fp,fpi);

    }   while(fp == NULL);

    //leitura inicial do indices
    indices = lerIndices(fpi, p_qtd);

    //seta a quantidade inicial de alunos registrados
    qtd_i = qtd;

    //printf("Quantidade de alunos:%d, %d",*p_qtd,qtd);

    while(com>0){

        //print menu
        menu();

        //entrada do comando
        scanf("%d",&com);

        switch(com){
            case 1: //Cadastrar
                if(*p_qtd < TAM)
                    cadastrarAluno(fp,indices,p_qtd);
                break;

            case 2: //Pesquisar
                pesquisarAluno(fp,indices,p_qtd);
                break;

            case 3: //Apresentar
                leituraAlunos(fp);
                break;
            case 4://Remover
                removerAluno(fp,indices,p_qtd);
                break;
            case 5://Finalizar
                if(qtd_i>qtd)//se a qtd de indices foi reduzida
                    flag = 1;
                finalizarExecucao(fp,fpi,indices,qtd,flag);
                return 0;
        }
    }


    return 0;
}
