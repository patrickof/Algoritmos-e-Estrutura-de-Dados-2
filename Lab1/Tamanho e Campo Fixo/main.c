#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define TAM 10

typedef struct{
    int n_usp;
    char nome[10];
    char sobrenome[10];
    char curso[20];
    float nota;

}tipoAluno;

void menu();
void criaArquivo(FILE *fp);
void leituraAlunos(FILE *fp);
void cadastrarAluno(FILE *fp);
void pesquisarAluno(FILE *fp);
int verificarTamanho(FILE *fp);
void finalizarExecucao(FILE *fp);


void menu(){

    printf("\n===== REGISTRO DE ALUNOS =====\n");
    printf("\nOperacoes: \n");
    printf("1 - Cadastrar novo aluno\n");
    printf("2 - Pesquisar um aluno\n");
    printf("3 - Mostrar alunos cadastrados\n");
    printf("4 - Finalizar operacoes\n");
    printf("Opcao: ");
}

void criaArquivo(FILE *fp){

    //cria o arquivo
    fp = fopen("alunos.dad", "w");

    fclose(fp);
    fp = NULL;
}

void leituraAlunos(FILE *fp){

    tipoAluno al_aux;

    //move o ponteiro para a posicao inicial do arquivo
    fseek(fp,0,SEEK_SET);

    printf("\n===== ALUNOS CADASTRADOS =====\n");
    //percorre o arquivo enquanto houver registros
    while(fread(&al_aux, sizeof(tipoAluno),1,fp)!=0){
        printf("Numero USP: %d\nNome: %s\nSobrenome: %s\nCurso: %s\nNota: %.2f\n\n", al_aux.n_usp, al_aux.nome, al_aux.sobrenome,al_aux.curso,al_aux.nota);

}
}

void cadastrarAluno(FILE *fp){

    tipoAluno al_aux;

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

    //se o registro foi escritos
    if(fwrite(&al_aux,sizeof(tipoAluno),1,fp))
        printf("Aluno gravado com sucesso !\n");
}

void pesquisarAluno(FILE *fp){

    //seta o ponteiro no inicio do arquivo
    fseek(fp,0,SEEK_SET);

    //variaveis auxiliares
    int nusp, nusp_aux;
    tipoAluno al_encontrado;

    //entrada de dado
    printf("\n===== PESQUISA DE ALUNO =====\n");
    printf("\nDigite o numero USP que deseja pesquisar: ");
    scanf("%d", &nusp);


    while(fread(&nusp_aux, sizeof(int), 1, fp) != 0){//leitura do numero USP do aluno

        if(nusp == nusp_aux){//numero usp encontrado

            fseek(fp,-sizeof(int),SEEK_CUR);//volta para a pos inicial do registro
            fread(&al_encontrado, sizeof(tipoAluno), 1, fp);//leitura do reg do aluno
            printf("\n\n------Aluno Encontrado-----\n");
            printf("Numero USP: %d\nNome: %s\nSobrenome: %s\nCurso: %s\nNota: %.2f\n", al_encontrado.n_usp, al_encontrado.nome, al_encontrado.sobrenome,al_encontrado.curso,al_encontrado.nota);

            return;
        }
        else{//passo restante para o proximo registro
            fseek(fp,(sizeof(tipoAluno)-sizeof(int)), SEEK_CUR);

        }
    }

    printf("\nNenhum aluno foi encontrado\n");
    return;
}

int verificarTamanho(FILE *fp){

    //posiciona o ponteiro no fim
    fseek(fp,0,SEEK_END);

    int qtd;

    qtd = ftell(fp)/sizeof(tipoAluno);

    if(qtd<TAM)
        return 1;
    else{ //qtd>=TAM
        printf("\nTamanho excedido.\n");
        return 0;
    }
}

void finalizarExecucao(FILE *fp){

    fclose(fp);
    fp = NULL;

    return;
}

int main()
{
    FILE *fp;
    int com = 1;

    do{
        fp = fopen("alunos.dad", "r+");

        if(fp == NULL) criaArquivo(fp);

    }   while(fp == NULL);

    while(com>0){

        //print menu
        menu();
        //entrada do comando
        scanf("%d",&com);

        switch(com){
            case 1: //Cadastrar
                if(verificarTamanho(fp))
                    cadastrarAluno(fp);
                break;

            case 2: //Pesquisar
                pesquisarAluno(fp);
                break;

            case 3: //Apresentar
                leituraAlunos(fp);
                break;
            case 4:
                finalizarExecucao(fp);
                return 0;
        }
    }


    return 0;
}
