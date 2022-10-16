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

void lerCursosVagas(FILE *arq, CursosVagas *vet, int n)
{
	for (int i = 0; i < n; i++) {
		fscanf(arq, "%d %d %d %d %d %d %d %d %d %d %d %d", &vet[i].cod, &vet[i].AC, &vet[i].L1, &vet[i].L3, &vet[i].L4, &vet[i].L5, &vet[i].L7, &vet[i].L8, &vet[i].L9, &vet[i].L11, &vet[i].L13, &vet[i].L15);
		printf("%d %d %d %d %d %d %d %d %d %d %d %d\n", vet[i].cod, vet[i].AC, vet[i].L1, vet[i].L3, vet[i].L4, vet[i].L5, vet[i].L7, vet[i].L8, vet[i].L9, vet[i].L11, vet[i].L13, vet[i].L15);
	}
}

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


	
	// // Tratando o arquivo de cursos e pesos
	// struct CursosPesos *cursosPesosArray;
	// int NCP;
	// cursos_e_pesos = fopen("cursos_e_pesos.txt", "r");
	// if (cursos_e_pesos == NULL) printf("Nao foi possivel abrir o arquivo cursos_e_pesos.txt\n");
	// else {
	// 	fscanf(cursos_e_pesos, "%d", &NCP);

	// 	cursosPesosArray = (CursosPesos*) calloc (NCP, sizeof(CursosPesos));
	// 	if (cursosPesosArray == NULL) printf("Vetor nao pode ser alocado!\n");

	// 	lerCursosPesos(cursos_e_pesos, cursosPesosArray, NCP);
	// 	fclose(cursos_e_pesos);
	// }
	// free(cursosPesosArray);

	// Tratando arquivo de cursos e vagas
	struct CursosVagas *cursosVagasArray;
	int NCV;
	cursos_e_vagas = fopen("cursos_e_vagas.txt", "r");
	if (cursos_e_vagas == NULL) printf("Nao foi possivel abrir o arquivo cursos_e_vagas.txt\n");
	else {
		fscanf(cursos_e_vagas, "%d", &NCV);
		cursosVagasArray = (CursosVagas*) calloc (NCV, sizeof(CursosVagas));
		lerCursosVagas(cursos_e_vagas, cursosVagasArray, NCV);
		fclose(cursos_e_vagas);
	}

	free(cursosVagasArray);

  return 0;
}