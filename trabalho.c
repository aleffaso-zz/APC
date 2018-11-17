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
const char *conhecimento_linguagem();
const char *opcao_acrescentar();
int matricula_comp();
void maiusculas(char []);
int ano_correto(char []);
int matricula_correta(char []);
int matricula_ano_correto(char [], char []);
int limpar_buffer();
int compara_arquivo_prog(FILE *arquivo, char [], char []);
int compara_arquivo_aluno(FILE *arquivo, char [], char []);
void salvar_arquivo_prog(FILE *arquivo, char []);
void salvar_arquivo_aluno(FILE *arquivo, char [], char [], char []);
void salvar_arquivo_aluno_linguagem(FILE *arquivo, char [], int);
void salvar_finalArquivo();


//Estrutura criada para salvar as informações

typedef struct cadastro{

	char nome[MAX];
	char matricula[MAX];
	char ano_semestre[MAX];
	char aluno_prog[MAX];
	int  conhecimento;

} cadastro;

// Início da função principal

int main(){

	struct cadastro aluno;

	char linguagem[MAX], matricula_cmp[MAX], linguagem_cmp[MAX], buffer[45], teste1[MAX];
	int opcao, parar, teste, n_linguagem, opcao_linguagem;
	
	parar = 1;
	n_linguagem = 1;
	
	while(parar!=0){

		printf("\nEscolha uma opção abaixo e pressione a tecla Enter:\n");
		printf("%s%s%s", hashtag(), menu_opcoes(), hashtag());
		printf("\nOpção: ");

		scanf("%d", &opcao);

		switch(opcao){

			case 1: // Cadastrar uma linguagem de progamação

				printf("Digite a linguagem: ");
				limpar_buffer();

				scanf("%[^\n]s", linguagem);
				maiusculas(linguagem);

				strcpy(linguagem_cmp, linguagem);

				
				// Comparar linguagem dentro do arquivo				

				if(compara_arquivo_prog(cadastro_prog, linguagem, linguagem_cmp) != 0){
					
					printf("\nLinguagem já cadastrada no sistema\n");
					break;
					
				}

				fflush(stdin);

				strcpy(linguagem, linguagem_cmp);

				// Salvar linguagem dentro do arquivo caso não esteja cadastrada

				salvar_arquivo_prog(cadastro_prog, linguagem);
				

				//limpar_tela();

				printf("%s", realizado_sucesso());

				break;

			case 2: // Cadastrar aluno

				printf("Digite a matricula no formato XX/YYYYYYY: ");
				limpar_buffer();

				scanf("%[^\n]s", aluno.matricula);
				

				// Identificar se a matricula digitada é correta

				if(matricula_correta(aluno.matricula) == 0){
					
					printf("\nMatricula com ano invalido, favor escrever no formato XX/YYYYYYY com o ano de ingresso válido\n");
					break;


				}else if(matricula_correta(aluno.matricula) == -1){

					printf("\nMatricula invalida, favor escrever no formato XX/YYYYYYY\n");
					break;
				}

				// Identificar se a matricula existe no sistema

				strcpy(matricula_cmp, aluno.matricula);

				if(compara_arquivo_aluno(cadastro_aluno, aluno.matricula, matricula_cmp) != 0){

					printf("\nMatrícula já cadastrada no sistema\n");
					break;
					
				}

				strcpy(aluno.matricula, matricula_cmp);	

				fflush(stdin);	

				printf("Digite o nome: ");
				limpar_buffer();

				scanf("%[^\n]s", aluno.nome);
				maiusculas(aluno.nome);
				fflush(stdin);	

				printf("Digite o ano e o semestre no formato aaaa/ss: ");
				limpar_buffer();

				scanf("%[^\n]s", aluno.ano_semestre);

				// Identificar se o ano digitado está correto

				if(ano_correto(aluno.ano_semestre) == 0){
					
					printf("\nAno invalido, favor escrever no formato aaaa/ss\n");
					break;


				}else if(ano_correto(aluno.ano_semestre) == -1){

					printf("\nAno invalido, favor escrever no formato aaaa/ss\n");
					break;
				}

				fflush(stdin);

	
				// Identificar se o ano e a matricula são correspondente

				if(matricula_ano_correto(aluno.matricula, aluno.ano_semestre) == 0){

					printf("\nMatricula não corresponde com o ano de ingresso\n");
					break;

				}

				// Salvar as variáveis no arquivo antes de informar as linguagens


				salvar_arquivo_aluno(cadastro_aluno, aluno.matricula, aluno.nome, aluno.ano_semestre);
				
		
				// Laço para cadastrar as linguagens que o aluno tem conhecimento

				while(n_linguagem != 0){

					printf("\nDigite a linguagem de programação conhecida: ");
					limpar_buffer();

					scanf("%[^\n]s", aluno.aluno_prog);
					maiusculas(aluno.aluno_prog);

					strcpy(linguagem_cmp, aluno.aluno_prog);
			
					fflush(stdin);


					// Condição para analisar se a linguagem de programação informada existe no sistema

					if(compara_arquivo_prog(cadastro_prog, linguagem, linguagem_cmp) == 0){

						printf("\nLinguagem não cadastrada no sistema\n");
						//Escrever função para excluir o que foi salvo
						n_linguagem = 0;

					}else{

						printf("Digite o conhecimento do aluno para %s", aluno.aluno_prog);
						limpar_buffer();

						printf("%s",conhecimento_linguagem());
						
						scanf("%d", &aluno.conhecimento);
			
						fflush(stdin);

						printf("%s",opcao_acrescentar());

						limpar_buffer();

						scanf("%d", &opcao_linguagem);
						fflush(stdin);	

						if(opcao_linguagem != 1 ){

							n_linguagem = 0;

						}

						strcpy(aluno.aluno_prog, linguagem_cmp);
						salvar_arquivo_aluno_linguagem(cadastro_aluno, aluno.aluno_prog, aluno.conhecimento);

					}

				}


				if(compara_arquivo_prog(cadastro_prog, linguagem, linguagem_cmp) == 0){
					
					n_linguagem = 1;
					break;

				}

				salvar_finalArquivo();

				printf("%s", realizado_sucesso());

				//limpar_tela();
		
				n_linguagem = 1;

				break;

			case 3: // Consultar aluno

								
				//fseek(cadastro_aluno, 0, SEEK_CUR);

				//fread(buffer, sizeof(buffer), 1, cadastro_aluno);
				//printf("%s\n", buffer);


				break;


			case 4: // Consultar linguagem
				
				printf("Digite a linguagem: ");
				limpar_buffer();

				scanf("%[^\n]s", linguagem);


				fflush(stdin);
				

				break;

			case 5: // Gerar relatório de linguagens

				break;

			case 6: // Excluir um aluno

				break;


			case 7: // Sair do programa

				limpar_tela();

				printf("\nSaindo do programa ...\n\n");
				parar = 0;
				break;

			default: // Valor errado

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

int ano_correto(char ano[]){

	int tamanho;
	tamanho = strlen(ano);

	if(strlen(ano) < 7){
		
		return -1;

	}else if(ano[0] > '2' || ano[4] != '/' || ano[5] != '0' || ano[6] > '2'){

		return 0;
	}else{

		return 1;	

	}

}

int matricula_correta(char mat[]){

	int tamanho;
	tamanho = strlen(mat);

	if(strlen(mat) < 10){

		return -1;

	}else if(mat[0] < '0' || mat[0] > '1' || mat[2] != '/'){

		return 0;
		
	}else{

		return 1;
	
	}

}

int matricula_ano_correto(char matricula[], char ano[]){


	if((matricula[0] == ano[2]) && (matricula[1] == ano[3])){

		return 1;

	}else{
		return 0;
	
	}


}

int compara_arquivo_prog(FILE *arquivo, char var1[], char var2[]){

	int count = 0;

	arquivo = fopen("linguagens.txt", "r");
				
		if(arquivo == NULL){

			exit(1);

		}


	while(fscanf(arquivo, " %s", var1) != EOF){


		if(strcmp(var1, var2) == 0){
							
		count++;

		}

	}

	return count;

	fclose(arquivo);

					
} 

void salvar_arquivo_prog(FILE *arquivo, char var1[]){

	arquivo = fopen("linguagens.txt", "ab");
				
	if(arquivo == NULL){

		exit(1);

	}

	fprintf(arquivo, "%s\n", var1);
				
	fclose(arquivo);

}

int compara_arquivo_aluno(FILE *arquivo, char var1[], char var2[]){

	int count = 0;

	arquivo = fopen("alunos_cadastro.txt", "r");
				
		if(arquivo == NULL){

			exit(1);

		}

	while(fscanf(arquivo, " %s", var1) != EOF){


		if(strcmp(var1, var2) == 0){
							
		count++;

		}

	}

	return count;

	fclose(arquivo);

					
} 

void salvar_arquivo_aluno(FILE *arquivo, char var1[], char var2[], char var3[]){

	arquivo = fopen("alunos_cadastro.txt", "ab");
				
	if(arquivo == NULL){

		exit(1);

	}

	fprintf(arquivo, "%s\n%s\n%s\n", var1, var2, var3);
				
	fclose(arquivo);

}

void salvar_arquivo_aluno_linguagem(FILE *arquivo, char var1[], int var2){

	arquivo = fopen("alunos_cadastro.txt", "ab");
				
	if(arquivo == NULL){

		exit(1);

	}

	fprintf(arquivo, "%s\n%d\n", var1, var2);
				
	fclose(arquivo);

}

void salvar_finalArquivo(){

	FILE *arquivo = fopen("alunos_cadastro.txt", "ab");
				
	if(arquivo == NULL){

		exit(1);

	}

	fprintf(arquivo, "-----------------------------\n");
				
	fclose(arquivo);

}

const char * conhecimento_linguagem(void){

	return "\n1 - Alto\n2 - Médio\n3 - Baixo\nDigite a opção: ";


}

const char * opcao_acrescentar(void){

	return "\nDeseja acrescentar uma linguagem para o aluno cadastrado?\n1 - Sim\n2 - Não\nDigite a opção: ";


}
