#include <stdio.h>
#include <stdlib.h>

struct No
{
	int valor;
	struct No *proximo;
};

void inserir_fim(int valor, No **lista);
void desaloca(No **lista);

int main()
{
	struct No *lista1 = NULL;
	struct No *lista2 = NULL;
	struct No *lista3 = NULL;
	int valor;
	struct No *aux;

	while(true) {
		scanf("%d", &valor);
		if (valor <= 0) break;
		inserir_fim(valor, &lista1);
	}

	while(true) {
		scanf("%d", &valor);
		if (valor <= 0) break;
		inserir_fim(valor, &lista2);
	}

	aux = lista1;
	while(aux) {
		inserir_fim(aux->valor, &lista3);
		aux = aux->proximo;
	}
	
	while(lista2) {
		aux = lista1;
		bool existe = false;
		while(aux) {
			if (aux->valor == lista2->valor) {
				existe = true;
				break;
			}
			aux = aux->proximo;
		}
		if (!existe) {
			inserir_fim(lista2->valor, &lista3);
		}
		
		lista2 = lista2->proximo;
	}

	while(lista3) {
		printf("%d ", lista3->valor);
		lista3 = lista3->proximo;
	}
	desaloca(&lista1);
	desaloca(&lista2);
	desaloca(&lista3);

	return 0;
}

void inserir_fim(int valor, No **lista)
{
	struct No *novo, *aux;
	novo = (No*) malloc (sizeof(No));
	if(novo) {
		novo->valor = valor;
		novo->proximo = NULL;
		if (*lista == NULL) {
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
	else
		printf("Nao foi possivel alocar memoria\n");
}

void desaloca(No **lista)
{
	No *aux;
	while(*lista) {
		aux = *lista;
		*lista = aux->proximo;
		free(aux);
	}
}