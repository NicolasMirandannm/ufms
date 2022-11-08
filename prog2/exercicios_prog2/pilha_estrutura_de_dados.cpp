#include <stdio.h>
#include <stdlib.h>

struct no
{
	int valor;
	struct no *proximo;
};

void empilhar(int valor, no **pilha);
int desempilhar(no **pilha);
void menu();


int main()
{
	int valor, op;
	struct no *pilha = NULL;

	do {

		menu();
		scanf("%d", &op);

		if (op == 1) {
			scanf("%d", &valor);
			empilhar(valor, &pilha);
		}
		else if(op == 2) {
			valor = desempilhar(&pilha);
			printf("O elemento desempilhado foi '%d'\n", valor);
		}
		else if(op == 3) {
			printf("saindo...\n");
		}
		else {
			printf("opcao invalida\n");
		}

	} while(op != 3);
	return 0;
}

void menu()
{
	printf("\n-----------Menu-pilha-------------\n\n");
	printf("1 - empilhar valor\n");
	printf("2 - desempilhar\n");
	printf("3 - sair\n");
}
void empilhar(int valor, no **pilha)
{
	struct no *novo;
	novo = (no*) malloc (sizeof(no));
	if(novo == NULL) printf("nao foi possivel alocar memoria\n");
	else
	{
		novo->valor = valor;
		novo->proximo = *pilha;
		*pilha = novo;
	}
}

int desempilhar(no **pilha)
{
	int num;
	struct no *aux;
	if(*pilha == NULL) {
		return 0;
	}
	else {
		num = (*pilha)->valor;
		aux = *pilha;
		*pilha = aux->proximo;
		free(aux);
		return num;
	}
}