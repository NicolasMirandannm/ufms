#include <stdio.h>
#include <stdlib.h>

struct no
{
	int valor;
	struct no *proximo;
};

void inserir_fim(int valor, no **lista);
no* remover_ultimo_elemento(no **lista);


int main()
{
	struct no *lista = NULL, *removido;
	int valor, n, k;

	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &valor);
		inserir_fim(valor, &lista);
	}

	scanf("%d", &k);
	for(int i = 0; i < k; i++) {
		if(i < n) {
			removido = remover_ultimo_elemento(&lista);
			if(removido) {
				printf("%d\n", removido->valor);
				free(removido);
			}
		}
		else 
			printf("0\n");
	}

	return 0; 
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

		if(*lista == NULL)
			*lista = novo;
		else {
			aux = *lista;
			while(aux->proximo)
				aux = aux->proximo;
			aux->proximo = novo;
		}
	}

}


no* remover_ultimo_elemento(no **lista)
{
	struct no *remover = NULL, *aux;
	if (*lista) {
		if((*lista)->proximo == NULL) {
			remover = *lista;
		}
		else {
			aux = *lista;
			while(aux->proximo->proximo) {
				aux = aux->proximo;
			}
			remover = aux->proximo;
			aux->proximo = NULL;
		}
		
	}
	return remover;
}
