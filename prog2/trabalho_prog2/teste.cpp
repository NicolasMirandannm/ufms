#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct CursosPesos {
  int cod;
  char nomeCurso[50];
  int red;
  int mat;
  int lin;
  int hum;
  int nat;
};

struct compNotas {
	int INSC;
	double V_LIN;
	double V_MAT;
	double V_NAT;
	double V_HUM;
	double RED;
	char cota[3];
	double NotaFinal;
	int classificacao;
	int codCurso;
	char nome[80];
	Data nasc_cand;
};

struct AjustesRED
{
	int insc;
	double nota1, nota2;
};

struct Acertos {
	int INS;
	int V_LIN;
	int V_MAT;
	int V_NAT;
	int V_HUM;
	double RED;
};



void alterarNotasRed(char *arqName, Acertos *alunos, int n)
{
	FILE *arq = fopen(arqName, "r");
	if (arq == NULL) printf("Arquivo %s nao pode ser aberto\n", arqName);
	else
	{
		int tam;
		struct AjustesRED candidato;
		fscanf(arq, "%d", &tam);
		for(int i = 0; i < tam; i++) {
			fscanf(arq, "%d %lf %lf", &candidato.insc, &candidato.nota1, &candidato.nota2);
			for (int j = 0; j < n; j++) {
				if (alunos[j].INS == candidato.insc) {
					printf("%d %.2lf\n", alunos[j].INS, alunos[j].RED);
					alunos[j]->RED = candidato.nota2;
					printf("%d %.2lf\n\n", alunos[j].INS, alunos[j].RED);
				}
			}
		}
	}
}




void menu(bool op_0);

void gerarArquivoDosClassificadosPorNota();


int main()
{
	bool op_0 = false;
	int op;

	do {
		menu(op_0);
		scanf("%d", &op);

		if ( op == 0 ) {
			printf("Efetuando a leitura dos arquivos...\n");
			op_0 = true;
			printf("leitura finalizada.");
		}
		else {
			printf("Primeiro digite a opcao 0 para o programa realizar a leitura dos arquivos\n");
		}

	}while( op != 0);

	do {
		menu(op_0);
		scanf("%d", &op);

		if (op == 0) {
			printf("O programa ja realizou a leitura dos arquivos, porfavor selecione outra opcao.\n");
		}

		else if ( op == 1 ) {
			printf("opcao 1\n");
		}

		else if ( op == 2 ) {
			printf("opcao 2\n");
		}

		else if ( op == 3 ) {
			printf("opcao 3\n");
		}

		else if ( op == 4 ) {
			printf("opcao 4\n");
		}
		else if ( op == 5 ) {
			printf("Finalizando o programa.");
		}

		else {
			printf("opcao invalida!\n");
		}

	} while (op != 5 );
	return 0;
}


void menu(bool op_0)
{

	printf("\n\n");
	if (op_0) {
		printf("*----------------------------MENU----------------------------*\n");
		printf("1 - Gerar arquivo de saida .txt\n");
		printf("2 - Pesquisar candidatos .txt\n");
		printf("3 - Gerar arquivo dos candidatos não aprovados\n");
		printf("4 - Alterar nota de redação dos candidatos que entreram com recurso\n");
		printf("5 - Encerrar o programa\n");
	}
	else {
		printf("*----------------------------MENU----------------------------*\n");
		printf("0 - Efetuar leitura dos arquivos e seu armazenamento\n");
		printf("1 - Gerar arquivo de saida .txt\n");
		printf("2 - Pesquisar candidatos .txt\n");
		printf("3 - Gerar arquivo dos candidatos nao aprovados\n");
		printf("4 - Alterar nota de redação dos candidatos que entreram com recurso\n");
		printf("5 - Encerrar o programa\n");
	}
	printf("\n\n");
	
}
