/* Autor: Patrick Oliveira Feitosa
   Desenvolvimento de uma Arvore B para ordernar indices de um arquivo de Registros
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Ordem da �rvore*/
#define ORDEM 166

/*Defines as flag que definirao para percorrer a arvore*/
#define BUSCA 0    	/* retorna o RRN do registro*/
#define INSERCAO 1 	/* retorna o caminho percorrido at� a folha que ser� inserido*/

/* Estrutura do �ndices */
typedef struct {
	int chave;
	long int RRN_arq;
}
INDICE;

typedef struct{
    INDICE indice_aux;
    long int RRN_n_filho;
}
AUX;

/* Estrutura da Pagina  */
typedef struct {
	int contador;
	INDICE indices[ORDEM-1];
	long int RRN_filhos[ORDEM];
}
PAGINA;

/*Estrutura dos registradores do arquivo*/
typedef struct{
    int n_usp;
    char nome[10];
    char sobrenome[20];
    char curso[20];
    float nota;

}
tipoAluno;


/*=========FUN��ES ARVORE B=========*/
/* Faz um print da pagina atual*/
void printarPagina(PAGINA *pagina_aux){

    printf("\n----------PAGINA ATUAL: ----------\n");
    printf("Contador: %d ",pagina_aux->contador);

    printf("Indices: ");/* CHAVE RRN_ARQ */
    int i;
	for(i = 0; i<pagina_aux->contador; i++)
		printf(" %d %li |", pagina_aux->indices[i].chave, pagina_aux->indices[i].RRN_arq);

	printf(" RRN FILHOS: ");
	for(i = 0; i<ORDEM; i++)
		printf("%li ", pagina_aux->RRN_filhos[i]);
}

/* Zera o contador da pagina e seta -1 nos RRN_filhos */
void resetarPagina(PAGINA *pagina_aux){

    int i;
    pagina_aux->contador = 0; /* zera o contador */

    for(i = 0; i<ORDEM; i++)
        pagina_aux->RRN_filhos[i] = (long int) -1; /* seta -1 nos RRN filhos*/


 }
/* Grava a pagina da arvore na posicao de terminada pelo RRN */
 void gravarPagina(FILE *fi, PAGINA *pagina_aux, long int RRN){
    /* seek para a posicao do RRN*/
    fseek(fi,(RRN)*sizeof(PAGINA),SEEK_SET);
    /* escreve no arquivo */
    fwrite(pagina_aux, sizeof(PAGINA),1,fi);

}

/* Faz uma leitura de uma pagina do arquivo de indices */
int carregarPagina(FILE *fi, PAGINA *pagina_aux, long int RRN){
    /* seek para a posicao do RRN*/
    fseek(fi,RRN*sizeof(PAGINA),SEEK_SET);
    /* l� no arquivo */
   if(fread(pagina_aux,sizeof(PAGINA),1,fi)!=0);
        return 0;

    return 1;
}

 /* Percorre a arvore, retorna o caminho at� a posicao de insercao mais a posicao que o indice deve ser adicionado na arvore*/
long int *percorrerArvore(FILE *fi, PAGINA *pagina_aux, long int RRN_Raiz, int chave, int flag){

	long int *retorno = (long int*)malloc(2*sizeof(long int)); /* aloca o retorno */
	retorno[0] = 2; /*tamanho do vet*/
	retorno[1] = RRN_Raiz; /* adiciona o RRN da Raiz */

	if(carregarPagina(fi,pagina_aux,RRN_Raiz)); /*Carrega a Raiz na mem�ria*/

	if(flag == INSERCAO){
		/* busca binaria*/
		int inicio;
		int fim;
		int meio;
		int encontrou = 0;

		while(1){
            /* faz busca binaria na pagina atual*/
			inicio = 0;
			fim = pagina_aux->contador - 1;
			meio = (inicio+fim)/2;

			while(inicio <= fim){

				if(pagina_aux->indices[meio].chave == chave){
					encontrou = 1;
					break;/* como trata-se de uma insercao, algo errado ocorreu */

				}
				else if(pagina_aux->indices[meio].chave > chave){

					if(meio != 0){
						if(pagina_aux->indices[meio-1].chave < chave)
							break;
					}

					fim = meio-1;
				}else{ /* indices[meio].chave < chave*/

					if(meio < pagina_aux->contador-1){
						if(pagina_aux->indices[meio+1].chave > chave){
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


			if(encontrou){ /* se a chave foi encontrada na insercao h� algo de errado*/
				retorno[0] = (long int)-1;
				break;
			}
			else{		  /* se a chave n�o foi encontrada naquela pagina*/

                /*faz uma realoca��o*/
				retorno = (long int*)realloc(retorno, (retorno[0]+1)*sizeof(long int));

				if(pagina_aux->RRN_filhos[meio] == (long int)-1){/*verifica se chegou na folha*/

					retorno[retorno[0]] = meio; /*adiciono a posicao que indice deve ficar*/
					retorno[0]++;               /*incrementa o tamanho do vetor*/

					break;


				}else{ /* se n chegou na folha, vai para a pagina seguinte*/
					retorno[retorno[0]] = pagina_aux->RRN_filhos[meio]; /*RRN da pagina seguinte*/
					retorno[0]++;

					if(carregarPagina(fi,pagina_aux,pagina_aux->RRN_filhos[meio])) /*carrega a pagina seguinte */
                        printf("\nErro ao carregar pagina\n");
				}
			}
		}
	}
	else{	/* flag == BUSCA*/

		int inicio;
		int fim;
		int meio;
		int encontrou = 0;

		while(1){

			inicio = 0;
			fim = pagina_aux->contador - 1;
			meio = (inicio+fim)/2;

			while(inicio <= fim){

				if(pagina_aux->indices[meio].chave == chave){
					encontrou = 1;
					break;

				}
				else if(pagina_aux->indices[meio].chave > chave){

					if(meio != 0){
						if(pagina_aux->indices[meio-1].chave < chave)
							break;
					}

					fim = meio-1;
				}else{

					if(meio < pagina_aux->contador-1){
						if(pagina_aux->indices[meio+1].chave > chave){
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
			/* aloca o retorno -> RRN do registro ou -1 caso n encontre*/
			retorno = (long int*)malloc(sizeof(long int));

			/*printf("%d ", meio);*/


			if(encontrou){ /* se a chave foi encontrada*/
				retorno[0] = pagina_aux->indices[meio].RRN_arq;
				break;
			}
			else{		  /* se a chave n�o foi encontrada naquela pagina*/

				if(pagina_aux->RRN_filhos[meio] == -1){/*verifica se chegou na folha*/
					retorno[0] = -1;
					break;
				}else /* se n chegou na folha, vai para a pagina seguinte*/
					carregarPagina(fi,pagina_aux,pagina_aux->RRN_filhos[meio]);

			}
		}
	}

	return retorno;


}

 /* Cria uma cabeca para a arvore */
int iniciarArvore(FILE *fi){

    /* Aloca uma pagina para ser a cabeca*/
	PAGINA *cabeca = (PAGINA*)malloc(sizeof(PAGINA));

	if(cabeca != NULL){
		/* Guarda a qtd de elementos na arvores*/
		cabeca->RRN_filhos[0] = 0;
		/* Guarda o RRN da raiz da �rvore;*/
		cabeca->RRN_filhos[1] = 0;

		fseek(fi,0,SEEK_SET);

		if(fwrite(cabeca, sizeof(PAGINA), 1, fi)!= 0)
			return 0;
	}
		return 1;

}

 /* Retorna os valores da cabeca da arvore */
long int* informacoesCabeca(FILE *fi, PAGINA *pagina_aux){  /*Retorna as informa��es de qtd de chaves e o RRN da raiz*/

	fseek(fi, 0, SEEK_SET);

	long int *info = (long int*)malloc(2*sizeof(long int));

	/*info[0] = info[1] = -1;*/

	if(fread(pagina_aux, sizeof(PAGINA), 1,fi)!=0){

		info[0] = pagina_aux->RRN_filhos[0]; /*	Qtd chaves*/
		info[1] = pagina_aux->RRN_filhos[1]; /*	RRN da raiz*/

	}

	return info;

}

 /* Funcao recusriva auxiliar para adicionar um elemento na arvore */
void inserirArvore_aux(FILE *fi, PAGINA *pagina_aux, long int* caminho, long int *info, int pos, AUX *auxiliar){

    if(auxiliar->RRN_n_filho == (long int)-2)/*condicao de parada*/
        return;
    /* posicao que o indice sera adicionado na pagina e RRN da pagina atual*/
    long int pos_insercao, RRN_pagina;

    /*printf("Pagina: %li, Aux: %i %li \n", RRN_pagina, auxiliar->indice_aux.chave, auxiliar->RRN_n_filho);*/

    if(auxiliar->RRN_n_filho == -1){/* primeira insercao*/

        RRN_pagina = caminho[pos-1]; /* RRN da pagina que ser� adicionado*/
        if(carregarPagina(fi,pagina_aux,RRN_pagina))/*carrega a pagina*/
            printf("\nErro ao carregar pagina\n");
        pos_insercao = caminho[pos]; /*posicao que sera adicionado na pagina*/
        pos = pos-2; /*pula pra posicao do RRN da pagina anterior*/

        /* contabiliza que 1 indice ser� adicionado -> foi adicionado aqui pq eu tenho a certeza que essa condi��o ser� satisfeita apenas uma vez*/
        info[0]++;  /* eliminiando a possiilidade de se somar mais de uma vez*/

    }
    else{ /*insercoes em outras paginas*/

        RRN_pagina = caminho[pos];/* RRN da pagina que ser� adicionado*/

        if(carregarPagina(fi,pagina_aux,RRN_pagina))
            printf("\nErro ao carregar pagina\n");

        pos--; /* nova posicao da RRN da pagina anterior*/

        /*pesquisar a posicao - busca binaria*/
        int inicio = 0;
        int fim = pagina_aux->contador - 1;
        int meio = (inicio+fim)/2;

        int chave = auxiliar->indice_aux.chave;

        while(inicio <= fim){

            if(pagina_aux->indices[meio].chave == chave){
                break;

            }
            else if(pagina_aux->indices[meio].chave > chave){

                if(meio != 0){
                    if(pagina_aux->indices[meio-1].chave < chave)
                        break;
                }

                fim = meio-1;
            }
            else{

                if(meio < pagina_aux->contador-1){
                    if(pagina_aux->indices[meio+1].chave > chave){
                        meio+=1;
                        break;
                    }
                }
                else if(meio == fim){
                    meio+=1;
                    break;
                }

                inicio = meio+1;

            }
            meio = (inicio+fim)/2;

            }

        pos_insercao = meio; /*posicao que o indice deve ser adicionado*/

    }

  /*  printf("Pagina: %li, Aux: %i %li \n", RRN_pagina, auxiliar->indice_aux.chave, auxiliar->RRN_n_filho);*/

    /* ---- Inicio das insercoes ----*/
    int i;

    if(pagina_aux->contador < (ORDEM-1)){ /*Se a pagina tiver espa�o*/

        /*shifta os indices*/
        for(i = pagina_aux->contador; i> pos_insercao; i--)
            pagina_aux->indices[i] = pagina_aux->indices[i-1];
        /*adicionar o indice*/
        pagina_aux->indices[pos_insercao] = auxiliar->indice_aux;

        int pos_RRN = pos_insercao+1;

        /*shifta os RRNs*/
        for(i = (pagina_aux->contador+1); i> pos_RRN; i--)
            pagina_aux->RRN_filhos[i] = pagina_aux->RRN_filhos[i-1];
        /*adiciona o RRN*/
        pagina_aux->RRN_filhos[pos_RRN] = auxiliar->RRN_n_filho;

        /* soma 1 ao contador */
        (pagina_aux->contador)++;

        /*printarPagina(pagina_aux);*/

        /* grava a pagina atualizada */
        gravarPagina(fi,pagina_aux,RRN_pagina);

        /* adiciona a condicao de parada*/
        auxiliar->RRN_n_filho = (long int)-2;


    } /*end-if insercao na pagina com espaco*/
     /*quebra de n�*/
    else{
        /*vetor que organizara os indices*/
        INDICE *indices_pagina = (INDICE*)malloc(ORDEM*sizeof(INDICE));

        /*vetor que organizara os RRNs*/
        long int *RRNs_pagina = (long int*)malloc((ORDEM+1)*sizeof(long int));

        /* **Organizac�o dos indices** */
        for(i = 0; i<pagina_aux->contador; i++)
            indices_pagina[i] = pagina_aux->indices[i];

        /* shifta os indices */
        for(i = pagina_aux->contador; i> pos_insercao; i--)
            indices_pagina[i] = indices_pagina[i-1];

        /* adiciona o indice ao vetor indices*/
        indices_pagina[pos_insercao] = auxiliar->indice_aux;

       /* printf("\nNo de quebra: %li\nVetor de indices: ", RRN_pagina);
        //for(int i = 0; i<ORDEM; i++)
          //  printf("%d ", indices_pagina[i].chave);
       // printf("\n");*/

        /* posicao que o RRN deve ser adicionado*/
        int pos_RRN = pos_insercao+1;

        /* **Organizac�o dos RRNs** */
        for(i = 0; i<(ORDEM); i++)
            RRNs_pagina[i] = pagina_aux->RRN_filhos[i];

        for(i = ORDEM; i> pos_RRN; i--)
            RRNs_pagina[i] = RRNs_pagina[i-1];

        /* adiciona o RRN do novo indice */
        RRNs_pagina[pos_RRN] = auxiliar->RRN_n_filho;

        /*printf("Vetor de RRNs: ", RRN_pagina);*/

       /*for(int i = 0; i<(ORDEM+1); i++)
            printf("%d ", RRNs_pagina[i]);*/

        /*printf("\n");*/

        /* reseta a pagina atual */
        resetarPagina(pagina_aux);

        /*Modifica a pagina atual -> adiciona metade dos menores indices*/
        for (i = 0; i < (ORDEM/2); i++)
            pagina_aux->indices[i] = indices_pagina[i];

        /* atualiza o contador da pagina */
        pagina_aux->contador = ORDEM/2;

        /* atualiza os RRNS das paginas filhas */
        for (i = 0; i < ((ORDEM/2)+1); i++)
            pagina_aux->RRN_filhos[i] = RRNs_pagina[i];

       /* printarPagina(pagina_aux);*/

        gravarPagina(fi,pagina_aux, RRN_pagina);

        /*CRIACAO DE UMA NOVA PAGINA -> adiciona a outra metade menos 1 do vetor de indices*/
        /* reseta a pagina atual */
        resetarPagina(pagina_aux);

        /* adiciona o indices que ficaram na nova pagina */
        for (i = (ORDEM/2)+1; i < ORDEM; i++)
            pagina_aux->indices[i-((ORDEM/2)+1)] = indices_pagina[i];

        /* adiciona a quantidade de indices na pagina */
        pagina_aux->contador = ORDEM/2 - 1;

        /* adiciona o restante dos RRNs*/
        for (i = ((ORDEM/2)+1); i < (ORDEM+1); i++)
            pagina_aux->RRN_filhos[i -((ORDEM/2)+1)] = RRNs_pagina[i];

        /* move ponteiro do arquivo pro fim e calcula o RRN*/
        fseek(fi,0,SEEK_END);
        long int RRN_pag_nova = ftell(fi)/sizeof(PAGINA); /* calcula O RRN da nova pagina*/

        /*printarPagina(pagina_aux);*/
        /* grava a pagina */
        gravarPagina(fi,pagina_aux,RRN_pag_nova);

        /*fwrite(pagina_aux,sizeof(PAGINA),1, fi);  grava a nova pagina*/

        if(info[1] == RRN_pagina){/* se quebra for em um n� raiz -> � criada outra pagina*/

            /* calculo no RRN da nova raiz*/
            fseek(fi,0,SEEK_END);
            long int RRN_raiz_nova = ftell(fi)/sizeof(PAGINA);

            resetarPagina(pagina_aux);

            /*adiciona o novo indice*/
            pagina_aux->indices[0] = indices_pagina[ORDEM/2];
			pagina_aux->contador++;

            /*adiciona os RRN da pagina atual e da pagina nova*/
            pagina_aux->RRN_filhos[0] = RRN_pagina;
            pagina_aux->RRN_filhos[1] = RRN_pag_nova;

            /* adiciona a nova posicao da raiz*/
            info[1] = RRN_raiz_nova;

            gravarPagina(fi,pagina_aux,RRN_raiz_nova);

            /*fwrite(pagina_aux,sizeof(PAGINA),1, fi);*/

            auxiliar->RRN_n_filho = -2;



        }
        else{ /*se a quebra for no meio da arvore o indice do meio do vetor sobe*/

            auxiliar->indice_aux = indices_pagina[ORDEM/2];
            auxiliar->RRN_n_filho = RRN_pag_nova;

        }



    }


    /* retorna a pagina anterior*/
    return  inserirArvore_aux(fi, pagina_aux, caminho, info, pos, auxiliar);


}

 /* Insere na arvore */
int inserirArvore(FILE *fi, PAGINA* pagina_aux, long int* info, long int RRN_arq, int chave){

	long int *caminho;


	if(info[0] == 0){/* Arvore sem elemento, sem raiz */

		resetarPagina(pagina_aux); /* zera o contador da pagina e seta -1 nos RRN das paginas filha */

		pagina_aux->contador = 1;
		pagina_aux->indices[0].chave = chave;
		pagina_aux->indices[0].RRN_arq = RRN_arq; /*RRN no arquivo */


		info[0] = info[1] = 1;/* Qtd de elementos = RRN da raiz = 1 */

        fseek(fi,0,SEEK_END);
        long int RRN_pg_nova = ftell(fi)/sizeof(PAGINA);

		gravarPagina(fi,pagina_aux,RRN_pg_nova);
		/*fwrite(pagina_aux,sizeof(PAGINA), 1, fi);*/

	}
	else{ /* Arvore com raiz */

		/*retorna o caminho + pos de insercao -- a ultima pagina lida � a pagina que sera feita a inser��o */
		caminho = percorrerArvore(fi,pagina_aux,info[1],chave,INSERCAO);

		long int tamanho = caminho[0]; /* tamanho do vetor */

		if(tamanho == (long int)-1){
			printf("ERRO: Chave jah existe\n");
			return 0;
		}

        int i;
        /* for(i = 0; i<tamanho; i++)
            printf("%li ", caminho[i]);
        printf("\n"); */

        AUX* auxiliar = (AUX*)malloc(sizeof(AUX));

        auxiliar->indice_aux.chave = chave;
        auxiliar->indice_aux.RRN_arq = RRN_arq;
        auxiliar->RRN_n_filho = -1;

        inserirArvore_aux(fi,pagina_aux,caminho,info,tamanho-1,auxiliar);

    }

    return 1;

}

 /* Busca o aluno */
void buscarAluno(FILE *fp, FILE *fi, PAGINA *pagina_aux, long int *info){

	int chave;

	printf("Digite o numero USP do aluno que deseja procurar: ");
	scanf("%d", &chave);

	long int *RRN_arq = percorrerArvore(fi,pagina_aux,info[1],chave,BUSCA);

	if(RRN_arq[0] == -1)
        printf("\nNenhum aluno foi encontrado\n");

	else{

        fseek(fp,(RRN_arq[0])*sizeof(tipoAluno),SEEK_SET);

        tipoAluno al_encontrado;
        fread(&al_encontrado, sizeof(tipoAluno), 1, fp);/*leitura do reg do aluno*/

        printf("\n\n------Aluno Encontrado-----\n");
            printf("Numero USP: %d\nNome: %s\nSobrenome: %s\nCurso: %s\nNota: %.2f\n", al_encontrado.n_usp, al_encontrado.nome, al_encontrado.sobrenome,al_encontrado.curso,al_encontrado.nota);
    }
    return;
}

 /* Visualiza o estado atual da arvore */
void visualizarArvore(FILE *fi, PAGINA *pagina_aux){

	int RRN = 0;
	int i;
	fseek(fi,0,SEEK_SET);

	while((fread(pagina_aux, sizeof(PAGINA),1,fi))>0){

		if(RRN == 0){

			printf("Qtd elem: %li ", pagina_aux->RRN_filhos[0]);
			printf("RRN da Raiz: %li", pagina_aux->RRN_filhos[1]);

			printf("\n");

		}else{
			printf("----------RRN: %i ----------\n", RRN);
			printf("Contador: %d ",pagina_aux->contador);

			printf("Indices: ");
			for(i = 0; i<pagina_aux->contador; i++)
				printf(" %d %li |", pagina_aux->indices[i].chave, pagina_aux->indices[i].RRN_arq);

			printf(" RRN FILHOS: ");
			for(i =0; i<(pagina_aux->contador+1); i++)
				printf("%li ", pagina_aux->RRN_filhos[i]);

			printf("\n");
			}
		RRN+=1;

	}
}

 /* Atualiza as informa��es da cabe�a */
void atualizarCabeca(FILE *fi, PAGINA *pagina_aux, long int *info){

	fseek(fi,0,SEEK_SET);

	/*resetarPagina(pagina_aux);*/

	/*depois modificar para n precisar escrever a pagina inteira*/
	pagina_aux->RRN_filhos[0] = info[0];
	pagina_aux->RRN_filhos[1] = info[1];

    gravarPagina(fi,pagina_aux,(long int)0);
	/*fwrite(pagina_aux,sizeof(PAGINA),1,fi);*/


}

/*=========FUN��ES ARQUIVO DE DADOS=========*/

/* Insere o aluno no arquivo de dados e nos indices*/
void inserirAlunos(FILE *fp, FILE *fi, PAGINA* pagina_aux, long int* info, tipoAluno aluno){

    long int RRN_arq;
    /*move o ponteiro par o final do arquivo*/
    fseek(fp,0,SEEK_END);
    
    /* RRN do registro no arquivo de dados */
    RRN_arq = ftell(fp)/sizeof(tipoAluno);


    if(inserirArvore(fi, pagina_aux,info, RRN_arq, aluno.n_usp)){
        if(fwrite(&aluno,sizeof(tipoAluno),1,fp))
            printf("\nAluno gravado com sucesso !\n");

    }

}

 /* Le as informacoes um novo aluno */
void cadastrarAluno(FILE *fp, FILE *fi, PAGINA* pagina_aux, long int* info){

    tipoAluno al_aux;
    long int RRN_arq;
    /*move o ponteiro par o final do arquivo*/
    fseek(fp,0,SEEK_END);

    /*recebe os dados*/
    printf("\n===== CADASTRO DE ALUNO =====\n");

    printf("\nDigita o numero USP do aluno: ");
    scanf("%d", &al_aux.n_usp);
    setbuf(stdin,NULL);

    printf("\nDigite o nome do aluno: ");
    scanf("%[A-Z a-z]", al_aux.nome);
    setbuf(stdin,NULL);

    printf("\nDigita o sobrenome do aluno: ");
    scanf("%[A-Z a-z]", al_aux.sobrenome);
    setbuf(stdin,NULL);

    printf("\nDigita o curso do aluno: ");
    scanf("%[A-Z a-z]", al_aux.curso);
    setbuf(stdin,NULL);

    printf("\nDigita a nota do aluno: ");
    scanf("%f", &al_aux.nota);
    setbuf(stdin,NULL);

 
    /*insere a aluno lido no arquivo de dados e nos indices*/
    inserirAlunos(fp, fi, pagina_aux, info,al_aux);

}

 /* Faz a leitura dos alunos atuais mo arquivo*/
void leituraAlunos(FILE *fp){

    tipoAluno al_aux;

    /*move o ponteiro para a posicao inicial do arquivo*/
    fseek(fp,0,SEEK_SET);

    printf("\n===== ALUNOS CADASTRADOS =====\n");
    /*percorre o arquivo enquanto houver registros e pula os que foram deletados*/
    while(fread(&al_aux,sizeof(tipoAluno),1,fp)!=0){
        printf("Numero USP: %d\nNome: %s\nSobrenome: %s\nCurso: %s\nNota: %.2f\n\n", al_aux.n_usp, al_aux.nome, al_aux.sobrenome,al_aux.curso,al_aux.nota);
    }

}


void criarArquivos(FILE *fp, FILE *fi){

    fp = fopen("dados.txt", "w");
	fi = fopen("index.dat", "w"); /* Criar um arquivo pra leitura*/

	if(iniciarArvore(fi))
		printf("\nErro ao criar a cabeca da arvore\n");

	fclose(fp);
    fclose(fi);

    fp = NULL;
	fi = NULL;

}

void gerar_dados(FILE *fp, FILE *fi, PAGINA *pagina_aux, long int *info, int qtd){

    tipoAluno aluno;

    /*vetor de nomes*/
    char nome[7][10] = {"Patricia","Guilherme","Carlos", "Bruna", "Felipe", "Joao", "Roberta"};
    /*vetor de sobrenomes*/
    char sobrenome[5][20] = {"da Silva", "Almeida", "Gonçalves", "Santos", "Costa" };
    /*vetor de cursos*/
    char curso[5][20] = {"Eng Comp", "BSI", "BCC", "Estatistica","Matematica"}; 

    srand(time(NULL));

    int i, rand_nom, rand_sob, rand_cur;
    float nota;

    /* INSERCAO DOS DADOS*/
    for(i = 0; i<qtd; i++){

        rand_cur = rand() % 7;
        rand_nom = rand() % 5;
        rand_sob = rand() % 5;
        nota = rand() % 10;

        strcpy(aluno.nome, nome[rand_nom]);
        strcpy(aluno.sobrenome, sobrenome[rand_sob]);
        strcpy(aluno.curso, curso[rand_cur]);
        aluno.n_usp = i;
        aluno.nota = nota;

        inserirAlunos(fp,fi,pagina_aux,info,aluno);
        atualizarCabeca(fi,pagina_aux,info);

    }

}

void menu(){

    printf("\n===== REGISTRO DE ALUNOS =====\n");
    printf("\nOperacoes: \n");
    printf("1 - Cadastrar novo aluno\n");
    printf("2 - Pesquisar um aluno\n");
    printf("3 - Mostrar alunos cadastrados\n");
    printf("4 - Finalizar operacoes\n");
    printf("Opcao: ");
}



int main(){

	FILE *fi, *fp;
	int com = 1;
    int qtd_dados_inicial = 10;
	long int *info; /*guardara informacoes da cabeca da arvore*/


	PAGINA* pagina_aux = (PAGINA*)malloc(sizeof(PAGINA)); /*pagina*/

	do{
		fp = fopen("dados.txt","r+"); /* Abre pra leitura e edi��o, mas deve existir*/
		fi = fopen("index.dat","r+"); /* Abre pra leitura e edi��o, mas deve existir*/

		if (fp == NULL) criarArquivos(fp,fi);

	} while(fp == NULL);

    /* recebe as informacoes da cabeca */
    info = informacoesCabeca(fi,pagina_aux);

    /* gera os dados*/
    gerar_dados(fp, fi, pagina_aux, info, qtd_dados_inicial);

    printf("%ld", sizeof(PAGINA)); /**/

	while(com>0){

        menu();

		scanf("%d",&com);

		switch(com){
            case 1: /*Cadastrar*/
                cadastrarAluno(fp, fi, pagina_aux, info);
                atualizarCabeca(fi,pagina_aux,info);
                break;

			case 2: /*Buscar*/
				buscarAluno(fp,fi,pagina_aux,info);
				break;

			case 3: /*Visualizar alunos*/
                leituraAlunos(fp);
				break;
			case 4: /* Encerrar aplica��o */
                com = -1;
                break;
			/*case 5: Visualiza a arvore
                visualizarArvore(fi,pagina_aux);
				break;*/
        }


	}

	free(info);
	fclose(fi);
	free(pagina_aux);

	return 0;
}
