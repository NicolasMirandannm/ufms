#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	Data nasc_cand;
};

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

// ARRAY DE CURSOSPESOS ORDENADO
void ordenaAlfabetico(compNotas *inscritos, int n)
{
	compNotas aux;
	int min;
	for (int i = 0; i < n; i++) {
		min = i;
		for (int j = i+1; j < n; j++) {
			if (strcmp(inscritos[i].cota, inscritos[j].cota) > 0 ) {
				min = j;
			}
		}
		aux = inscritos[i];
		inscritos[i] = inscritos[min];
		inscritos[min] = aux;
	}

}

void gerarArquivoDosClassificadosPorNota(char *nomeArq, compNotas *inscritos, int qtd_insc, CursosPesos *cursos, int qtd_cursos)
{
	FILE *arq = fopen(nomeArq, "a");
	if (arq == NULL) printf("Ñao foi possivel abrir o arquivo, verifique se o nome digitado contem .txt no final\n");
	else 
	{
		ordenaAlfabetico(inscritos, qtd_insc);
		fprintf(arq, "/*LISTA GERAL CLASSIFICADO POR NOTA*/\n");
		for (int i = 0; i < qtd_cursos; i++) {
			fprintf(arq, "%d   %s\n", cursos[i].cod, cursos[i].nomeCurso);
			fprintf(arq, "\n");
			fprintf(arq, "INSC V_LIN V_MAT V_NAT V_HUM RED COTA NOTA FINAL CLASSIFICAÇÃO");
			
			for (int j = 0; j < qtd_insc; j++) {
				if (inscritos[j].codCurso == cursos[i].cod) {
					printf("%d %.2lf %.2lf %.2lf %.2lf %.2lf %s %.2lf %d\n", inscritos[i].INSC, inscritos[i].V_LIN, inscritos[i].V_MAT, inscritos[i].V_NAT, 
					inscritos[i].V_HUM, inscritos[i].RED, inscritos[i].cota, inscritos[i].NotaFinal, inscritos[i].classificacao);
				}
			}

		}
	}

}

// int qtdInscritosPorCurso(DadosTodosCursos *vet, int cod)
// {
// 	for (int j = 0; j <= 113; j++) {
// 		if (cursosDados[j].cod_curso == cod) {
// 			return cursosDados[j].num_de_candidatos;
// 		}
// 	}
// }

// void imprimeNotaOrdenado(FILE *arq, compNotas *todosInsc, int cod_curso, int numCand, int n_cd)
// {
// 	compNotas *aux;
// 	int i = 0;
// 	aux = (compNotas*) calloc (numCand, sizeof(compNotas));
// 	if (aux == NULL) printf("Vetor de compNotas para impressao nao pode ser alocado.\n");
// 	else {
// 		for (int x = 0; x < n_cd; x++) {
// 			if (todosInsc[i].cod_curso == cod_curso) {
// 				aux[i] = todosInsc[x];
// 				i++;
// 			}
// 		}

// 		ordenaAlfabetico(aux, numCand);

// 		for (int x = 0; x < numCand; x++) {
// 			fprintf(arq, "%d %.2lf %.2lf %.2lf %.2lf %.2lf %s %.2lf %d",
// 				aux[x].INSC,
// 				aux[x].V_LIN,
// 				aux[x].V_MAT,
// 				aux[x].V_NAT,
// 				aux[x].V_HUM,
// 				aux[x].RED,
// 				aux[x].cota,
// 				aux[x].NotaFinal,
// 				aux[x].classificacao);
// 		}
// 		free(aux);
// 	}
// }

