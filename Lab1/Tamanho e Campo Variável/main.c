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
char *parser(char *buffer, int *pos);
int camp_var_reg_var(tipoAluno aluno, char *buffer);
void criaArquivo(FILE *fp);
void leituraAlunos(FILE *fp);
void cadastrarAluno(FILE *fp);
void pesquisarAluno(FILE *fp);
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

char *parser(char *buffer, int *pos){

    int posi = *pos;

    while(buffer[*pos] != '|')
        (*pos)++;
    buffer[*pos] = '\0';

    (*pos)++;
    return &buffer[posi];
}

int camp_var_reg_var(tipoAluno aluno, char *buffer){
    sprintf(buffer, "%d|%s|%s|%s|%f|", aluno.n_usp,aluno.nome,aluno.sobrenome,aluno.curso,aluno.nota);
    return strlen(buffer);
}

void criaArquivo(FILE *fp){

    //cria o arquivo
    fp = fopen("alunos.dad", "w");

    fclose(fp);
    fp = NULL;
}

void leituraAlunos(FILE *fp){

    tipoAluno al_aux;
    char buffer[1000];//guarda o registro
    char size;//tamanho do registro
    int pos; //guarda a posicao do ponteiro no buffer
    //move o ponteiro para a posicao inicial do arquivo
    fseek(fp,0,SEEK_SET);

    printf("\n===== ALUNOS CADASTRADOS =====\n");

    //percorre o arquivo enquanto houver registros
    while(fread(&size,sizeof(size),1,fp)!=0){
        fread(buffer,size,1,fp);
        pos = 0;
        sscanf(parser(buffer,&pos),"%d",&al_aux.n_usp);
        strcpy(al_aux.nome,parser(buffer,&pos));
        strcpy(al_aux.sobrenome,parser(buffer,&pos));
        strcpy(al_aux.curso,parser(buffer,&pos));
        sscanf(parser(buffer,&pos),"%f",&al_aux.nota);

        printf("Numero USP: %d\nNome: %s\nSobrenome: %s\nCurso: %s\nNota: %.2f\n\n", al_aux.n_usp, al_aux.nome, al_aux.sobrenome,al_aux.curso,al_aux.nota);
    }

}




void cadastrarAluno(FILE *fp){

    tipoAluno al_aux;

    char size, buffer[1000];

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

    //tratamento do resgitro
    size = camp_var_reg_var(al_aux,buffer);

    //escreve o tamanho e depois o registro
    if(fwrite(&size,sizeof(size), 1,fp)){
	    if(fwrite(buffer,size,1,fp))
	        printf("Aluno gravado com sucesso !\n");
    }
}

void pesquisarAluno(FILE *fp){

    //seta o ponteiro no inicio do arquivo
    fseek(fp,0,SEEK_SET);

    //variaveis auxiliares
    int nusp, nusp_aux, pos;
    char size, buffer_aux[10], buffer[1000];//Buffer para leitura do registro

    tipoAluno al_encontrado;

    //entrada de dado
    printf("\n===== PESQUISA DE ALUNO =====\n");
    printf("\nDigite o numero USP que deseja pesquisar: ");
    scanf("%d", &nusp);



    while(fread(&size,sizeof(size),1,fp)!=0){//leitura do numero USP do aluno

    	fread(buffer_aux,sizeof(buffer_aux),1,fp); //lê os primeiros 10 bytes

        pos = 0;
    	sscanf(parser(buffer_aux,&pos),"%d", &nusp_aux);//quebra o nusp e converte pra int

        if(nusp == nusp_aux){//numero usp encontrado

            fseek(fp,-sizeof(buffer_aux),SEEK_CUR);//volta para a pos inicial do registro
            fread(buffer, size, 1, fp);//leitura do reg do aluno

            pos = 0;
            //quebra do registro
            sscanf(parser(buffer,&pos),"%d",&al_encontrado.n_usp);
            strcpy(al_encontrado.nome,parser(buffer,&pos));
            strcpy(al_encontrado.sobrenome,parser(buffer,&pos));
            strcpy(al_encontrado.curso,parser(buffer,&pos));
            sscanf(parser(buffer,&pos),"%f",&al_encontrado.nota);


            printf("\n\n------Aluno Encontrado-----\n");
            printf("Numero USP: %d\nNome: %s\nSobrenome: %s\nCurso: %s\nNota: %.2f\n", al_encontrado.n_usp, al_encontrado.nome, al_encontrado.sobrenome,al_encontrado.curso,al_encontrado.nota);

            return;
        }
        else{//passo restante para o proximo registro
            fseek(fp,size-sizeof(buffer_aux),SEEK_CUR);

        }
    }

    printf("\nNenhum aluno foi encontrado\n");
    return;
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
