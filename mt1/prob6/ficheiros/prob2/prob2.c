#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	char nome[100];
	int pop2001;
	int pop2012;
}
municipio;

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2.1 ***/
municipio *lerFicheiro(FILE *ficheiro, int *num_municipios)
{
	char nome[100];
	int pop2001, pop2012, contador = 0, i, j;
	municipio *lista, aux;
	lista = 0; //inicializar o pointer
	while (fscanf(ficheiro, "%s %d %d", nome, &pop2001, &pop2012) == 3) {
		lista = realloc(lista, sizeof(municipio)*(contador+1));
		strcpy(lista[contador].nome, nome);
		lista[contador].pop2001 = pop2001;
		lista[contador].pop2012 = pop2012;
		contador++;
	}
	*num_municipios = contador;
	return lista;
}

/*** problema 2.2 ***/
void gerarRelatorio(FILE *ficheiro, municipio *resultados, int num_municipios)
{
	municipio aux;
	int i, j;
	if (!ficheiro || resultados == NULL) return;
	for (i = 0; i < num_municipios; i++) {
		for (j = 0; j < num_municipios-i-1; j++) {
			if (resultados[j].pop2001 - resultados[j].pop2012 < resultados[j+1].pop2001 - resultados[j+1].pop2012) {
				aux = resultados[j];
				resultados[j] = resultados[j+1];
				resultados[j+1] = aux;
			}
		}
	}

	for (i = 0; i < 10; i++) {
		fprintf(ficheiro, "%s, %d\n", resultados[i].nome, resultados[i].pop2001 - resultados[i].pop2012);
		printf("%s, %d\n", resultados[i].nome, resultados[i].pop2001 - resultados[i].pop2012);
	}
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{
	FILE *fin, *fout;
	municipio *resultados;
	int n;

	fin = fopen("municipios.txt", "r");
	if(fin == NULL)
		return 1;

	fout = fopen("relatorio.txt", "w");
	if(fout == NULL)
		return 1;

	resultados = lerFicheiro(fin, &n);
	gerarRelatorio(fout, resultados, n);

	fclose(fin);
	fclose(fout);
	free(resultados);

	return 0;
}