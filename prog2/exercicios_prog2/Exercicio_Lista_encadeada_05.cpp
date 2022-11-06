#include <stdio.h>
#include <stdlib.h>

struct No
{
	int valor;
	struct No *proximo;
};

void empilhar(int valor, No **pilha);
int desempilhar(No **pilha);

int main()
{
	struct No *pilha = NULL;
	int n, valor;
	scanf("%d", &n);

	if(n == 0 ) printf("0\n");

	while(n != 0) {
		valor = n % 2;
		empilhar(valor, &pilha);
		n = n / 2;
	}

	while(pilha) {
		valor = desempilhar(&pilha);
		printf("%d", valor);
	}
	printf("\n");

	return 0;
}

void empilhar(int valor, No **pilha)
{
	struct No *novo;
	novo = (No*) malloc (sizeof(No));
	if (novo) {
		novo->valor = valor;
		novo->proximo = *pilha;
		*pilha = novo;
	}
	else
		printf("Nao foi possivel alocar memoria\n");
}

int desempilhar(No **pilha)
{
	struct No *aux;
	int num;

	if(*pilha == NULL) {
		return 0;
	}
	else {
		num = (*pilha)->valor;
		aux = *pilha;
		*pilha = (*pilha)->proximo;
		free(aux);
		return num;
	}
}