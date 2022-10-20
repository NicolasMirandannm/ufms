#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define length(x) (int) (sizeof(x) / sizeof (x[0])) 

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

//tratamento do arquivo acertos.txt
void leArquivosAcertos(FILE *arq, Acertos *vet, int n);
void lerArrayAcertos(Acertos *&vet);

//tratamento do arquivo dados.txt
void lerArquivoDados(FILE *arq, Dados *vet, int n);
void lerArrayDados(DadosTodosCursos *&vet);

//tratamento do arquivo cursos_e_vagas.txt
void lerArquivoCursosVagas(FILE *arq, CursosVagas *vet, int n);
void lerArrayCursosVagas(CursosVagas *&vet);

//tratamento do arquivo cursos_e_pesos.txt
void lerArquivoCursosPesos(FILE *arq, CursosPesos *vet, int n);
void lerArrayCursosPesos(CursosPesos *&vet);

//desalocando vetores
void desalocaTodosArrays(Acertos *acertos, DadosTodosCursos *dadosTodosCursos, CursosVagas *cursosVagas, CursosPesos *cursosPesos);

//calculo de media e desvio padrao
void calcMediaAndDesvioPadrao(Acertos *vet, int n, Acertos *media, Acertos *desvioPadrao);





int main() {
	struct CursosVagas *cursosVagasArray;
	struct Acertos *acertosArray;
	struct DadosTodosCursos *dadosTodosCursosArray;
	struct CursosPesos *cursosPesosArray;

	lerArrayAcertos(acertosArray);
	lerArrayDados(dadosTodosCursosArray);
	lerArrayCursosVagas(cursosVagasArray);
	lerArrayCursosPesos(cursosPesosArray);




	desalocaTodosArrays(acertosArray, dadosTodosCursosArray, cursosVagasArray, cursosPesosArray);
  return 0;
}





//implementação das funções sobre os arquivos

//acertos
void leArquivosAcertos(FILE *arq, Acertos *vet, int n)
{
	for (int i = 0; i < n; i++) {
		fscanf(arq, "%d %d %d %d %d %lf", &vet[i].INS, &vet[i].V_LIN, &vet[i].V_MAT, &vet[i].V_NAT, &vet[i].V_HUM, &vet[i].RED);
		//printf("%d %d %d %d %d %lf", vet[i].INS, vet[i].V_LIN, vet[i].V_MAT, vet[i].V_NAT, vet[i].V_HUM, vet[i].RED);
	}
}

void lerArrayAcertos(Acertos *&vet)
{
	FILE *acertos = fopen("acertos.txt", "r");
	if(acertos == NULL) printf("Nao foi possivel abrir o arquivo acertos.txt\n");
	else {
		int n;
		fscanf(acertos, "%d", &n);
		vet = (Acertos*) calloc (n, sizeof(Acertos));
		if(vet == NULL) printf("Vetor de acertos nao pode ser alocado\n");
		else {
			leArquivosAcertos(acertos, vet, n);
			fclose(acertos);
		}
	}
}


//dados
void lerArquivoDados(FILE *arq, Dados *vet, int n)
{
	for (int i = 0; i < n; i++) {
		fscanf(arq, "%d %[^1234567890] %d/%d/%d %s", &vet[i].num_candidato, vet[i].nome, &vet[i].nascimento.dia, &vet[i].nascimento.mes, &vet[i].nascimento.ano, vet[i].tipoVaga);
		//printf("%d - %d %s %d/%d/%d %s\n", i, vet[i].num_candidato, vet[i].nome, vet[i].nascimento.dia, vet[i].nascimento.mes, vet[i].nascimento.ano, vet[i].tipoVaga);
	}
}

void lerArrayDados(DadosTodosCursos *&vet)
{
	FILE *dados;
	int indice = 0;
	dados = fopen("dados.txt", "r");
	if (dados == NULL) printf("Nao foi possivel abrir o arquivo de dados.txt\n");
	else {
		vet = (DadosTodosCursos*) calloc (113, sizeof(DadosTodosCursos));
		while( feof(dados) == 0 ) {
			fscanf(dados, "%d %d", &vet[indice].cod_curso, &vet[indice].num_de_candidatos);
			vet[indice].dadosCurso = (Dados*) calloc (vet[indice].num_de_candidatos, sizeof(Dados));
			if (vet[indice].dadosCurso == NULL) printf("Vetor de dados não pode ser alocado!\n");
			lerArquivoDados(dados, vet[indice].dadosCurso, vet[indice].num_de_candidatos);
			indice++;
		}
	}
	fclose(dados);
}

//cursos_e_vagas
void lerArquivoCursosVagas(FILE *arq, CursosVagas *vet, int n)
{
	for (int i = 0; i < n; i++) {
		fscanf(arq, "%d %d %d %d %d %d %d %d %d %d %d %d", &vet[i].cod, &vet[i].AC, &vet[i].L1, &vet[i].L3, &vet[i].L4, &vet[i].L5, &vet[i].L7, &vet[i].L8, &vet[i].L9, &vet[i].L11, &vet[i].L13, &vet[i].L15);
		//printf("%d %d %d %d %d %d %d %d %d %d %d %d\n", vet[i].cod, vet[i].AC, vet[i].L1, vet[i].L3, vet[i].L4, vet[i].L5, vet[i].L7, vet[i].L8, vet[i].L9, vet[i].L11, vet[i].L13, vet[i].L15);
	}
}

void lerArrayCursosVagas(CursosVagas *&vet)
{
		FILE *cursos_e_vagas = fopen("cursos_e_vagas.txt", "r");
		if( cursos_e_vagas == NULL) printf("Nao foi possivel abrir o arquivo cursos_e_vagas.txt\n");
		else {
			int n;
			fscanf(cursos_e_vagas, "%d", &n);
			vet = (CursosVagas*) calloc (n, sizeof(CursosVagas));
			if (vet == NULL) printf("Nao foi possivel alocar o vetor de cursos e vagas\n");
			else {
				lerArquivoCursosVagas(cursos_e_vagas, vet, n);
				fclose(cursos_e_vagas);
			} 
		}
}

//cursos_e_pesos
void lerArquivoCursosPesos(FILE *arq, CursosPesos *vet, int n)
{
	for (int i = 0; i < n; i++) {
		fscanf(arq, "%d %[^1234567890] %d %d %d %d %d", &vet[i].cod, vet[i].nomeCurso, &vet[i].red, &vet[i].mat, &vet[i].lin, &vet[i].hum, &vet[i].nat);	
		//printf("%d %s %d %d %d %d %d\n", vet[i].cod, vet[i].nomeCurso, vet[i].red, vet[i].mat, vet[i].lin, vet[i].hum, vet[i].nat);	
	}
}

void lerArrayCursosPesos(CursosPesos *&vet)
{
	FILE *cursos_e_pesos = fopen("cursos_e_pesos.txt", "r");
	if (cursos_e_pesos == NULL) printf("Nao foi possivel abrir o arquivo cursos_e_pesos.txt\n");
	else {
		int n;
		fscanf(cursos_e_pesos, "%d", &n);
		vet = (CursosPesos*) calloc (n, sizeof(CursosPesos));
		if (vet == NULL) printf("Vetor de cursos e pesos nao pode ser alocado!\n");
		lerArquivoCursosPesos(cursos_e_pesos, vet, n);
		fclose(cursos_e_pesos);
	}
}


//implementação da função de desalocar vetores

void desalocaTodosArrays(Acertos *acertos, DadosTodosCursos *dadosTodosCursos, CursosVagas *cursosVagas, CursosPesos *cursosPesos)
{
	free(acertos);

	for (int i = 0; i < 113; i++) {
		free(dadosTodosCursos[i].dadosCurso);
	}
	free(dadosTodosCursos);
	free(cursosVagas);
	free(cursosPesos);
}

//calculo de media e desvio padrao
void calcMediaAndDesvioPadrao(Acertos *vet, int n, Acertos *media, Acertos *desvioPadrao)
{
	media->V_LIN = 0;
	media->V_MAT = 0;
	media->V_NAT = 0;
	media->V_HUM = 0;

	for (int i = 0; i < n; i++) {
		media->V_LIN += vet[i].V_LIN;
		media->V_MAT += vet[i].V_MAT;
		media->V_NAT += vet[i].V_NAT;
		media->V_HUM += vet[i].V_HUM;
	}
	media->V_LIN /= n;
	media->V_MAT /= n;
	media->V_NAT /= n;
	media->V_HUM /= n;


}