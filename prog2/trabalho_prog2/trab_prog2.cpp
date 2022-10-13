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
		fscanf(arq, "%d %[^1234567890] %d %d %d %d %d", &vet[n].cod, vet[n].nomeCurso, &vet[n].red, &vet[n].mat, &vet[n].lin, &vet[n].hum, &vet[n].nat);	
		printf("%d %s %d %d %d %d %d\n", vet[n].cod, vet[n].nomeCurso, vet[n].red, vet[n].mat, vet[n].lin, vet[n].hum, vet[n].nat);	
	}
	printf("\n\n%d\n", vet[2].cod);
	
}


int main() {
	FILE *cursos_e_pesos;
	FILE *cursos_e_vagas;
	FILE *dados;
	FILE *acertos;

	
	// Tratando o arquivo de cursos e pesos
	int n;
	cursos_e_pesos = fopen("arqTeste.txt", "r");
	if (cursos_e_pesos == NULL) printf("Nao foi possivel abrir o arquivo\n");
	else {
		fscanf(cursos_e_pesos, "%d", &n);
		CursosPesos cursosPesosArray[n];
		lerCursosPesos(cursos_e_pesos, cursosPesosArray, n);
		fclose(cursos_e_pesos);
		printf("\n\n%d\n", cursosPesosArray[2].cod);
	}


  return 0;
}