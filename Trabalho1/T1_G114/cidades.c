/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "cidades.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

vetor* cidades_load(const char *nomef)
{
  FILE *f;
  f = fopen(nomef, "rb");
  if (f == NULL) return NULL;
  
  vetor *lista_cidades;
  cidade cidade_lida;
  
  lista_cidades = vetor_novo();
  
  while(fread(&cidade_lida, sizeof(cidade_lida), 1, f) == 1) {
    vetor_insere(lista_cidades, cidade_lida, -1);
  }
  
  fclose(f);
  
  return lista_cidades;
}

int cidades_save(const vetor *vec, const char *nomef)
{
  FILE *f;
  f = fopen(nomef, "wb");
  if (f == NULL) return NULL;

  int tamanho, i;
  cidade *cidade_escrever;
  
  tamanho = vetor_tamanho(vec);
  
  for (i = 0; i < tamanho; i++) {
    cidade_escrever = vetor_elemento(vec, i);
    fwrite(cidade_escrever, sizeof(cidade), 1, f);
  }

  fclose(f);
  
  return tamanho;
}

int cidades_peek(const char *nomef, const char *nomecidade, cidade *resultado)
{
	return -1;
}

/*int cidades_poke(const char *nomef, const char *nomecidade, cidade nova)
{
  int i, posicao, tamanho;
  vetor *cidades;
  cidade *cidade_atual;

  cidades = vetor_novo();
  cidades = cidades_load(nomef);
  
  tamanho = vetor_tamanho(cidades);

  for (i = 0; i < tamanho; i++) {
    cidade_atual = vetor_elemento(cidades, i);
    if(!strcmp(cidade_atual->nome, nomecidade)) { // caso: string é igual
      vetor_remove(cidades, i);
      vetor_insere(cidades, nova, i);
      posicao = i;
    }
    else {
      continue;
    }
  }  
  cidades_save(cidades, nomef);
  //libertar memoria dos vetores criados
  free(cidades);

  return posicao;
}*/
int cidades_poke(const char *nomef, const char *nomecidade, cidade nova)
{
FILE *f;
  char str[1000];
  int iterador_cidade, i=0;

  f = fopen(nomef,"r+b");

  while(1){
    
    iterador_cidade = fseek(f,sizeof(cidade) * i, SEEK_SET);

    if(iterador_cidade != 0) return -1; //Caso: cidade não encontrada
    fread(str,sizeof(cidade),1,f);

    if(strcmp(str,nomecidade) == 0){
      iterador_cidade = fseek(f, sizeof(cidade) * i, SEEK_SET);
      if(iterador_cidade != 0) return -1; //Caso: erro na leitura
      
      fwrite(&nova,sizeof(cidade),1,f);
      break;
    }
      i++;
    }

    fclose(f);
    printf("%d", i);
  
  return i;
}

int cidades_resort(vetor *vec, char criterio)
{
  switch (criterio) {
    case 'p':
      //inserir codigo

      break; 
    case 'a':
      // inserir codigo

      break;
    default:
      printf("Opção invalida.\n");
  }
  return -1;
}

char** cidades_similar (vetor *vec, const char *nomecidade, int deltapop, int *nsimilares)
{
  return NULL;
}
