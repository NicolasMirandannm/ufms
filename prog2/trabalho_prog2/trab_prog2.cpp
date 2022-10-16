#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data {
	int dia;
	int mes;
	int ano;
};

struct CursosPesos {
  int cod;
  char nomeCurso[50];
  int red;
  int mat;
  int lin;
  int hum;
  int nat;
};

struct CursosVagas {
	int cod;
	int AC;
	int L1;
	int L3;
	int L4;
	int L5;
	int L7;
	int L8;
	int L9;
	int L11;
	int L13;
	int L15;
};

struct Dados {
	int cod;
	int num_candidato;
	char nome[80];
	Data nascimento;
	char tipoVaga[3];
};

struct Acertos {
	int INS;
	int V_LIN;
	int V_MAT;
	int V_NAT;
	int V_HUM;
	double RED;
};


void lerCursosPesos(FILE *arq, CursosPesos *vet, int n)
{
	for (int i = 0; i < n; i++) {
		fscanf(arq, "%d %[^1234567890] %d %d %d %d %d", &vet[i].cod, vet[i].nomeCurso, &vet[i].red, &vet[i].mat, &vet[i].lin, &vet[i].hum, &vet[i].nat);	
		printf("%d %s %d %d %d %d %d\n", vet[i].cod, vet[i].nomeCurso, vet[i].red, vet[i].mat, vet[i].lin, vet[i].hum, vet[i].nat);	
	}
}


int main() {
	FILE *cursos_e_pesos;
	FILE *cursos_e_vagas;
	FILE *dados;
	FILE *acertos;


	
	// Tratando o arquivo de cursos e pesos
	struct CursosPesos *cursosPesosArray;
	int n;
	cursos_e_pesos = fopen("arqTeste.txt", "r");
	if (cursos_e_pesos == NULL) printf("Nao foi possivel abrir o arquivo\n");
	else {
		fscanf(cursos_e_pesos, "%d", &n);

		cursosPesosArray = (CursosPesos*) calloc (n, sizeof(CursosPesos));
		if (cursosPesosArray == NULL) printf("Vetor nao pode ser alocado!\n");

		lerCursosPesos(cursos_e_pesos, cursosPesosArray, n);
		fclose(cursos_e_pesos);
		printf("\n\n");

	}

	for (int i = 0; i < n; i++) {
		printf("%d %s %d %d %d %d %d\n", cursosPesosArray[i].cod, cursosPesosArray[i].nomeCurso, cursosPesosArray[i].red, cursosPesosArray[i].mat, cursosPesosArray[i].lin, cursosPesosArray[i].hum, cursosPesosArray[i].nat);
	}
	free(cursosPesosArray);
  return 0;
}