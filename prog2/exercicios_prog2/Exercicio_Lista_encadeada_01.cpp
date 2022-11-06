#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct No
{
	char nome[31];
	struct No *proximo;
};

No* interseccao(No *L1, No *L2);
void inserir_fim(char nome[31], No **lista);
void imprimir(No *lista);

int main()
{
	No *lista1 = NULL;
	No *lista2 = NULL;
	No *lista3 = NULL;
	char nome[31];

	while(true) {
		scanf(" %s", nome);
		if (strcmp(nome, "FIM") == 0) {
			break;
		}
		inserir_fim(nome, &lista1);
	}

	while(true) {
		scanf(" %s", nome);
		if (strcmp(nome, "FIM") == 0) {
			break;
		}
		inserir_fim(nome, &lista2);
	}


	lista3 = interseccao(lista1, lista2);
	// printf("%s\n", lista3->nome);

	if(lista3) {
		imprimir(lista3);
	}
	else {
		printf("VAZIA\n");
	}

	return 0;
}

void inserir_fim(char nome[31], No **lista)
{
	No *novo, *aux;
	novo = (No*) malloc(sizeof(No));
	if (novo) {
		strcpy(novo->nome, nome);
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

No* interseccao(No *L1, No *L2)
{
	No *novo = NULL;
	No *aux1, *aux2;
	aux1 = L1;

	while(aux1) {
		aux2 = L2;
		while(aux2) {
			if (strcmp(aux1->nome, aux2->nome) == 0) {
				inserir_fim(aux1->nome, &novo);
			}
			aux2 = aux2->proximo;
		}
		aux1 = aux1->proximo;
	}
	
	return novo;
}

void imprimir(No *lista)
{
	for (No *p = lista; p != NULL; p = p->proximo) {
		printf("%s ", p->nome);
	}
	printf("\n");
}