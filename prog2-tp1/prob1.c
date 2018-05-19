#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

  int *elementos, numero_elementos;
  int *elementos_impares, *elementos_pares;
  int numero_pares = 0, numero_impares = 0;
  int i, j, k = 0, l = 0, m, n;

  printf("Numero de elementos: ");
  scanf("%d", &numero_elementos);
  elementos = (int *) malloc(numero_elementos * sizeof(int));

  for (i = 0; i < numero_elementos; i++) {
    scanf("%d", &elementos[i]);
  }

  printf("Vetor Original: [ ");
  for (j = 0; j < numero_elementos; j++) {
    printf("%d ", elementos[j]);
    if (elementos[j] % 2 == 0){
      numero_pares++;
    }
    else numero_impares++;
  }

  printf("]\n");
  elementos_pares = (int *) malloc(numero_pares * sizeof(int));

  for (m = 0; m < i; m++) {
    if (elementos[m] % 2 == 0) elementos_pares[k++] = elementos[m];
  }

  elementos_impares = (int *) malloc(numero_impares * sizeof(int));

  for (n = 0; n < i; n++) {
    if (elementos[n] % 2 == 1) elementos_impares[l++] = elementos[n];
  }
  printf("Vetor Pares: [ ");

  for (i = 0; i < sizeof(elementos_pares)/sizeof(int); i++) {
    printf("%d ", elementos_pares[i]);
  }
  printf("]\n");

  printf("Vetor Impares: [ ");

  for (i = 0; i < sizeof(elementos_impares)/sizeof(int); i++) {
    printf("%d ", elementos_impares[i]);

  }

  printf("]\n");

  return 0;
}
