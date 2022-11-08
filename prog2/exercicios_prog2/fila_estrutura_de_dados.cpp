#include <stdio.h>
#include <stdlib.h>

struct no
{
	int valor;
	struct no *proximo;
};

void inserir_na_fila(int valor, no **inicio, no **fim);
int remover_da_fila(no **inicio, no **fim);
void menu();

int main()
{
	int op;
	int valor;
	struct no *inicio = NULL, *fim = NULL;

	do {
		menu();
		scanf("%d", &op);

		if(op == 1) {
			scanf("%d", &valor);
			inserir_na_fila(valor, &inicio, &fim);
			printf("elemento '%d' inserido na fila com sucesso!\n", valor);
		}
		else if(op == 2) {
			valor = remover_da_fila(&inicio, &fim);
			printf("elemento '%d' removido na fila com sucesso!\n", valor);
		}
		else if(op == 4) {
			printf("saindo...\n");
		}
		else {
			printf("opcao invalida!\n");
		}

	} while(op != 4);

	return 0;
}

void menu() {
	printf("\n---------------Menu-Lista---------------\n\n");
	printf("1 - inserir na fila.\n");
	printf("2 - remover da fila.\n");
	printf("4 - sair.\n\n");
}

void inserir_na_fila(int valor, no **inicio, no **fim)
{
	struct no *novo;
	novo = (no*) malloc (sizeof(no));
	if(novo == NULL) printf("nao foi possivel alocar memoria\n");
	else
	{
		novo->valor = valor;
		novo->proximo = NULL;

		if(*inicio == NULL) {
			*inicio = *fim = novo;
		}
		else {
			(*fim)->proximo = novo;
			*fim = novo;
		}
	}
}


int remover_da_fila(no **inicio,no **fim)
{
	int num;
	no *aux;

	if(*inicio == NULL) {
		return 0;
	}
	else {
		num = (*inicio)->valor;
		aux = *inicio;
		*inicio = aux->proximo;
		if(*inicio == NULL) {
			*fim = NULL;
		}
		free(aux);
		return num;
	}
}
