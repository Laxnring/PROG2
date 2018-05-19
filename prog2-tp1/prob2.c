#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"

void imprime(vetor *nome_vetor, int numero_elementos) {
  int i;
  for (i = 0; i < numero_elementos; i++) {
    printf("%s ", nome_vetor->elementos[i].str);
  }
  printf("\n");
}

int apaga_string(vetor *vetor) {
  char str[100];
  printf("Insira uma string please: \n");
  scanf("%s", str);
  int encontrado = vetor_pesquisa(vetor, str);
  if (encontrado != -1) {
    vetor_remove(vetor, encontrado);
    return 0;
  } else return 1;
}

int main(int argc, char const *argv[]) {
  int i;
  int size = 5;
  vetor *novo_vetor;
  char str[100];
// 1
  novo_vetor = vetor_novo();
// 2
  for (i = 0; i < size; i++) {
    scanf("%s", str);
    vetor_insere(novo_vetor, str, i);
  }
// 3
  imprime(novo_vetor, size);
// 4
  if(apaga_string(novo_vetor) != 1){
    size--;
  }
// 5
  imprime(novo_vetor, size);
// 6
  vetor_ordena(novo_vetor);
// 7
  imprime(novo_vetor, size);
// 8

vetor_novissimo = vetor_concatena(novo_vetor, novo_vetor);
imprime(vetor_novissimo, 2*size);

  return 0;
}
