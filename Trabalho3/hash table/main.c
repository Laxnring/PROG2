#include <stdio.h>
#include <stdlib.h>
#include "terra_incognita.h"
#include "tabdispersao.h"
#include <time.h>

#define TABLE_SIZE 1000000
tabela_dispersao *cel;
int xmax = 0, ymax=0, xmin=0, ymin=0;

int mapa_pos(int x, int y)
{    
    int valor;
    char buffer[10];
    sprintf(buffer, "%d %d", x+xmin, y+ymin);
    //printf("%s\n\n", buffer);
    
    if (tabela_existe(cel, buffer) == 1) {
        //  printf("%s", tabela_valor(cel, buffer));
        
        valor = atoi(tabela_valor(cel, buffer));
        return valor;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    /*clock_t start_t, end_t;
    float total_t;
    start_t = clock();*/
    char c, buffer[10], valor;
    int id,typus,explo,positio[MAX_EXPLORADORES][2];
    cel = tabela_nova(TABLE_SIZE, *hash_djbm); // criação de lista para as células

    intro(argc, argv, &explo, positio); // iniciar comunicações

    while(1){
        c = explorator(&id,&typus);
        if(c == 'X'){
            break;
        }
        switch(c) {
            case 'N':
                (positio[id][1]--); break;
            case 'S':
                (positio[id][1]++); break;
            case 'E':
                (positio[id][0]++); break;
            case 'O':
                (positio[id][0]--); break;
        }
        if (positio[id][0] < xmin) xmin = positio[id][0];
        if (positio[id][1] < ymin) ymin = positio[id][1];
        if (positio[id][0] > xmax) xmax = positio[id][0]; // guardar posições extremos
        if (positio[id][1] > ymax) ymax = positio[id][1];

        sprintf(buffer, "%d %d", positio[id][0], positio[id][1]);
        sprintf(&valor, "%d", typus);
        tabela_insere(cel, buffer, &valor);
    }    
    
    // temos de pesquisar o vetor para saber os extremos. alt e lat*/
    
    int alt = (ymax - ymin)+1; // o gajo não conta o ponto de coordenadas 0 como um ponto
    int lat = (xmax - xmin)+1;
    /*for(pos = cel->inicio; pos != NULL;pos = pos->proximo){
        pos->valor->x = pos->valor->x-xmin;
        pos->valor->y = pos->valor->y-ymin;
    }*/

    //for (int i = 0; i < lat; i++) {printf("%d", matriz[i][i]);}
    
    /* 3) imprime e verifica o mapa
          NOTA: funcao mapa_pos e' o primeiro das funcoes */
    // chamar mapa_pos para pesquisar no nosso metodo de keep o tipo de terreno em x,y
    tabula(*mapa_pos, lat, alt);
    veritas(*mapa_pos, lat, alt);
    //mostraTabela(cel);
    /* 4) termina comunicacoes com os exploradores */
    void relinquo();

    /*end_t = clock();
    total_t = (double)((end_t - start_t));
    printf("Tempo de execucao: %f", total_t/CLOCKS_PER_SEC);
    return 0;*/
}