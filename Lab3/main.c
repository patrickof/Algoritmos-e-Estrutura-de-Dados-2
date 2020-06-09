// NOME: Patrick Oliveira Feitosa
// NUSP: 10276682
// DISCIPLINA: ALGORITMOS E ESTRUTURA DE DADOS 2
// TRABALHO: LABORATORIO 3

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

//Estrutura dos registradores do indice primario
typedef struct{
    tipoChave chave;
    int pos;
}index_prim;

//Estrutura dos registradores do indice secundario
typedef struct{
    char chave_sec[10]; //chave secundária
    int inicio;         //inicio da lista invertida
}index_sec;
//Estrutura dos registradores da lista invertida
typedef struct{
    tipoChave chave;  //chave secundária
    int prox;         //posição do proxima chave da lista invertida
}list_inv;


// ======= FUNCOES EM DESENVOLVIMENTO =======
index_sec* lerIndicesSec(FILE *fsec, int *qtd_ind_sec);
list_inv* lerListaInv(FILE *flis, int *qtd_lista);
int inserirIndicesSec(index_sec *indices_sec, list_inv *lista, char* sobrenome, tipoChave n_usp, int *qtd_ind_sec, int *qtd_list);// Inseri um indices no vetor de indices sec e na lista invertida
int removerIndicesSec(index_sec *indices_sec,list_inv *lista, char chave_sec[], int chave_prim); // Remove um indice do vetor de indices
void percorrerListaInv(index_sec *indices_sec, list_inv *lista);
int *pesquisarIndicesSec(index_sec* indices_sec,list_inv* lista, char chave_sec[],int qtd_ind_sec, int *qtd_enc);
void finalizarGravarIndicesSec(FILE *fsec, FILE *flis, index_sec *indices_sec, list_inv *lista,int qtd_ind_sec, int qtd_lista);
void imprimirIndicesSec(index_sec *indices_sec, list_inv *lista, int qtd_ind_sec, int qtd_list);

// ======= FUNCOES DESENVOLVIDAS =======
void menu(); // Printa o menu no terminal
void criaArquivos(FILE *fp, FILE *fpi, FILE *fsec, FILE *flis);// Cria os arquivos de dados e indices
void leituraAlunos(FILE *fp); //Le os alunos presentes no arquivo de dados
void cadastrarAluno(FILE *fp, index_prim *indices_prim, index_sec *indices_sec,list_inv *lista, int *qtd_ind_sec, int *qtd_list, int *qtd_ind_prim); //Cadastra um aluno arquivo de dados e no vetor de indices
void pesquisarAluno(FILE *fp, index_prim* indices, index_sec *indices_sec, list_inv* lista, int *p_qtd, int *qtd_lista, int *qtd_ind_sec); //Pesquisa um aluno no arquivo de dados
void removerAluno(FILE *fp, index_prim* indices_prim, index_sec* indices_sec, list_inv *lista, int *p_qtd, int *qtd_ind_sec); // Remove um aluno do arquivo de dados
void finalizarExecucao(FILE *fp, FILE *fpi, index_prim *indices, int qtd, int flag); // Finaliza os ponteiros de arquivos e atualiza o arquivo de indices

index_prim *lerIndicesPrim(FILE *fpi, int *p_qtd); //Le o arq de indices
int pesquisarIndicesPrim(index_prim *indices, int qtd, int* pos_arq, tipoChave chave_aux); //Pesquisa uma chave no vetor de indices
int inserirIndicesPrim(index_prim *indices, index_prim indice, int *p_qtd);// Inseri um indices no vetor de indices
int removerIndicesPrim(index_prim *indices,int qtd, int pos_ind); // Remove um indice do vetor de indices
void gravarIndicesPrim(FILE *fpi, index_prim *indices, int qtd, int flag); //Grava o vetor de indices no arq de indices

index_sec* lerIndicesSec(FILE *fsec, int *qtd_ind_sec);//le o arquivo de indices secundarios
list_inv* lerListaInv(FILE *flis, int *qtd_lista); //le a lista invertida
int *pesquisarIndicesSec(index_sec* indices_sec,list_inv* lista, char chave_sec[],int qtd_ind_sec, int *qtd_enc);//pesquisa no indice secundario
int inserirIndicesSec(index_sec *indices_sec, list_inv *lista, char* sobrenome, tipoChave n_usp, int *qtd_ind_sec, int *qtd_list);// Inseri um indices no vetor de indices sec e na lista invertida
int removerIndicesSec(index_sec *indices_sec,list_inv *lista, char chave_sec[], int chave_prim); // Remove um indice do vetor de indices
void finalizarGravarIndicesSec(FILE *fsec, FILE *flis, index_sec *indices_sec, list_inv *lista,int qtd_ind_sec, int qtd_lista);

void percorrerListaInv(index_sec *indices_sec, list_inv *lista);
void imprimirIndicesSec(index_sec *indices_sec, list_inv *lista, int qtd_ind_sec, int qtd_list);


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
void criaArquivos(FILE *fp, FILE *fpi, FILE *fsec, FILE *flis){

    //cria os arquivos
    fp    = fopen("alunos.dat", "w");
    fpi   = fopen("index_prim.dat", "w");
    fsec  = fopen("index_sec.dat", "w");
    flis  = fopen("list_inv.dat", "w");


    fclose(fp);
    fclose(fpi);
    fclose(fsec);
    fclose(flis);

    fp   = NULL;
    fpi  = NULL;
    fsec = NULL;
    flis = NULL;
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
void cadastrarAluno(FILE *fp, index_prim *indices_prim, index_sec *indices_sec, list_inv *lista, int *qtd, int *qtd_list, int *qtd_ind_sec){

    tipoAluno al_aux;

    index_prim indice_prim;

    //move o ponteiro par o final do arquivo
    fseek(fp,0,SEEK_END);

    //recebe os dados
    printf("\n===== CADASTRO DE ALUNO =====\n");
    printf("\nDigite o numero USP do aluno: ");
    scanf("%d", &al_aux.n_usp);
    printf("Digite o nome do aluno: ");
    scanf("%s", &al_aux.nome);
    printf("Digite o sobrenome do aluno: ");
    scanf("%s", &al_aux.sobrenome);
    printf("Digite o curso do aluno: ");
    scanf("%s", &al_aux.curso);
    printf("Digite a nota do aluno: ");
    scanf("%f", &al_aux.nota);

    //cria uma indices
    indice_prim.chave = al_aux.n_usp;
    indice_prim.pos = (ftell(fp)/sizeof(tipoAluno));


    //se o registro foi escrito no arq de dados e nos indices
    if(fwrite(&al_aux,sizeof(tipoAluno),1,fp) && inserirIndicesPrim(indices_prim,indice_prim,qtd) && inserirIndicesSec(indices_sec,lista,al_aux.sobrenome, al_aux.n_usp,qtd_ind_sec,qtd_list)){
        printf("\nAluno gravado com sucesso !\n");
        (*qtd)++;
        (*qtd_list)++;
        }
}

void pesquisarAluno(FILE *fp, index_prim* indices, index_sec *indices_sec, list_inv* lista, int *p_qtd, int *qtd_lista, int *qtd_ind_sec){

    //variaveis auxiliares:
    //pos_ind -> pos no arquivo de indices
    //pos_arq -> pos no arquivo de dados
    //qtd_chaves_prim -> qtd de chaves primarias encontradas referente a chave secundaria encontrada
    int pos_ind, *pos_arq, *qtd_chaves_prim;

    //quardará as chaves primarias referente a chave secundaria encontrada
    tipoChave *chaves_prim;

    pos_arq         = (int*)malloc(sizeof(int));
    qtd_chaves_prim = (int*)malloc(sizeof(int));

    if(pos_arq == NULL && qtd_chaves_prim == NULL){
        printf("\n ERRO DE ALOCACAO \n");
        return;
    }
    //pegara a opcao que o usuario deseja
    char entrada;

    printf("\n===== PESQUISA DE ALUNO =====\n");
    printf("\nDeseja pesquisar por (S)obrenome ou (N)umero usp: ");

    setbuf(stdin, NULL);//limpa o buffer
    scanf("%c", &entrada);

    if(entrada == 'S' || entrada == 's'){//se a opcao por sobrenome for escolhida

        char chave_sec[10];

        printf("\nDigite o sobrenome que deseja pesquisar: ");
        scanf("%s", &chave_sec);
        //percorre os indices secundarios e retorna
        chaves_prim = pesquisarIndicesSec(indices_sec, lista,chave_sec ,*qtd_ind_sec,qtd_chaves_prim);

        if(chaves_prim[0] == -1){//se nenhum numero for encontrado encerra a procura
            printf("\nNenhum aluno foi encontrado\n");
            return;
        }
        //quantidade de chaves primarias corresponde a quantidade de alunos com o mesmo numero USP
        pos_arq = (int*)realloc(pos_arq, (*qtd_chaves_prim)*sizeof(int)); //guardará os RRNs no arquivo

        int i = 0;
        while(i<*qtd_chaves_prim){//percorrerá as chaves primarias a procura dos RRNs
            pos_ind = pesquisarIndicesPrim(indices, *p_qtd, &pos_arq[i], chaves_prim[i]);//numero usp
            i++;
        }


    }else if(entrada == 'N' || entrada == 'n'){//se a opcao de pesquisa por nusp for escolhida

        chaves_prim = (tipoChave*)malloc(sizeof(tipoChave));
        printf("\nDigite o numero USP que deseja pesquisar: ");
        scanf("%d", chaves_prim);

        pos_ind = pesquisarIndicesPrim(indices, *p_qtd, pos_arq, *chaves_prim);

        if(pos_ind == -1){//nao foi encotrado no vetor de indices
            printf("\nNenhum aluno foi encontrado\n");
            return;
        }
        *qtd_chaves_prim = 1;
    }else{
        printf("Opcao invalida");
        return;
    }

    int aux = 0;
    //printf(" ->%d ", sizeof(tipoAluno));

    tipoAluno al_encontrado;

    while(aux<*qtd_chaves_prim){

        fseek(fp,(pos_arq[aux])*sizeof(tipoAluno),SEEK_SET);
        fread(&al_encontrado, sizeof(tipoAluno), 1, fp);//leitura do reg do aluno

        printf("\n\n------Aluno Encontrado-----\n");
        printf("Numero USP: %d\nNome: %s\nSobrenome: %s\nCurso: %s\nNota: %.2f\n", al_encontrado.n_usp, al_encontrado.nome, al_encontrado.sobrenome,al_encontrado.curso,al_encontrado.nota);

        aux++;
    }

    return;

}
void finalizarExecucao(FILE *fp,FILE *fpi, index_prim *indices_prim, int qtd, int flag){

    //grava os indices no arq de indices
    gravarIndicesPrim(fpi,indices_prim,qtd,flag);

    //Fecha os arquivos
    fclose(fp);
    fclose(fpi);

    free(indices_prim);

    fpi = NULL;
    fp = NULL;

    return;
}
void removerAluno(FILE *fp, index_prim* indices_prim, index_sec* indices_sec, list_inv *lista, int *p_qtd, int *qtd_ind_sec){

    //variaveis auxiliares
    int *pos_arq, *pos_ind, *qtd_chaves_prim;

    char chave_sec[10];

    tipoChave *chaves_prim;

    qtd_chaves_prim = (int*)malloc(sizeof(int));
    pos_arq = (int*)malloc(sizeof(int));
    pos_ind = (int*)malloc(sizeof(int));

    qtd_chaves_prim = (int*)malloc(sizeof(int));

    if(pos_arq == NULL){
        printf("\n ERRO DE ALOCACAO \n");
        return;
    }
    char entrada;

    printf("\n===== REMOCAO DE ALUNO =====\n");
    printf("\nDeseja remover por (S)obrenome ou (N)umero usp: ");

    setbuf(stdin, NULL);
    scanf("%c", &entrada);

     if(entrada == 'S' || entrada == 's'){

        printf("\nDigite qual eh o sobrenome do aluno que deseja remover: ");
        scanf("%s", &chave_sec);

        chaves_prim = pesquisarIndicesSec(indices_sec, lista,chave_sec ,*qtd_ind_sec,qtd_chaves_prim);

        if(chaves_prim[0] == -1)//se nenhum numero for encontrado encerra a procura
            return;

        //quantidade de chaves primarias corresponde a quantidade de alunos com o mesmo numero USP
        pos_arq = (int*)realloc(pos_arq, (*qtd_chaves_prim)*sizeof(int)); //guardará os RRNs no arquivo
        pos_ind = (int*)realloc(pos_ind, (*qtd_chaves_prim)*sizeof(int)); //posiçoes no arquivo de indices primarios

        int i = 0;
        while(i<*qtd_chaves_prim){//percorrerá as chaves primarias a procura dos RRNs
            pos_ind[i] = pesquisarIndicesPrim(indices_prim, *p_qtd, &pos_arq[i], chaves_prim[i]);//numero usp
            i++;
        }

    }else if(entrada == 'N' || entrada == 'n'){//se a opcao de pesquisa por nusp for escolhida

        chaves_prim = (tipoChave*)malloc(sizeof(tipoChave));

        printf("\nDigite o numero USP do aluno que deseja remover: ");
        scanf("%d", chaves_prim);

        *pos_ind = pesquisarIndicesPrim(indices_prim, *p_qtd, pos_arq, *chaves_prim);

        if(*pos_ind == -1){//nao foi encotrado no vetor de indices
            printf("\nNenhum aluno foi encontrado\n");
            return;
        }
        *qtd_chaves_prim = 1;

    }else{
        printf("Opcao invalida");
        return;
    }

    int aux = 0;
    tipoAluno al_encontrado;

    while(aux<*qtd_chaves_prim){

        fseek(fp,(pos_arq[aux])*sizeof(tipoAluno),SEEK_SET);
        fread(&al_encontrado, sizeof(tipoAluno), 1, fp);//leitura do reg do aluno

        printf("\n------OPCAO:%d------\n",aux);
        printf("Numero USP: %d\nNome: %s\nSobrenome: %s\nCurso: %s\nNota: %.2f\n", al_encontrado.n_usp, al_encontrado.nome, al_encontrado.sobrenome,al_encontrado.curso,al_encontrado.nota);
        aux++;

    }

    if(entrada == 'n' || entrada == 'N')//se a remocao for feita pelo numero usp eh preciso recuperar o nome do sobrenome, pra ser utilizado na remocao idex2
        strcpy(chave_sec, al_encontrado.sobrenome);

    printf("\nQual aluno voce deseja remover ?\n");

    int opcao;
    scanf("%d", &opcao);

    fseek(fp, (pos_arq[opcao])*sizeof(tipoAluno), SEEK_SET);

    char del = DEL;

    if(fwrite(&del,sizeof(char), 1, fp)!=0 && removerIndicesPrim(indices_prim,*p_qtd,pos_ind[opcao])&& removerIndicesSec(indices_sec,lista,chave_sec, chaves_prim[opcao])){
        printf("\nAluno removido com sucesso !\n");
        (*p_qtd)--;
        }

}
index_prim *lerIndicesPrim(FILE *fpi, int *p_qtd){

    //alocacao dos indices
    index_prim *indices = (index_prim*)malloc(TAM*sizeof(index_prim));

    if(indices == NULL){
        printf("\n ERRO DE ALOCACAO \n");
        return indices;
    }

    //variaveis auxiliares
    int qtd_aux = 0; // contador de indices
    char ver_aux; // verifica de indices

    //seta o ponteiro no inicio do arquivo
    fseek(fpi,0,SEEK_SET);

    while(fread(&ver_aux, sizeof(char),1,fpi)!=0){
        if(ver_aux != DEL){
            fseek(fpi, -sizeof(char),SEEK_CUR);
            fread(&indices[qtd_aux],sizeof(index_prim),1,fpi);
            qtd_aux++;
        }
        else
            break;
    }

    *p_qtd = qtd_aux;

    return indices;

}
int pesquisarIndicesPrim(index_prim *indices, int qtd, int* pos_arq, tipoChave chave_aux){//retorna a posicao no vetor de indices e a posicao nos registros

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
int inserirIndicesPrim(index_prim *indices, index_prim indice, int *qtd){

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
int removerIndicesPrim(index_prim *indices,int qtd, int pos_ind){

    //shifta todos os indices para a esquerda sobrepondo o indice eliminado
    for(int i = pos_ind; i<qtd-1; i++)
        indices[i] = indices[i+1];

    return 1;
}
void gravarIndicesPrim(FILE *fpi,index_prim *indices,int qtd,int flag){

    int del = DEL;
    fseek(fpi,0,SEEK_SET);

    fwrite(indices,sizeof(index_prim),qtd,fpi);

    if(flag == 1) //se a qtd de indices atual for "<" que a qtd inicial e adciona um "*" no fim do arq de indices
        fwrite(&del,sizeof(char),1,fpi);


}

int removerIndicesSec(index_sec *indices_sec,list_inv *lista, char chave_sec[], int chave_prim){

    int i = 0; //posição da chave secudária
    int aux;
    while(strcoll(indices_sec[i].chave_sec,chave_sec)!= 0)
        i++;
    aux = indices_sec[i].inicio;

    while(lista[aux].chave != chave_prim)
        aux = lista[aux].prox;

    lista[aux].chave = -1;

    return 1;
}
int *pesquisarIndicesSec(index_sec* indices_sec,list_inv* lista, char chave_sec[],int qtd_ind_sec, int *qtd_enc){

    int  aux;
    int *saida = (int *)malloc(sizeof(int)); //todos os numeros usp com aquele numero usp

    strlwr(chave_sec); //transforma em minisculo

    int i = 0; //posição da chave secudária

    while(strstr(strlwr(indices_sec[i].chave_sec),chave_sec) == NULL){
        if(i==(qtd_ind_sec-1)){
            printf("\nSobrenome nao encontrado\n");
            saida[0] = -1;
            return saida;
        }

        i++;
    }
    aux = indices_sec[i].inicio;

    int pos = 0;

    while(aux != -1){

        if(pos >0)
            saida = (int*)realloc(saida,(pos+1)*sizeof(int));

        if(lista[aux].chave != -1){//condição para se o dado foi excluido
            saida[pos] = lista[aux].chave;
            pos++;
        }

        aux = lista[aux].prox;
    }

    *qtd_enc = pos;

    return saida;
}
void percorrerListaInv(index_sec *indices_sec, list_inv *lista){

    char chave_sec[10];
    int  aux;
    scanf("%s", chave_sec);

    int i = 0; //posição da chave secudária
    while(strcoll(indices_sec[i].chave_sec,chave_sec))
        i++;

    aux = indices_sec[i].inicio;
    while(aux != -1){

        printf("%d|", aux);
        printf("%d|", lista[aux].chave);
        printf("%d ", lista[aux].prox);

        aux = lista[aux].prox;
    }



}
index_sec* lerIndicesSec(FILE *fsec, int *pqtd_ind_sec){

    index_sec *indices_sec = (index_sec*)malloc(TAM*sizeof(index_sec));

    if(indices_sec == NULL){
        printf("\n ERRO DE ALOCACAO \n");
        return indices_sec;
    }

    //variaveis auxiliares
    int qtd_aux = 0; // contador de indices
    //seta o ponteiro no inicio do arquivo
    fseek(fsec,0,SEEK_SET);

    while(fread(&indices_sec[qtd_aux], sizeof(index_sec),1,fsec)!=0){
        qtd_aux++;
    }


    *pqtd_ind_sec = qtd_aux;

    return indices_sec;



}
list_inv* lerListaInv(FILE *flis, int *qtd_lista){

    list_inv *lista = (list_inv*)malloc(TAM*sizeof(list_inv));

    if(lista == NULL){
        printf("\n ERRO DE ALOCACAO \n");
        return lista;
    }

    int qtd_aux = 0;
    //seta o ponteiro no inicio do arquivo
    fseek(flis,0,SEEK_SET);

    while(fread(&lista[qtd_aux], sizeof(list_inv),1,flis)!=0){
        qtd_aux++;
    }


    *qtd_lista = qtd_aux;

    return lista;


}
void finalizarGravarIndicesSec(FILE *fsec, FILE *flis, index_sec *indices_sec, list_inv *lista,int qtd_ind_sec, int qtd_lista){

    fsec = fopen("index_sec.dat", "w");
    flis = fopen("list_inv.dat", "w");

    fseek(fsec,0,SEEK_SET);
    fwrite(indices_sec,sizeof(index_sec),qtd_ind_sec,fsec);

    fseek(flis,0,SEEK_SET);
    fwrite(lista,sizeof(list_inv),qtd_lista,flis);

    fclose(fsec);
    fclose(flis);
    free(indices_sec);
    free(lista);

}
void imprimirIndicesSec(index_sec *indices_sec, list_inv *lista, int qtd_ind_sec, int qtd_list){

    printf("\nIndices Secundarios:\n\n");
    printf("Pos|Chave Secundaria|Inicio da lista\n");
    for(int i=0; i<qtd_ind_sec; i++){
        printf("%d|", i);
        printf("%s|", indices_sec[i].chave_sec);
        printf("%d\n", indices_sec[i].inicio);
    }
    printf("\n========================\n");

    printf("Lista Invertida:\n\n");
    printf("Pos|Chave Primaria|Prox\n");
    for(int i=0; i<qtd_list; i++){
        printf("%d|", i);
        printf("%d|", lista[i].chave);
        printf("%d\n", lista[i].prox);
    }


}
int inserirIndicesSec(index_sec *indices_sec, list_inv *lista, char* sobrenome, tipoChave n_usp, int *qtd_ind_sec, int *qtd_list){


    index_sec indice_sec_aux;

	//Inserir ordenado o sobrenome
    //Adiciona o indice na lista
	list_inv indice_list_aux = {n_usp,-1};
	lista[*qtd_list] = indice_list_aux;


	//quebra o sobrenome (split)

    if(*qtd_ind_sec == 0){//Se não houver nenhum indice secundario

        strcpy(indice_sec_aux.chave_sec,sobrenome);
        indice_sec_aux.inicio = (*qtd_list);

        indices_sec[0] = indice_sec_aux;
        (*qtd_ind_sec)++;

        return 1;

    }else{ //Se já possuir indice secundário
        int i;
        for(i = 0; i<*qtd_ind_sec;i++){//percorrera os indices secundarios

            if(strcoll(indices_sec[i].chave_sec,sobrenome)>0) {// Se o indice a ser adicionado vem primeiro do atual

                for(int j = *qtd_ind_sec;  j>i ; j--)//shifto pra direita todos os indices secundarios
                        indices_sec[j] = indices_sec[j-1];
                break;//finaliza o for para a

            }else if(strcoll(indices_sec[i].chave_sec,sobrenome)==0){//possui um sobrenome semelhante no arquivo de indices

            //guardará os indices das posições na lista
            int aux = indices_sec[i].inicio;
            //guarda a posição anterior da lista
            int ant = aux;
            //percorre a lista de chave primaria de uma chave secundaria
            while(aux != -1){
                if(lista[aux].chave>lista[*qtd_list].chave)
                    break;
                ant = aux;
                aux = lista[aux].prox;

            }//adiciona o registro no meio da lista lógica
            if(aux == ant){//adiciona o registro no meio da lista lógica
                indices_sec[i].inicio = *qtd_list;
                lista[*qtd_list].prox = aux;

            }else{//adiciona o registro no meio e fim da lista lógica
                int v_aux = lista[ant].prox;
                lista[ant].prox = *qtd_list;
                lista[*qtd_list].prox = v_aux;

                }
            return 1; //Finaliza a inserção de um indice secundario existente
        }

	}
        strcpy(indice_sec_aux.chave_sec,sobrenome);
        indice_sec_aux.inicio = (*qtd_list);

        indices_sec[i] = indice_sec_aux;
        (*qtd_ind_sec)++;
        return 1;
    }
    return 0;
}


int main(){
    FILE *fp, *fpi, *fsec, *flis;//dados e indices
    index_prim *indices_prim; // guardara os indices

    index_sec *indices_sec;
    list_inv *lista;

    int qtd = 0;//qtd atual de alunos
    int qtd_i; //qtd inicial de alunos
    int *p_qtd = &qtd;//ponteiro para altera a qtd de alunos

    int com = 1; // controle das opcoes
    int flag = 0; // controle a respeito da qtd de indices

    int qtdlista = 0;
    int *qtd_lista = &qtdlista;

    int qtd_sec = 0;
    int *qtd_ind_sec = &qtd_sec;

    do{
        fp   = fopen("alunos.dat", "r+");
        fpi  = fopen("index_prim.dat", "r+");
        fsec = fopen("index_sec.dat", "r+");
        flis = fopen("list_inv.dat", "r");


        if(fp == NULL) criaArquivos(fp,fpi,fsec,flis);



    }   while(fp == NULL);

    //leitura inicial do indices
    indices_prim = lerIndicesPrim(fpi, p_qtd);
    indices_sec  = lerIndicesSec(fsec,qtd_ind_sec);
    lista        = lerListaInv(flis,qtd_lista);


    //seta a quantidade inicial de alunos registrados
    qtd_i = qtd;

   // printf("Quantidade de alunos:%d, %d",*qtd_ind_sec,*qtd_lista);

    while(com>0){

        char sobre[10];
        int numero;
        //print menu
        menu();

        //entrada do comando
        scanf("%d",&com);


        switch(com){
            case 1: //Cadastrar
                if(*p_qtd < TAM)
                    cadastrarAluno(fp,indices_prim,indices_sec,lista,p_qtd,qtd_lista,qtd_ind_sec);
                break;

            case 2: //Pesquisar
                pesquisarAluno(fp,indices_prim,indices_sec,lista,p_qtd,qtd_lista,qtd_ind_sec);
                break;

            case 3: //Apresentar
                leituraAlunos(fp);
                break;
            case 4://Remover
                removerAluno(fp,indices_prim,indices_sec,lista,p_qtd,qtd_ind_sec);
                break;
            case 5://Finalizar
                if(qtd_i>qtd)//se a qtd de indices foi reduzida
                    flag = 1;
                finalizarExecucao(fp,fpi,indices_prim,qtd,flag);
                finalizarGravarIndicesSec(fsec,flis,indices_sec,lista,*qtd_ind_sec,*qtd_lista);
                return 0;
          //  case 7:
            //    imprimirIndicesSec(indices_sec,lista, *qtd_ind_sec,*qtd_lista);
              //  break;
          //  case 8:
            //    percorrerListaInv(indices_sec,lista);
            //    break;
        }
    }


    return 0;
}
