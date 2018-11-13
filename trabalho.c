/*
	Universidade de Brasília - Campus Gama
	Disciplina: Algoritmo e Programação de Computadores	Turma: FF
	Semestre:2018.2
	Professor: Giovanni Almeida Santos
	Aluno: Áleff Antônio da Silva Oliveira		Matrícula: 13/0042404

											*/

// Bibliotecas utilizadas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Variável global a ser utilizada durante o programa

#define MAX 100
#define limpar_tela() printf("\033[H\033[J")

// Arquivos a serem utilizados durante o programa

FILE *cadastro_prog;
FILE *cadastro_aluno;

// Funções criadas para serem utilizadas durante o programa

const char *menu_opcoes();
const char *hashtag();
const char *realizado_sucesso();
const char *leitura_arquivo(const char *filename);
int matricula_comp();
void maiusculas(char []);
void ano_correto(char []);
void matricula_correta(char []);
int limpar_buffer();


//Estrutura criada para salvar as informações

typedef struct cadastro{

	char nome[MAX];
	char matricula[MAX];
	char ano_semestre[MAX];
	char aluno_prog[MAX];

} cadastro;

// Início da função principal

int main(){

	struct cadastro aluno;

	char linguagem[MAX], matricula_cmp[MAX], buffer[45], teste[MAX];
	int opcao, parar, cont_0, cont_1;
	
	parar = 1;
	
	while(parar!=0){

		printf("\nEscolha uma opção abaixo e pressione a tecla Enter:\n");
		printf("%s%s%s", hashtag(), menu_opcoes(), hashtag());
		printf("\nOpção: ");

		scanf("%d", &opcao);

		switch(opcao){


			// Cadastrar uma linguagem de progamação

			case 1: 

				printf("Digite a linguagem: ");

				limpar_buffer();
				scanf("%[^\n]s", linguagem);
				maiusculas(linguagem);

				fflush(stdin);

				cadastro_prog = fopen("linguagens.txt", "ab");
				
				if(cadastro_prog == NULL){

					printf("\nErro na abertura do arquivo\n");
					exit(1);

				}

				fprintf(cadastro_prog, "%s\n", linguagem);
				
				fclose(cadastro_prog);
				

				limpar_tela();

				printf("%s", realizado_sucesso());

				break;

			// Cadastrar aluno

			case 2:

				printf("Digite o nome: ");
				limpar_buffer();

				scanf("%[^\n]s", aluno.nome);
				maiusculas(aluno.nome);
				fflush(stdin);

				printf("Digite a matricula no formato XX/YYYYYYY: ");
				limpar_buffer();

				scanf("%[^\n]s", aluno.matricula);
				//matricula_correta(aluno.matricula);
				fflush(stdin);


				strcpy(matricula_cmp, aluno.matricula);

				cadastro_aluno = fopen("alunos_cadastro.txt", "r");
				
				if(cadastro_aluno == NULL){

					printf("\nErro na abertura do arquivo\n");
					exit(1);

				}
				
				while(fscanf(cadastro_aluno, " %s", aluno.matricula) != EOF){


					if(strcmp(aluno.matricula,matricula_cmp) == 0){
							
						cont_0++;

					}

				}

				if(cont_0 == 1){

					printf("\nMatrícula já cadastrada no sistema\n");
					fclose(cadastro_aluno);
					cont_0 = 0;
					break;
					
				}

				strcpy(aluno.matricula, matricula_cmp);			

				printf("Digite o ano e o semestre no formato aaaa/ss: ");
				limpar_buffer();

				scanf("%[^\n]s", aluno.ano_semestre);
				//ano_correto(aluno.ano_semestre);
				fflush(stdin);

				printf("Digite a linguagem de programação conhecida: ");
				limpar_buffer();

				scanf("%[^\n]s", aluno.aluno_prog);
				maiusculas(aluno.aluno_prog);
				fflush(stdin);



				// Condição para analisar se a linguagem de programação informada existe no sistema


				cadastro_prog = fopen("linguagens.txt", "r");
				
				if(cadastro_prog == NULL){

					printf("\nErro na abertura do arquivo\n");
					exit(1);

				}
				

				while(fscanf(cadastro_prog, " %s", linguagem) != EOF){


					if(strcmp(aluno.aluno_prog,linguagem) == 0){
							
						cont_1++;

					}

				}


				if(cont_1 == 1){ //Caso o valor do contador seja 1, ele ira cadastrar o aluno no sistema


					cadastro_aluno = fopen("alunos_cadastro.txt", "ab");
				
					if(cadastro_aluno == NULL){

						printf("\nErro na abertura do arquivo\n");
						exit(1);

					}


					fprintf(cadastro_aluno, "%s\n%s\n%s\n%s\n", aluno.matricula, aluno.nome, aluno.ano_semestre, aluno.aluno_prog);
				

					printf("%s", realizado_sucesso());


				}else{

					printf("\nLinguagem não cadastrada no sistema\n");

				}

				fclose(cadastro_prog);
				fclose(cadastro_aluno);
				cont_1 = 0;
				

				//limpar_tela();

				break;

			// Consultar aluno

			case 3:

								
				//fseek(cadastro_aluno, 0, SEEK_CUR);

				//fread(buffer, sizeof(buffer), 1, cadastro_aluno);
				//printf("%s\n", buffer);


				break;

			// Consultar linguagem

			case 4:

				printf("Digite um valor: ");

				limpar_buffer();
				scanf("%[^\n]s", teste);
				matricula_correta(teste);
				

				break;

			// Gerar relatório de linguagens

			case 5:

				break;

			// Excluir um aluno

			case 6:

				break;

			// Sair do programa

			case 7:
				limpar_tela();

				printf("\nSaindo do programa ...\n\n");
				parar = 0;
				break;

			// Valor errado

			default:
				limpar_tela();
				printf("\nEscolha um valor válido\n");
				

		}
		
	}
	
	return 0;

}

const char * menu_opcoes(void){
	
	return "\n1) Cadastrar uma linguagem de programação\n2) Cadastrar um aluno\n3) Consultar aluno\n4) Consultar linguagem\n5) Gerar relatório de linguagens\n6) Excluir relatório de linguagens\n7) Sair do programa\n";	

}

const char * hashtag(void){

	return "\n###################### Sistema AGF ######################\n";

}


const char * realizado_sucesso(void){

	return "\n############ Cadastro Realizado com Sucesso ############\n";

}

int limpar_buffer(void){

	int ch;
	while(((ch=getchar())!=EOF && (ch != '\n')));
	return ch;

}

void maiusculas(char m[]){

	int c = 0;

	while(m[c] != '\0'){

		if(m[c] >= 'a' && m[c] <= 'z'){
			
			m[c] = m[c] - 32;

		}

		c++;
	}

}

void ano_correto(char ano[]){

	int i, count, tamanho;
	count = 0;
	tamanho = strlen(ano);

	if(strlen(ano) < 7){
		
		printf("\nAno invalido, favor escrever no formato aaaa/ss\n");

	}else{

		if(ano[4] != '/' && ano[5] != 0 && (ano[6] != 1 || ano[6] != 0)){

			printf("\nAno invalido, favor escrever no formato aaaa/ss\n");

		}
	}

}

void matricula_correta(char mat[]){

	int i, count, tamanho;
	count = 0;
	tamanho = strlen(mat);

	if(strlen(mat) < 10){
		
		printf("\nMatricula invalida, favor escrever no formato XX/YYYYYYY\n");

	}else{

		if(mat[0] > 1 || mat[2] != '/'){

			printf("\nMatricula com ano invalido, favor escrever no formato XX/YYYYYYY com o ano de ingresso válido\n");

		}
	}

}
