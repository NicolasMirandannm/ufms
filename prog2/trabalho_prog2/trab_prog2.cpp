#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


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

struct MediaEdp {
	double lin;
	double mat;
	double nat;
	double hum;
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
	Data nasc_cand;
};

//tratamento do arquivo acertos.txt
void leArquivosAcertos(FILE *arq, Acertos *vet, int n);
void lerArrayAcertos(Acertos *&vet, int *tamanho);

//tratamento do arquivo dados.txt
void lerArquivoDados(FILE *arq, Dados *vet, int n);
void lerArrayDados(DadosTodosCursos *&vet, int *tamanho);

//tratamento do arquivo cursos_e_vagas.txt
void lerArquivoCursosVagas(FILE *arq, CursosVagas *vet, int n);
void lerArrayCursosVagas(CursosVagas *&vet, int *tamanho);

//tratamento do arquivo cursos_e_pesos.txt
void lerArquivoCursosPesos(FILE *arq, CursosPesos *vet, int n);
void lerArrayCursosPesos(CursosPesos *&vet, int *tamanho);

//desalocando vetores
void desalocaTodosArrays(Acertos *acertos, DadosTodosCursos *dadosTodosCursos, CursosVagas *cursosVagas, CursosPesos *cursosPesos);

//calculo de media e desvio padrao
void calcMediaAndDesvioPadrao(Acertos *vet, int n, MediaEdp *media, MediaEdp *desvioPadrao);

//criação de um array para computaçaõ e lançamento de nota de cada inscrito
void computarNotas(compNotas *&vet, int n, Acertos *acertosArray, MediaEdp m, MediaEdp dp, CursosPesos *cursosPesos, int qtdCursos, DadosTodosCursos *todosCursos);
double EP(int valor, double media, double desvioPd);

// metodos de ordenação
void troca(compNotas *q, compNotas *p);
int separa(int p, int r, compNotas *v);
void quickSort(int p, int r, compNotas *vet);
void ordenaPorPrioridades(compNotas *vet, int n);
void imprimeInscritos(compNotas *vetor, int n);
void classificaInscritos(compNotas *notasOrd, int n_notas, CursosVagas *vagas);


int main() {
	struct CursosVagas *cursosVagasArray;
	int N_CV;

	struct Acertos *acertosArray;
	int N_A;

	struct DadosTodosCursos *dadosTodosCursosArray;
	int N_DTC;

	struct CursosPesos *cursosPesosArray;
	int N_CP;

	lerArrayAcertos(acertosArray, &N_A);
	lerArrayDados(dadosTodosCursosArray, &N_DTC);
	lerArrayCursosVagas(cursosVagasArray, &N_CV);
	lerArrayCursosPesos(cursosPesosArray, &N_CP);




	struct MediaEdp media, desvioPadrao;
	calcMediaAndDesvioPadrao(acertosArray, N_A, &media, &desvioPadrao);

	struct compNotas *notasCandidatos;
	computarNotas(notasCandidatos, N_A, acertosArray, media, desvioPadrao, cursosPesosArray, N_CP, dadosTodosCursosArray);

	quickSort(0, N_A-1, notasCandidatos);
	ordenaPorPrioridades(notasCandidatos, N_A);

	classificaInscritos(notasCandidatos, N_A, cursosVagasArray);

	imprimeInscritos(notasCandidatos, N_A);

	free(notasCandidatos);
	desalocaTodosArrays(acertosArray, dadosTodosCursosArray, cursosVagasArray, cursosPesosArray);
  return 0;
}

//
double EP(int valor, double media, double desvioPd)
{
	return (500 + 100 * (((2 * valor) - media )) / desvioPd);
}

void buscaCotaPorInscrito(DadosTodosCursos *todosCursos, compNotas *inscrito)
{
	int indice = 0;
	while (indice <= 113) {
		for (int i = 0; i < todosCursos[indice].num_de_candidatos; i++) {
			if (todosCursos[indice].dadosCurso[i].num_candidato == inscrito->INSC) {			
				// printf("%d %d %s\n", todosCursos[indice].cod_curso, todosCursos[indice].dadosCurso[i].num_candidato, todosCursos[indice].dadosCurso[i].tipoVaga);
				strcpy(inscrito->cota, todosCursos[indice].dadosCurso[i].tipoVaga);
				inscrito->codCurso = todosCursos[indice].cod_curso;
				inscrito->nasc_cand.dia = todosCursos[indice].dadosCurso[i].nascimento.dia;
				inscrito->nasc_cand.mes = todosCursos[indice].dadosCurso[i].nascimento.mes;
				inscrito->nasc_cand.ano = todosCursos[indice].dadosCurso[i].nascimento.ano;
				break;
			}
		}
		indice++;
	}
}

int buscarCursoPorInscrito(DadosTodosCursos *todosCursos, int INSC)
{
	int indice = 0;
	while (indice <= 113) {
		for (int i = 0; i < todosCursos[indice].num_de_candidatos; i++) {
			if (todosCursos[indice].dadosCurso[i].num_candidato == INSC) {
				return todosCursos[indice].cod_curso;
			}
		}
		indice++;
	}
	return -1;
}

void buscarPesosPorInscrito(int *pr, int *ph, int *pn, int *pl, int *pm, int ins, CursosPesos *cursosPesos, int qtdCursos, DadosTodosCursos *dadosTC)
{
	int curso = buscarCursoPorInscrito(dadosTC, ins);
	for (int i = 0; i < qtdCursos; i++) {
		if (cursosPesos[i].cod == curso) {
			*pr = cursosPesos[i].red;
			*ph = cursosPesos[i].hum;
			*pn = cursosPesos[i].nat;
			*pl = cursosPesos[i].lin;
			*pm = cursosPesos[i].mat;
			break;
		}
	}
}

double NF(double notaRED, double notaHUM, double notaNAT, double notaMAT, double notaLIN, int INSC, CursosPesos *cursosPesos, int qtdCursos, DadosTodosCursos *todosCursos)
{
	int PR;
	int PH;
	int PN;
	int PL;
	int PM;
	buscarPesosPorInscrito(&PR, &PH, &PN, &PL, &PM, INSC, cursosPesos, qtdCursos, todosCursos);

	return ( (PR * notaRED) + (PH * notaHUM) + (PN * notaNAT) + (PL * notaLIN) + (PM * notaMAT) ) / ( PR + PH + PN + PL + PM );
}

//computação das notas
void computarNotas(compNotas *&vet, int n, Acertos *acertosArray, MediaEdp m, MediaEdp dp, CursosPesos *cursosPesos, int qtdCursos, DadosTodosCursos *todosCursos)
{
	int teste = 0;
	int codigo_do_curso;
	int dia, mes, ano;
	vet = (compNotas*) calloc (n, sizeof(compNotas));
	if (vet == NULL) printf("Nao foi possivel alocar o vetor de notas computadas\n");
	else {
		for (int i = 0; i < n; i++) {
			vet[i].INSC = acertosArray[i].INS;
			vet[i].V_LIN = EP(acertosArray[i].V_LIN, m.lin, dp.lin);
			vet[i].V_MAT = EP(acertosArray[i].V_MAT, m.mat, dp.mat);
			vet[i].V_NAT = EP(acertosArray[i].V_NAT, m.nat, dp.nat);
			vet[i].V_HUM = EP(acertosArray[i].V_HUM, m.hum, dp.hum);
			vet[i].RED = (double) acertosArray[i].RED;
			buscaCotaPorInscrito(todosCursos, &vet[i]);
			vet[i].NotaFinal = NF(vet[i].RED, vet[i].V_HUM, vet[i].V_NAT, vet[i].V_MAT, vet[i].V_LIN, vet[i].INSC, cursosPesos, qtdCursos, todosCursos);
		}
	}
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

void lerArrayAcertos(Acertos *&vet, int *tamanho)
{
	FILE *acertos = fopen("acertos.txt", "r");
	if(acertos == NULL) printf("Nao foi possivel abrir o arquivo acertos.txt\n");
	else {
		int n;
		fscanf(acertos, "%d", &n);
		*tamanho = n;
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

void lerArrayDados(DadosTodosCursos *&vet, int *tamanho)
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
	*tamanho = indice;
}

//cursos_e_vagas
void lerArquivoCursosVagas(FILE *arq, CursosVagas *vet, int n)
{
	for (int i = 0; i < n; i++) {
		fscanf(arq, "%d %d %d %d %d %d %d %d %d %d %d %d", &vet[i].cod, &vet[i].AC, &vet[i].L1, &vet[i].L3, &vet[i].L4, &vet[i].L5, &vet[i].L7, &vet[i].L8, &vet[i].L9, &vet[i].L11, &vet[i].L13, &vet[i].L15);
		//printf("%d %d %d %d %d %d %d %d %d %d %d %d\n", vet[i].cod, vet[i].AC, vet[i].L1, vet[i].L3, vet[i].L4, vet[i].L5, vet[i].L7, vet[i].L8, vet[i].L9, vet[i].L11, vet[i].L13, vet[i].L15);
	}
}

void lerArrayCursosVagas(CursosVagas *&vet, int *tamanho)
{
		FILE *cursos_e_vagas = fopen("cursos_e_vagas.txt", "r");
		if( cursos_e_vagas == NULL) printf("Nao foi possivel abrir o arquivo cursos_e_vagas.txt\n");
		else {
			int n;
			fscanf(cursos_e_vagas, "%d", &n);
			*tamanho = n;
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

void lerArrayCursosPesos(CursosPesos *&vet, int *tamanho)
{
	FILE *cursos_e_pesos = fopen("cursos_e_pesos.txt", "r");
	if (cursos_e_pesos == NULL) printf("Nao foi possivel abrir o arquivo cursos_e_pesos.txt\n");
	else {
		int n;
		fscanf(cursos_e_pesos, "%d", &n);
		*tamanho = n;
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
void calcMediaAndDesvioPadrao(Acertos *vet, int n, MediaEdp *media, MediaEdp *desvioPadrao)
{
	media->lin = 0.0;
	media->mat = 0.0;
	media->nat = 0.0;
	media->hum = 0.0;

	desvioPadrao->lin = 0;
	desvioPadrao->mat = 0;
	desvioPadrao->nat = 0;
	desvioPadrao->hum = 0;

	for (int i = 0; i < n; i++) {
		media->lin += vet[i].V_LIN;
		media->mat += vet[i].V_MAT;
		media->nat += vet[i].V_NAT;
		media->hum += vet[i].V_HUM;
	}
	media->lin /= n;
	media->mat /= n;
	media->nat /= n;
	media->hum /= n;

	for (int i = 0; i < n; i++) {
		desvioPadrao->lin += pow(vet[i].V_LIN - media->lin, 2);
		desvioPadrao->mat += pow(vet[i].V_MAT - media->mat, 2);
		desvioPadrao->nat += pow(vet[i].V_NAT - media->nat, 2);
		desvioPadrao->hum += pow(vet[i].V_HUM - media->hum, 2);
	}

	desvioPadrao->lin = (sqrt(desvioPadrao->lin / (n - 1))) * 2; 
	desvioPadrao->mat = (sqrt(desvioPadrao->mat / (n - 1))) * 2;
	desvioPadrao->nat = (sqrt(desvioPadrao->nat / (n - 1))) * 2;
	desvioPadrao->hum = (sqrt(desvioPadrao->hum / (n - 1))) * 2;

	media->lin *= 2;
	media->mat *= 2;
	media->nat *= 2;
	media->hum *= 2;

}

void troca(compNotas *q, compNotas *p)
{
	struct compNotas aux;
	aux = *q;
	*q = *p;
	*p = aux;
}

int separa(int p, int r, compNotas *v)
{
	int i, j;
	struct compNotas x = v[p];
	i = p - 1;
	j = r + 1;
	while (1) {
		do {
			j--;
		} while(v[j].NotaFinal < x.NotaFinal);
		do {
			i++;
		} while (v[i].NotaFinal > x.NotaFinal);
		if( i < j)
			troca(&v[i], &v[j]);
		else
			return j;
	}
}

void quickSort(int p, int r, compNotas *vet)
{
	int q;
	if (p < r) {
		q = separa(p, r, vet);
		quickSort(p, q, vet);
		quickSort(q+1, r, vet);
	}
}

void ordenaPorPrioridades(compNotas *vet, int n)
{
	int min;
	for (int i = 0; i < n; i++) {
		min = i;
		for(int j = i+1; j < n; j++) {

			if (vet[i].NotaFinal == vet[j].NotaFinal && vet[i].codCurso == vet[j].codCurso) {
				if ( vet[j].nasc_cand.ano <= 1962 ) {
					if( vet[i].nasc_cand.ano > vet[j].nasc_cand.ano) {
						min = j;
					}
				} 
				else {
					if (vet[i].RED < vet[j].RED) {min = j;}
					else {
						if (vet[i].V_LIN < vet[j].V_LIN) {min = j;}
						else {
							if (vet[i].V_MAT < vet[j].V_MAT){ min = j;}
							else {
								if (vet[i].V_HUM < vet[j].V_HUM){ min = j;}
								else
									if (vet[i].V_NAT < vet[j].V_NAT) {min = j;}
							}
						}
					}
				}
			}
		}
		troca(&vet[i], &vet[min]);
	}
}

void imprimeInscritos(compNotas *vetor, int n)
{
	for (int i = 0; i < n; i++) {
		printf("%d %.2lf %.2lf %.2lf %.2lf %.2lf %s %.2lf %d %d %d/%d/%d\n", vetor[i].INSC, vetor[i].V_LIN, vetor[i].V_MAT, vetor[i].V_NAT, 
			vetor[i].V_HUM, vetor[i].RED, vetor[i].cota, vetor[i].NotaFinal, vetor[i].classificacao, vetor[i].codCurso, vetor[i].nasc_cand.dia, 
			vetor[i].nasc_cand.mes, vetor[i].nasc_cand.ano);
	}
}

void classificaInscritos(compNotas *notasOrd, int n_notas, CursosVagas *vagas)
{
	int ac, l1, l3, l4, l5, l7, l8, l9, l11, l13, l15;
	for (int i = 0; i < 113; i++) {
		ac = 1;
		l1 = 1;
		l3 = 1;
		l4 = 1;
		l5 = 1;
		l7 = 1;
		l8 = 1;
		l9 = 1;
		l11 = 1;
		l13 = 1;
		l15 = 1;

		for (int j = 0; j < n_notas; j++) {
			if ( notasOrd[j].codCurso == vagas[i].cod) {
				if ( strcmp(notasOrd[j].cota, "AC") == 0 && ac <= vagas[i].AC) {
					notasOrd[j].classificacao = ac;
					ac++;
				}
				else if (strcmp(notasOrd[j].cota, "L1") == 0 && ac <= vagas[i].L1) {
					notasOrd[j].classificacao = l1;
					l1++;
				}
				else if (strcmp(notasOrd[j].cota, "L3") == 0 && ac <= vagas[i].L3 ) {
					notasOrd[j].classificacao = l3;
					l3++;
				}
				else if (strcmp(notasOrd[j].cota, "L4") == 0 && ac <= vagas[i].L4 ) {
					notasOrd[j].classificacao = l4;
					l4++;
				}
				else if (strcmp(notasOrd[j].cota, "L5") == 0 && ac <= vagas[i].L5 ) {
					notasOrd[j].classificacao = l5;
					l5++;
				}
				else if (strcmp(notasOrd[j].cota, "L7") == 0 && ac <= vagas[i].L7 ) {
					notasOrd[j].classificacao = l7;
					l7++;
				}
				else if (strcmp(notasOrd[j].cota, "L8") == 0 && ac <= vagas[i].L8 ) {
					notasOrd[j].classificacao = l8;
					l8++;
				}
				else if (strcmp(notasOrd[j].cota, "L9") == 0 && ac <= vagas[i].L9 ) {
					notasOrd[j].classificacao = l9;
					l9++;
				}
				else if (strcmp(notasOrd[j].cota, "L11") == 0 && ac <= vagas[i].L11 ) {
					notasOrd[j].classificacao = l11;
					l11++;
				}
				else if (strcmp(notasOrd[j].cota, "L13") == 0 && ac <= vagas[i].L13 ) {
					notasOrd[j].classificacao = l13;
					l13++;
				}
				else if (strcmp(notasOrd[j].cota, "L15") == 0 && ac <= vagas[i].L15 ) {
					notasOrd[j].classificacao = l15;
					l15++;
				}
				else {
					notasOrd[j].classificacao = 0;
				}
			}
		}
	}
}
