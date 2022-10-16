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
	int num_candidato;
	char nome[80];
	Data nascimento;
	char tipoVaga[3];
};

struct DadosTodosCursos {
	int cod_curso;
	int num_de_candidatos;
	Dados *dadosCurso;
};

struct Acertos {
	int INS;
	int V_LIN;
	int V_MAT;
	int V_NAT;
	int V_HUM;
	double RED;
};

void lerDados(FILE *arq, Dados *vet, int n)
{
	for (int i = 0; i < n; i++) {
		fscanf(arq, "%d %[^1234567890] %d/%d/%d %s", &vet[i].num_candidato, vet[i].nome, &vet[i].nascimento.dia, &vet[i].nascimento.mes, &vet[i].nascimento.ano, vet[i].tipoVaga);
		//printf("%d - %d %s %d/%d/%d %s\n", i, vet[i].num_candidato, vet[i].nome, vet[i].nascimento.dia, vet[i].nascimento.mes, vet[i].nascimento.ano, vet[i].tipoVaga);
	}
}

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

	// Tratando o arquivo de dados;
	struct DadosTodosCursos *dadosTodosCursos;
	struct Dados *dadosArray;
	int ND, codigo_do_curso;
	dados = fopen("dados.txt", "r");
	if (dados == NULL) printf("Nao foi possivel abrir o arquivo de dados.txt\n");
	else {

		dadosTodosCursos = (DadosTodosCursos*) calloc (113, sizeof(DadosTodosCursos));
		if ( dadosTodosCursos ==  NULL) printf("vetor gigante de dados de todos os cursos nao pode ser alocado\n");
		int indice = 0;
		while( feof(dados) == 0) {

			fscanf(dados, "%d %d", &codigo_do_curso, &ND);
			dadosArray = (Dados*) calloc (ND, sizeof(Dados));
			if (dadosArray == NULL) printf("Vetor de dados não pode ser alocado!\n");
			lerDados(dados, dadosArray, ND);

			dadosTodosCursos[indice].cod_curso = codigo_do_curso;
			dadosTodosCursos[indice].num_de_candidatos = ND;
			dadosTodosCursos[indice].dadosCurso = dadosArray;
			free(dadosArray);
			indice++;
		}
		fclose(dados);
		
		printf("\n\n");
		
		printf("%d %d %d %s %d/%d/%d %s\n", dadosTodosCursos[1].cod_curso, dadosTodosCursos[1].num_de_candidatos, dadosTodosCursos[1].dadosCurso[0].num_candidato, dadosTodosCursos[1].dadosCurso[0].nome, dadosTodosCursos[1].dadosCurso[0].nascimento.dia, dadosTodosCursos[1].dadosCurso[0].nascimento.mes, dadosTodosCursos[1].dadosCurso[0].nascimento.ano, dadosTodosCursos[1].dadosCurso[0].tipoVaga);
	}
	

	 free(dadosTodosCursos);
	
	// // Tratando o arquivo de cursos e pesos
	// struct CursosPesos *cursosPesosArray;
	// int NCP;
	// cursos_e_pesos = fopen("cursos_e_pesos.txt", "r");
	// if (cursos_e_pesos == NULL) printf("Nao foi possivel abrir o arquivo cursos_e_pesos.txt\n");
	// else {
	// 	fscanf(cursos_e_pesos, "%d", &NCP);

	// 	cursosPesosArray = (CursosPesos*) calloc (NCP, sizeof(CursosPesos));
	// 	if (cursosPesosArray == NULL) printf("Vetor de cursos e pesos nao pode ser alocado!\n");

	// 	lerCursosPesos(cursos_e_pesos, cursosPesosArray, NCP);
	// 	fclose(cursos_e_pesos);
	// }
	// free(cursosPesosArray);

	// // Tratando arquivo de cursos e vagas
	// struct CursosVagas *cursosVagasArray;
	// int NCV;
	// cursos_e_vagas = fopen("cursos_e_vagas.txt", "r");
	// if (cursos_e_vagas == NULL) printf("Nao foi possivel abrir o arquivo cursos_e_vagas.txt\n");
	// else {
	// 	fscanf(cursos_e_vagas, "%d", &NCV);
	// 	cursosVagasArray = (CursosVagas*) calloc (NCV, sizeof(CursosVagas));
	//  if (cursosVagasArray == NULL) printf("Vetor de cursos e vagas nao pode ser alocado\n");
	// 	lerCursosVagas(cursos_e_vagas, cursosVagasArray, NCV);
	// 	fclose(cursos_e_vagas);
	// }
	// free(cursosVagasArray);

  return 0;
}