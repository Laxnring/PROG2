#include <stdio.h>
#include <stdlib.h>
#include "terra_incognita.h"
#include "lista.h"
#include <time.h>
    
//int **matriz;
lista* cel;
int mapa_pos(int x, int y)
{    
   l_elemento* pos;
   for(pos = cel->inicio; pos != NULL;pos = pos->proximo){
       if(x == pos->valor->x && y == pos->valor->y){
           return pos->valor->type;
       }
   }
   return 0;
   
    //return matriz[x][y];
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
    
    while(1){
        aux = (celula*) malloc (sizeof(celula));

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
        if(lista_pesquisa(cel,aux,LISTA_INICIO) == NULL){
             lista_insere(cel, aux, NULL);
        }
       
    }    
    
    // temos de pesquisar o vetor para saber os extremos. alt e lat*/
    
    int alt = (ymax - ymin)+1; // o gajo não conta o ponto de coordenadas 0 como um ponto
    int lat = (xmax - xmin)+1;

    for(pos = cel->inicio; pos != NULL;pos = pos->proximo){
        pos->valor->x = pos->valor->x-xmin;
        pos->valor->y = pos->valor->y-ymin;
    }
   /* matriz = (int**) malloc(alt*sizeof(int*));
    for (int i = 0; i < alt; i++) {
        matriz[i] = (int*) calloc(lat,sizeof(int));
        
    }*/

  /*  for (pos = cel->inicio; pos != NULL; pos = pos->proximo){
        
        matriz[pos->valor->x-xmin][pos->valor->y-ymin] = pos->valor->type;
        printf("%d  %d  %d\n",pos->valor->x-xmin,pos->valor->y-ymin,pos->valor->type);
    }*/
   
    //for (int i = 0; i < lat; i++) {printf("%d", matriz[i][i]);}
    /* 3) imprime e verifica o mapa
          NOTA: funcao mapa_pos e' o primeiro das funcoes */
    // chamar mapa_pos para pesquisar no nosso metodo de keep o tipo de terreno em x,y
    tabula(*mapa_pos, lat, alt);
    veritas(*mapa_pos, lat, alt);

    /* 4) termina comunicacoes com os exploradores */
    void relinquo();
    end_t = clock();
    total_t = (double)(end_t - start_t);
    printf("Tempo de execucao: %f", total_t);
    return 0;
}