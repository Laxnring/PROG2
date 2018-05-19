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
    municipio *lista_municipios;
    char nome[100];
    int pop2001, pop2012, i = 0;
    lista_municipios = malloc(0);

    while (1) {
        if (fscanf(ficheiro, "%s %d %d", nome, &pop2001, &pop2012) != 3) {
            break;
        } else {
            lista_municipios = realloc(lista_municipios, sizeof(municipio)*(i+1));
            strcpy(lista_municipios[i].nome, nome);
            lista_municipios[i].pop2001 = pop2001;
            lista_municipios[i].pop2012 = pop2012;
            i++;
        }
    }
    *num_municipios = i;
    return lista_municipios;
}

/*** problema 2.2 ***/
void gerarRelatorio(FILE *ficheiro, municipio *resultados, int num_municipios)
{
    int passo, imin, i, perda_pop;
    municipio *perdas, aux;

    for(passo=0; passo < num_municipios - 1; passo++) {
        imin = passo;
        i = passo + 1;
        while (i < num_municipios){
            if (resultados[i].pop2001 - resultados[i].pop2012 > resultados[imin].pop2001 - resultados[imin].pop2012) imin = i;
                i++;
            }
        if (imin != passo) {
            aux = resultados[passo];
            resultados[passo] = resultados[imin];
            resultados[imin] = aux;
        }
    }
    for (i = 0; i < 10; i++) {
        printf("%s, %d\n", resultados[i].nome, resultados[i].pop2001-resultados[i].pop2012);
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
