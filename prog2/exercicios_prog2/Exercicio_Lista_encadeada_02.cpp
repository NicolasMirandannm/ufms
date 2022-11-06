#include <stdio.h>
#include <stdlib.h>

struct No
{
	int valor;
	struct No *proximo;
};

void inserir_fim(int valor, No **lista);

int main()
{
	struct No *lista = NULL;
	struct No *lista2 = NULL;
	int valor, contador = 0;
	int *vetor;

	while(true) {
		scanf("%d", &valor);
		if(valor == 0) break;
		inserir_fim(valor, &lista);
		contador++;
	}


	vetor = (int*) calloc (contador, sizeof(int));
	struct No *aux = lista;

	for (int i = 0; i < contador; i++) {
		vetor[i] = aux->valor;
		aux = aux->proximo;
	}

	for (int i = 0; i < contador; i++) {
		inserir_fim(vetor[i], &lista2);
	}

	aux = lista2;
	while(aux) {
		printf("%d ", aux->valor);
		aux = aux->proximo;
	}
	printf("\n");

	return 0;

}

void inserir_fim(int valor, No **lista)
{
	No *novo, *aux;
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