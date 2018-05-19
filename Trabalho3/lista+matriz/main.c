#include <stdio.h>
#include <stdlib.h>
#include "terra_incognita.h"
#include "lista.h"
#include <time.h>
    
int **matriz = NULL;
lista* cel;
int mapa_pos(int x, int y)
{    
    return matriz[x][y];
}

int main(int argc, char *argv[])
{
    clock_t start_t, end_t;
    float total_t;
    start_t = clock();
    char c;
    int id,typus,explo,positio[MAX_EXPLORADORES][2],xmax = 0,ymax=0,xmin=0,ymin=0;
      
    //lista* cel;
    cel = lista_nova(); // criação de lista para as células

    l_elemento* pos; // iniciar apontador para as posições
    pos = cel->inicio;

    intro(argc, argv, &explo, positio); // iniciar comunicações

    celula* aux;                   //iniciar struct tipo celula

    aux = (celula*) malloc (sizeof(celula));
    
    while(1){
        c = explorator(&id,&typus);
        if(c == 'X'){
            break;
        }
        
       switch(c)
        {
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

        aux->type = typus;
        aux->x = positio[id][0]; // criar struct para inserir na lista
        aux->y = positio[id][1];
        lista_insere(cel, aux, NULL);      
    }    
    
    // temos de pesquisar o vetor para saber os extremos. alt e lat*/
    
    int alt = (ymax - ymin)+1; // o gajo não conta o ponto de coordenadas 0 como um ponto
    int lat = (xmax - xmin)+1;

    for(pos = cel->inicio; pos != NULL;pos = pos->proximo){
        pos->valor->x = pos->valor->x-xmin;
        pos->valor->y = pos->valor->y-ymin;
    }
    int i;
    matriz = (int**) malloc((lat)*sizeof(int*));
    for (i = 0; i < (lat); i++) {
        matriz[i] = (int*) calloc((alt), sizeof(int));   
    }
    /*printf("%d\n", i);
    printf("%d %d\n", lat, alt);
    printf("%d %d\n", cel->inicio->valor->x, cel->inicio->valor->y);
    printf("%d\n", matriz[167][221]);*/
    for (pos = cel->inicio; pos != NULL; pos = pos->proximo){
        //printf("%d %d\n ", pos->valor->x, pos->valor->y);
        matriz[pos->valor->x][pos->valor->y] = pos->valor->type;
    }
    lista_apaga(cel);
    //for (int i = 0; i < lat; i++) {printf("%d", matriz[i][i]);}
    
    /* 3) imprime e verifica o mapa
          NOTA: funcao mapa_pos e' o primeiro das funcoes */
    // chamar mapa_pos para pesquisar no nosso metodo de keep o tipo de terreno em x,y
    tabula(*mapa_pos, lat, alt);
    veritas(*mapa_pos, lat, alt);

    for (i = 0; i < (lat); i++) {
        free(matriz[i]);   
    }
    free(matriz);
    matriz = NULL;
    
    /* 4) termina comunicacoes com os exploradores */
    void relinquo();
    free(aux);

    end_t = clock();
    total_t = (double)((end_t - start_t));
    printf("Tempo de execucao: %f", total_t/CLOCKS_PER_SEC);
    return 0;
}