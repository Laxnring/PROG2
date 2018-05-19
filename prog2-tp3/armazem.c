#include "armazem.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * funcoes do armazem
 */
/* alinea b) */
armazem* armazem_novo(int comprimento, int altura)
{
	armazem *novo_armazem;
	novo_armazem = (armazem *)malloc(sizeof(armazem));
	if (novo_armazem == NULL) return NULL;

	novo_armazem->comprimento = comprimento;
	novo_armazem->altura = altura;
	novo_armazem->contentores = fila_nova();

	return novo_armazem;
}

/* alinea c) */
int armazem_vazio(armazem* armz)
{
	pilha *pilha_inicial;

	pilha_inicial = fila_front(armz->contentores);
	if (fila_front(armz->contentores) == NULL) {
		return 1;
	}
	return 0;
}

/* alinea d) */
int armazem_cheio(armazem* armz)
{
	pilha* pilha_ultima;
	if (armz->comprimento == fila_tamanho(armz->contentores)) {
		pilha_ultima = fila_back(armz->contentores);
		if (pilha_ultima->tamanho == armz->altura) {
			// devolve cheio
			return 1;
		}
	}
	/* devolve nao cheio */
	return 0;
}

/* alinea e) */
int armazenar_contentor(armazem* armz, contentor* contr)
{
	fila *nova_fila;
	
	pilha *ultima_pilha;
	if (armazem_cheio(armz)) return 0;
	if (armazem_vazio(armz)) {
		ultima_pilha = pilha_nova();
		fila_push(armz->contentores, ultima_pilha);
		pilha_push(ultima_pilha, contr);
		return 1;
	}
	ultima_pilha = fila_back(armz->contentores);
	if (ultima_pilha->tamanho == armz->altura) {
		ultima_pilha = pilha_nova();
		fila_push(armz->contentores, ultima_pilha);
		pilha_push(ultima_pilha, contr);
		return 1;
	}
	pilha_push(ultima_pilha, contr);

	return 1;
}

/* alinea f) */
contentor* expedir_contentor(armazem* armz)
{
	pilha *primeira_pilha;
	contentor *contentor_remover;
	if (armazem_vazio(armz)) return NULL;

	primeira_pilha = fila_front(armz->contentores);

	if (primeira_pilha->tamanho == 0) {
		fila_pop(armz->contentores);
		primeira_pilha = fila_front(armz->contentores);
	}
	contentor_remover = pilha_top(primeira_pilha);
	//contentor_apaga(contentor_remover);
	pilha_pop(primeira_pilha);
	if (primeira_pilha->tamanho == 0) {
		fila_pop(armz->contentores);
	}
	imprimeArmazem(armz);

	printf("%lf", contentor_remover->valor);
	return contentor_remover;
}
