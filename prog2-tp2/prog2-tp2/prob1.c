#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int main() {
  FILE *f, *fp;
  char str[100];
  lista *jogos, *lista_sem, *oldies, *lista_junta;
  l_elemento *posicao;
  int i = 0, j, numero_jogos;

  f = fopen("arquivo.txt", "r");
  fp = fopen("oldies.txt", "r");

  jogos = lista_nova();
  lista_sem = lista_nova();
  oldies = lista_nova();
  lista_junta = lista_nova();

  while(fgets(str, sizeof(str), f) != NULL) {
    lista_insere(jogos, str, NULL);
  }
  while(fgets(str, sizeof(str), fp) != NULL) {
    lista_insere(oldies, str, NULL);
  }

  posicao = jogos->inicio;

  //printf("Foram lidos %d jogos\n", numero_jogos);
  //lista_imprime(jogos);

  lista_sem = lista_pesquisa_substring(jogos, "PS2");
  posicao = jogos->inicio;
  for (i = 0; i < lista_sem->tamanho; i++) {
    if (lista_pesquisa(jogos, posicao->str, LISTA_INICIO) != NULL) {
      lista_remove(jogos, posicao);
    }
    posicao = posicao->proximo;
  }
  lista_imprime(jogos);
  lista_junta = lista_concatena(jogos, oldies);
  lista_imprime(lista_junta);

  return 0;
}
