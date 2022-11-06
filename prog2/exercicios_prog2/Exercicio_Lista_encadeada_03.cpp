#include <stdio.h>
#include <stdlib.h>

struct No
{
	int valor;
	struct No *proximo;
};

void inserir_fim(int valor, No **lista);
int soma(No *lista);

int main()
{
	struct No *lista = NULL;
	int num, sum;

	while(true) {
		scanf("%d", &num);
		if (num < 0) break;
		inserir_fim(num, &lista);
	}
	
	sum = soma(lista);
	printf("%d\n", sum);
	return 0;
}

int soma(No *lista)
{
	int soma = 0;
	while(lista) {
		soma += lista->valor;
		lista = lista->proximo;
	}
	return soma;
}

void inserir_fim(int valor, No **lista)
{
	
	struct No *novo, *aux;
	novo = (No*) malloc (sizeof(No));
	if (novo) {
		novo->valor = valor;
		novo->proximo = NULL;
		if(*lista == NULL) {
			*lista = novo;
		}
		else {
			aux = *lista;
			while(aux->proximo) {
				aux = aux->proximo;
			}
			aux->proximo = novo;
		}
	}
	else {
		printf("Nao foi possivel alocar memoria\n");
	}
}