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
FILE *prog_temp;
FILE *cadastro_aluno;
FILE *cadastro_aluno_temp;

// Funções criadas para serem utilizadas durante o programa

const char *menu_opcoes();
const char *hashtag();
const char *realizado_sucesso();
const char *conhecimento_linguagem();
const char *opcao_acrescentar();
int ano_correto(char []);
int matricula_correta(char []);
int matricula_ano_correto(char [], char []);
int limpar_buffer();
int compara_arquivo_prog(FILE *arquivo, char [], char []);
int compara_arquivo_aluno(FILE *arquivo, char [], char []);
int matricula_comp();
int linha_aluno(char []);
int linha_informacoes_gerais();
int linha_aluno_consulta(char []);
int linha_aluno_consulta(char []);
int n_linha_informacoes(char []);
int n_linha_informacoes_1(char []);
void maiusculas(char []);
int quantidade_linguagem_aluno(char []);
void salvar_arquivo_prog(FILE *arquivo, char []);
void salvar_arquivo_aluno(FILE *arquivo, char [], char [], char []);
void salvar_arquivo_aluno_linguagem(FILE *arquivo, char [], int);
void excluir_aluno(int);
void consultar_aluno(int);
void salvar_finalArquivo(char []);
void copia_arquivo();
void copia_arquivo_linguagem(int );
void remover_arquivo();
void arquivo_linguagem_original();


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

	char linguagem[MAX], matricula_cmp[MAX], linguagem_cmp[MAX], aluno_consulta[MAX], buffer_teste[MAX], teste1[MAX], teste2[MAX];
	char ling1[MAX], ling2[MAX], ling3[MAX], alto[MAX], medio[MAX], baixo[MAX];
	int opcao, parar, teste, n_linguagem, opcao_linguagem, linha_exclusao, linha_contagem, linha, linha1,  contador, contador1, contador2;
	int tam_ling;

	char teste_arq[] = "teste_arquivo.txt";
	char temp[] = "alunos_cadastro_temporario.txt";
	char teste_arq1[] = "alunos_cadastro1.txt";
	char teste_arq2[] = "linguagens_copia.txt";
	
	parar = 1;
	n_linguagem = 1;
	contador = 0;
	contador1 = 0;
	contador2 = 0;
	
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
						
						linha_contagem = linha_aluno(aluno.ano_semestre) + 1;
						linha_exclusao = linha_aluno(matricula_cmp);
					
						while(linha_contagem--){

							excluir_aluno(linha_exclusao);

						}

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

				salvar_finalArquivo(aluno.matricula);

				limpar_tela();

				printf("%s", realizado_sucesso());
		
				n_linguagem = 1;

				break;

			case 3: // Consultar aluno

				copia_arquivo();

				printf("Digite a matrícula do aluno: ");
				limpar_buffer();

				scanf("%[^\n]s", aluno.matricula);
				maiusculas(aluno.matricula);


				fflush(stdin);			

				// Identificar se a matricula digitada é correta

				if(matricula_correta(aluno.matricula) == 0){
					
					printf("\nMatricula com ano invalido, favor escrever no formato XX/YYYYYYY com o ano de ingresso válido\n");
					break;


				}else if(matricula_correta(aluno.matricula) == -1){

					printf("\nMatricula invalida, favor escrever no formato XX/YYYYYYY\n");
					break;
				}

				strcpy(matricula_cmp, aluno.matricula);

					
					contador = linha_aluno_consulta(matricula_cmp) - (linha_aluno_consulta(matricula_cmp) - 1);
				
					linha = linha_aluno_consulta(matricula_cmp);

					while(linha--){
			
						consultar_aluno(contador);

					}


					strcpy(teste1, "*");

					strcat(matricula_cmp, teste1);

					linha1 = linha_aluno_consulta(matricula_cmp);

					contador1 = linha_informacoes_gerais() - linha1 + 1;

					while(contador1--){
			
						consultar_aluno(linha1);
			
					}

				// Identificar se a matricula existe no sistema

				if(compara_arquivo_aluno(cadastro_aluno, aluno.matricula, matricula_cmp) != 0){


					cadastro_aluno = fopen("alunos_cadastro1.txt", "r");
				
					if(cadastro_aluno == NULL){
	
						exit(1);

					}

					while(fscanf(cadastro_aluno, " %s", buffer_teste) != EOF){


						printf("%s\n", buffer_teste);

					}

					fclose(cadastro_aluno);

					
				}else{

					printf("\nAluno não encontrado no sistema\n");
			
				}

				void remover_arquivo();

				contador = 0;

				contador1 = 0;

				contador2 = 0;

				break;


			case 4: // Consultar linguagem


				printf("Digite a linguagem: ");
				limpar_buffer();

				scanf("%[^\n]s", linguagem);
				maiusculas(linguagem);

				strcpy(linguagem_cmp, linguagem);

				fflush(stdin);

				// Identifica se a linguagem existe no sistema

				if(compara_arquivo_prog(cadastro_prog, linguagem, linguagem_cmp) == 0){
					
					printf("\nLinguagem não cadastrada no sistema\n");
					break;
					
				}else{

					strcpy(ling1, "1");
					strcpy(ling2, "2");
					strcpy(ling3, "3");

					strcpy(alto, linguagem_cmp);
					strcpy(medio, linguagem_cmp);
					strcpy(baixo, linguagem_cmp);

					// O formato do banco foi salvo diferente, desta forma, a linguagem pesquisada é concatenada para ser varrida

					strcat(alto,ling1);
					strcat(medio,ling2);
					strcat(baixo,ling3);

					tam_ling = quantidade_linguagem_aluno(alto) + quantidade_linguagem_aluno(medio) + quantidade_linguagem_aluno(baixo);

					printf("Quantidade de aluno(s) que sabe(m) %s: %d\n\n", linguagem_cmp, tam_ling);
					printf("Percentual de alunos com o conhecimento alto: %d%%\n", quantidade_linguagem_aluno(alto)*100/tam_ling);
					printf("Percentual de alunos com o conhecimento médio: %d%%\n", quantidade_linguagem_aluno(medio)*100/tam_ling);
					printf("Percentual de alunos com o conhecimento baixo: %d%%\n", quantidade_linguagem_aluno(baixo)*100/tam_ling);
				
				}

				break;

			case 5: // Gerar relatório de linguagens

				copia_arquivo_linguagem(1);
				copia_arquivo_linguagem(2);
				copia_arquivo_linguagem(3);
				

				cadastro_aluno = fopen("alunos_cadastro.txt", "r");
				
					if(cadastro_aluno == NULL){
	
						exit(1);

					}

				prog_temp = fopen("linguagens_copia.txt", "r");
				
					if(prog_temp == NULL){
	
						exit(1);

					}

					while(fscanf(cadastro_aluno, " %s", teste1) != EOF){


						//printf("%s\n", teste1);

					}

					while(fscanf(prog_temp, " %s", teste2) != EOF){


						//printf("%s\n", teste2);

						if(strcmp(teste1, teste2) == 0){


							contador++;

						}

					}

					printf("%d\n", contador);	
					
					fclose(cadastro_aluno);

					fclose(prog_temp);

				
				arquivo_linguagem_original();

				break;

			case 6: // Excluir um aluno

				printf("Digite a matricula no formato XX/YYYYYYY para excluir: ");
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

				strcpy(matricula_cmp, aluno.matricula);

				// Identificar se a matricula existe no sistema

				if(compara_arquivo_aluno(cadastro_aluno, aluno.matricula, matricula_cmp) != 0){

					
					linha_exclusao = linha_aluno(matricula_cmp); // Verificar onde o aluno foi cadastrado no arquivo

					linha_contagem = n_linha_informacoes(matricula_cmp); // Fazer contagem das linhas para exclusao

					while(linha_contagem--){

						excluir_aluno(linha_exclusao);

					}


					printf("\nAluno excluido com sucesso\n");
					
				}else{

					printf("\nAluno não encontrado no sistema\n");
			
				}

				fflush(stdin);


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
	
	return "\n1) Cadastrar uma linguagem de programação\n2) Cadastrar um aluno\n3) Consultar aluno\n4) Consultar linguagem\n5) Gerar relatório de linguagens\n6) Excluir aluno\n7) Sair do programa\n";	

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

	fprintf(arquivo, "%s%d\n", var1, var2);
				
	fclose(arquivo);

}

void salvar_finalArquivo(char var[]){

	FILE *arquivo = fopen("alunos_cadastro.txt", "ab");
				
	if(arquivo == NULL){

		exit(1);

	}

	fprintf(arquivo, "%s*\n", var);
				
	fclose(arquivo);

}

const char * conhecimento_linguagem(void){

	return "\n1 - Alto\n2 - Médio\n3 - Baixo\nDigite a opção: ";


}

const char * opcao_acrescentar(void){

	return "\nDeseja acrescentar uma linguagem para o aluno cadastrado?\n1 - Sim\n2 - Não\nDigite a opção: ";


}

void excluir_aluno(int n_linha){

	char temp[] = "alunos_cadastro_temporario.txt";
	char teste_arq[] = "alunos_cadastro.txt";
	char buffer[MAX];

	int cont;

	cont = 0;

	cadastro_aluno_temp = fopen(temp, "ab");

	if(cadastro_aluno_temp == NULL){

		fclose(cadastro_aluno_temp);
		exit(1);

	}

	cadastro_aluno = fopen(teste_arq, "r");

	if(cadastro_aluno == NULL){

		fclose(cadastro_aluno);
		exit(1);

	}

	while(fscanf(cadastro_aluno, "%s", buffer) != EOF){


		cont++;

		if(cont != n_linha){						

			fprintf(cadastro_aluno_temp, "%s\n", buffer);

		}


	}

			
	fclose(cadastro_aluno);
	fclose(cadastro_aluno_temp);

	remove(teste_arq);
	rename(temp, teste_arq);

}

int linha_aluno(char matricula[]){

	char teste_arq[] = "alunos_cadastro.txt";
	char buffer1[MAX];
	int n;

	n = 0;
	
	cadastro_aluno = fopen(teste_arq, "r");

	if(cadastro_aluno == NULL){

		fclose(cadastro_aluno);
		exit(1);

	}

	strcpy(buffer1, "\n");

	while(fscanf(cadastro_aluno, "%s", buffer1) != EOF){
		
		n++;
					
		if(strcmp(buffer1, matricula) == 0){

			break;

		}
	}

	fclose(cadastro_aluno);	


	return n;

}

int n_linha_informacoes(char matricula[]){

	int cont1, cont2;
	char teste[MAX];

	cont1 = linha_aluno(matricula);

	strcpy(teste, "*");

	strcat(matricula, teste);

	cont2 = linha_aluno(matricula);

	return (cont2 - cont1) + 1;


}

void consultar_aluno(int n_linha){

	char temp[] = "alunos_cadastro_temporario.txt";
	//char teste_arq[] = "alunos_cadastro.txt";
	char teste_arq1[] = "alunos_cadastro1.txt";
	char buffer[MAX];

	int cont;

	cont = 0;

	cadastro_aluno_temp = fopen(temp, "ab");

	if(cadastro_aluno_temp == NULL){

		fclose(cadastro_aluno_temp);
		exit(1);

	}

	cadastro_aluno = fopen(teste_arq1, "r");

	if(cadastro_aluno == NULL){

		fclose(cadastro_aluno);
		exit(1);

	}

	while(fscanf(cadastro_aluno, "%s", buffer) != EOF){

		cont++;

		if(cont != n_linha){						

			fprintf(cadastro_aluno_temp, "%s\n", buffer);

		}

	}

			
	fclose(cadastro_aluno);
	fclose(cadastro_aluno_temp);

	remove(teste_arq1);
	rename(temp, teste_arq1);

}

int linha_aluno_consulta(char matricula[]){

	char teste_arq[] = "alunos_cadastro1.txt";
	char buffer1[MAX];
	int n;

	n = 0;
	
	cadastro_aluno = fopen(teste_arq, "r");

	if(cadastro_aluno == NULL){

		fclose(cadastro_aluno);
		exit(1);

	}

	strcpy(buffer1, "\n");

	while(fscanf(cadastro_aluno, "%s", buffer1) != EOF){
		
		n++;
					
		if(strcmp(buffer1, matricula) == 0){

			break;

		}
	}

	fclose(cadastro_aluno);	


	return n;

}

int linha_informacoes_gerais(){

	char teste_arq[] = "alunos_cadastro1.txt";
	char buffer1[MAX];
	int n;

	n = 0;
	
	cadastro_aluno = fopen(teste_arq, "r");

	if(cadastro_aluno == NULL){

		fclose(cadastro_aluno);
		exit(1);

	}

	strcpy(buffer1, "\n");

	while(fscanf(cadastro_aluno, "%s", buffer1) != EOF){
		
		n++;

	}

	fclose(cadastro_aluno);	


	return n;

}

int n_linha_informacoes_1(char matricula[]){

	int cont1, cont2;
	char teste[MAX];

	cont1 = linha_aluno_consulta(matricula);

	strcpy(teste, "*");

	strcat(matricula, teste);

	cont2 = linha_aluno_consulta(matricula);

	return (cont2 - cont1) + 1;


}

void copia_arquivo(){

	char buffer[MAX];

	FILE *arq_1 = fopen("alunos_cadastro.txt", "r");

	if(arq_1 == NULL){

		fclose(arq_1);
		exit(1);

	}

	FILE *arq_2 = fopen("alunos_cadastro1.txt", "ab");

	if(arq_2 == NULL){

		fclose(arq_2);
		exit(1);

	}

	while(fscanf(arq_1, "%s", buffer) != EOF){					

			fprintf(arq_2, "%s\n", buffer);


	}
			
	fclose(arq_1);
	fclose(arq_2);


}

void remover_arquivo(){

	char teste_arq1[] = "alunos_cadastro1.txt";

	remove(teste_arq1);	

}

int quantidade_linguagem_aluno(char linguagem[]){

	char buffer[MAX];

	int contador = 0;

	cadastro_aluno = fopen("alunos_cadastro.txt", "r");
				
	if(cadastro_aluno == NULL){

		exit(1);

	}

	while(fscanf(cadastro_aluno, " %s", buffer) != EOF){
				

		if(strcmp(buffer, linguagem) == 0){
					
			contador++;

		}

	}

	return contador;

}

void copia_arquivo_linguagem(int nivel){

	char buffer[MAX];

	FILE *arq_1 = fopen("linguagens.txt", "r");

	if(arq_1 == NULL){

		fclose(arq_1);
		exit(1);

	}

	FILE *arq_2 = fopen("linguagens_copia.txt", "ab");

	if(arq_2 == NULL){

		fclose(arq_2);
		exit(1);

	}

	while(fscanf(arq_1, "%s", buffer) != EOF){					

			fprintf(arq_2, "%s%d\n", buffer, nivel);


	}
			
	fclose(arq_1);
	fclose(arq_2);


}


void arquivo_linguagem_original(){

	char temp[] = "linguagens_copia.txt";
	char teste_arq[] = "linguagens.txt";
	char buffer[MAX];

	int cont;

	prog_temp = fopen(temp, "ab");

	if(prog_temp == NULL){

		fclose(prog_temp);
		exit(1);

	}

	cadastro_prog = fopen(teste_arq, "r");

	if(cadastro_prog == NULL){

		fclose(cadastro_prog);
		exit(1);

	}

			
	fclose(prog_temp );
	fclose(cadastro_prog);

	remove(temp);


}

