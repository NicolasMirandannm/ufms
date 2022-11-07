#include <stdio.h>
#include <stdlib.h>

struct No {
	int valor;
	struct No *proximo;
};

void inserir_fim(int valor, No **lista);
bool existe(No *lista, int valor);

int main()
{
	struct No *lista = NULL, *aux;
	int valor;

	while(true) {
		scanf("%d", &valor);
		if(valor == 0) break;
		if (!existe(lista, valor)) {
			inserir_fim(valor, &lista);
		}
		
	}
	
	while(lista) {
		aux = lista;
		printf("%d ", aux->valor);
		lista = lista->proximo;
		free(aux);
	}
	printf("\n");
	return 0;
}

void inserir_fim(int valor, No **lista)
{
	struct No *novo, *aux;
	novo = (No*) malloc (sizeof(No));
	if(novo)
	{
		novo->valor = valor;
		novo->proximo = NULL;
		if(*lista == NULL)
			*lista = novo;
		else {
			aux = *lista;
			while(aux->proximo) {
				aux = aux->proximo;
			}
			aux->proximo = novo;	
		}
	}
	else
		printf("Nao foi possivel alocar memoria\n");
}

bool existe(No *lista, int valor)
{
	struct No *aux;
	aux = lista;
	while(aux) {
		if (aux->valor == valor) {
			return true;
		}
		aux = aux->proximo;
	}
	return false;
}