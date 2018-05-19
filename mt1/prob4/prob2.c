#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pilha.h"

#define BUFFER 256

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2 ***/
float* avalia_expressoes(FILE *ficheiro, int *N)
{
	char aux, string_aux[BUFFER];
	pilha *nova_pilha;
	float a, b, r, *resultados;
	nova_pilha = pilha_nova();
	int i, j = 0;
	resultados = 0;
	while(fgets(string_aux, BUFFER, ficheiro) != NULL) {
		for (i = 0; i < strlen(string_aux); i++) {
			aux = string_aux[i];
			if (aux == ' ') continue;
			if (aux >= '0' && aux <= '9') {
				pilha_push(nova_pilha, aux);
			}
			if (aux == '-' || aux == '/' || aux == '+' || aux == '*') {
				b = pilha_top(nova_pilha);
				b = b - '0';
				pilha_pop(nova_pilha);
				a = pilha_top(nova_pilha);
				a = a - '0';
				pilha_pop(nova_pilha);

				switch(aux) {
					case '-':
						r = a - b;
						break;
					case '+':
						r = a + b;
						break;
					case '*':
						r = a * b;
						break;
					case '/':
						r = a / b;
						break;
				}
				pilha_push(nova_pilha, r + '0');
			}
		}
		resultados = realloc(resultados, sizeof(float) * (j+1));
		resultados[j] = r;
		j++;
	}
	*N = j;
	return resultados;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

#define BUFFER 256

int main()
{
	FILE *fin;
	float *resultados;
	char expressao[BUFFER];
	int i, n=0;

	fin = fopen("expressoes.txt", "r");
	if(fin == NULL)
	{
		printf("Erro ao abrir ficheiro.\n");
		return 1;
	}

	if((resultados = avalia_expressoes(fin, &n)) != NULL)
	{
		rewind(fin);
		for(i=0; i<n && fgets(expressao, BUFFER, fin) != NULL; i++)
		{
			expressao[strlen(expressao)-1] = '\0';
			printf("%s -> %f\n", expressao, resultados[i]);
		}
	}
	else
		printf("Funcao retornou erro.\n");

	fclose(fin);

	return 0;
}
