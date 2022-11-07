#include <stdio.h>
#include <stdlib.h>

struct no
{
	int valor;
	struct no *proximo;
};

void inserir_fim(int valor, no **lista);
no* remover_par(no **lista);

int main()
{
	struct no *lista = NULL, *removido, *aux;
	int valor;

	while(true) {
		scanf("%d", &valor);
		if(valor == 0) break;
		inserir_fim(valor, &lista);
	}

	do {
		removido = remover_par(&lista);
		if(removido) {
			free(removido);	
		}
		
	} while(removido != NULL);

	aux = lista;
	while(aux) {
		printf("%d ", aux->valor);
		aux = aux->proximo;
	}
	printf("\n");

	return 0;
}

no* remover_par(no **lista)
{
	struct no *aux, *remover = NULL;
	
	if(*lista) {
		if((*lista)->valor % 2 == 0) {
			remover = *lista;
			*lista = remover->proximo;
		}
		else {
			aux = *lista;
			while(aux->proximo && aux->proximo->valor % 2 != 0)
				aux = aux->proximo;
			if(aux->proximo) {
				remover = aux->proximo;
				aux->proximo = remover->proximo;
			}
		}
		
	}	

	return remover;
}




void inserir_fim(int valor, no **lista)
{
	struct no *novo, *aux;
	novo = (no*) malloc (sizeof(no));
	if(novo == NULL) printf("nao foi possivel alocar memoria\n");
	else
	{
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
}