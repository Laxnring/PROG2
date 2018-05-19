#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  int numero_elementos, contador_pares = 0, contador_impares = 0;
  int i;
  int *elementos, *elementos_pares, *elementos_impares;
  scanf("%d", &numero_elementos);
  elementos = (int*)malloc(sizeof(int) * numero_elementos);
  elementos_pares = (int*)malloc(0);
  elementos_impares = (int*)malloc(0);

  for (i = 0; i < numero_elementos; i++) {
    scanf("%d", &elementos[i]);
    if (elementos[i] % 2 == 0) {
      elementos_pares = (int*)realloc(elementos_pares, sizeof(int)*(contador_pares+1));
      elementos_pares[contador_pares] = elementos[i];
      contador_pares++;
    } else {
      elementos_impares = (int*)realloc(elementos_impares, sizeof(int)*(contador_impares+1));
      elementos_impares[contador_impares] = elementos[i];
      contador_impares++;
    }
  }
    for (i = 0; i < numero_elementos; i++) {
      printf("%d ", elementos[i]);
    }
    printf("\n");
    for (i = 0; i < contador_impares; i++) {
      printf("%d ", elementos_impares[i]);
    }
    printf("\n");
    for (i = 0; i < contador_pares; i++) {
      printf("%d ", elementos_pares[i]);
    }
    printf("\n");


  return 0;
}
