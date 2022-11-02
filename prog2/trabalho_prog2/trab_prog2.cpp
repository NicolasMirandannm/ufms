#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct Data {
	int dia, mes, ano;
};

struct CursosPesos {
  int cod;
  char nomeCurso[50];
  int red, mat, lin, hum, nat;
};

struct CursosVagas {
	int cod, AC, L1, L3, L4, L5, L7, L8, L9, L11, L13, L15;
};


struct Dados {
	int num_candidato;
	char nome[80];
	Data nascimento;
	char tipoVaga[3];
};

struct DadosTodosCursos {
	int cod_curso, num_de_candidatos;
	Dados *dadosCurso;
};

struct Acertos {
	int INS, V_LIN, V_MAT, V_NAT, V_HUM;
	double RED;
};

struct MediaEdp {
	double lin, mat, nat, hum;
};

struct compNotas {
	int INSC;
	double V_LIN, V_MAT, V_NAT, V_HUM, RED;
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
void desalocaTodosArrays(Acertos *acertos, DadosTodosCursos *dadosTodosCursos, CursosVagas *cursosVagas, CursosPesos *cursosPesos, compNotas *notasComputadas);

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
void classificaInscritos(compNotas *notasOrd, int n_notas, CursosVagas *vagas);

// gerando arquivo ordenado
void trocaCursoPeso(CursosPesos *a, CursosPesos *b);
int separadorCursos(int p, int r, CursosPesos *v);
void quickSortCursoPorCod(int p, int r, CursosPesos *v);
void gerarArquivoDosClassificadosPorNota(char *nomeArq, compNotas *inscritos, int qtd_insc, CursosPesos *cursos, int qtd_cursos);

// Buscar o candidato pelo codigo

void buscaImprimeCandidato(CursosPesos *cursosPesos, int qtdCursos, DadosTodosCursos *todosDados ,compNotas *vetor, int n, int INSC);
void buscarNomePorInsc(DadosTodosCursos *vet, int INSC, char *name);
void buscarNomeDoCursoPorCod(CursosPesos *vet, int n, int codCurso, char *curso);

//ordenação dos candidatos por ordem alfabetica
void ordenaCandAlf(compNotas *vetor, int n);

//Geração de um arquivo com todos candidatos não aprovados
void ordenaCursosPesosPorCod(CursosPesos *vet);
void geraArquivoDeCandNaoAprovados(char *arqName, compNotas *todosAlunos, int qtdAlunos, CursosPesos *todosCursos);

//alterar nota da redação de quem entrou com recurso
void alterarNotasRed(char *arqName, Acertos *alunos, int n);

// -------- menu ----------- //
void menu(bool op_0);

int main() {
	
	bool op_0 = false;
	int op;

	struct CursosVagas *cursosVagasArray;
	int N_CV;

	struct Acertos *acertosArray;
	int N_A;

	struct DadosTodosCursos *dadosTodosCursosArray;
	int N_DTC;

	struct CursosPesos *cursosPesosArray, cursosPcopy[113];
	int N_CP;

	struct MediaEdp media;
	struct MediaEdp desvioPadrao;
	struct compNotas *notasCandidatos;

	do {
		menu(op_0);
		scanf("%d", &op);

		if ( op == 0 ) {
			printf("Efetuando a leitura dos arquivos...\n");

			lerArrayAcertos(acertosArray, &N_A);
			lerArrayDados(dadosTodosCursosArray, &N_DTC);
			lerArrayCursosVagas(cursosVagasArray, &N_CV);
			lerArrayCursosPesos(cursosPesosArray, &N_CP);

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
			printf("Digite o nome para o arquivo: ");
			char arqName[50];
			scanf("%s]", arqName);

			calcMediaAndDesvioPadrao(acertosArray, N_A, &media, &desvioPadrao);
			computarNotas(notasCandidatos, N_A, acertosArray, media, desvioPadrao, cursosPesosArray, N_CP, dadosTodosCursosArray);
			quickSort(0, N_A-1, notasCandidatos);
			ordenaPorPrioridades(notasCandidatos, N_A);
			classificaInscritos(notasCandidatos, N_A, cursosVagasArray);
			quickSortCursoPorCod(0, N_CP-1, cursosPesosArray);

			gerarArquivoDosClassificadosPorNota(arqName, notasCandidatos, N_A, cursosPesosArray, N_CP);
			printf("\n\nArquivo %s criado com sucesso!\n\n", arqName);
		}

		else if ( op == 2 ) {
			int inscricao;
			printf("VOCE ENTROU NO MENU DE PESQUISA...\n");
			do {
				printf("INFORME A MATRICULA DO CANDIDATO PARA PESQUISAR OU 0 PARA ENCERRAR A PESQUISA: ");
				scanf("%d", &inscricao);
				buscaImprimeCandidato(cursosPesosArray, N_CP, dadosTodosCursosArray, notasCandidatos, N_A, inscricao);
				printf("\n");
			} while (inscricao != 0);
			
		}

		else if ( op == 3 ) {
			
			char arqName[50];
			printf("nome para o arquivo: ");
			scanf(" %s", arqName);
			geraArquivoDeCandNaoAprovados(arqName, notasCandidatos, N_A, cursosPesosArray);
			printf("\nArquivo %s gerado com sucesso!\n\n", arqName);
		}

		else if ( op == 4 ) {
			free(notasCandidatos);
			char arqName[50];
			printf("Digite o nome do arquivo para alteracao das notas: ");
			scanf(" %s", arqName);
			alterarNotasRed(arqName, acertosArray, N_A);
			printf("\nNotas alteradas com sucesso!\n\n");
		}
		else if ( op == 5 ) {
			printf("\n\nFinalizando o programa...\n\n");
			desalocaTodosArrays(acertosArray, dadosTodosCursosArray, cursosVagasArray, cursosPesosArray, notasCandidatos);
			printf("\nate a proxima!\n\n");
		}

		else {

			printf("opcao invalida!\n");
		}

	} while (op != 5 );

	return 0;
}

//  ----------- menu -------------- //

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



//alterar nota da redação de quem entrou com recurso//

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
					alunos[j].RED = candidato.nota2;
					printf("%d %.2lf\n\n", alunos[j].INS, alunos[j].RED);
				}
			}
		}
	}
}


//ordenação dos candidatos por nome em ordem alfabetica //
void ordenaCandAlf(compNotas *vetor, int n)
{
	struct compNotas aux;
	int min;
	for (int i = 0; i < n; i++) {
		min = i;
		for (int j = i+1; j < n; j++) {
			if (strcmp(vetor[min].nome, vetor[j].nome) > 0) {
				min = j;
			}
		}
		aux = vetor[i];
		vetor[i] = vetor[min];
		vetor[min] = aux;
	}
}


//Ordenação dos cursos pelo codigo em ordem crescente //

void ordenaCursosPesosPorCod(CursosPesos *vet)
{
	struct CursosPesos aux;
	int n = 113;
	int min;
	for (int i = 0; i < n; i++) {
		min = i;
		for(int j=i+1; j < n; j++) {
			if (vet[min].cod > vet[j].cod) {
				min = j;
			}
		}
		aux = vet[i];
		vet[i] = vet[min];
		vet[min] = aux;
	}
}

//Geração de um arquivo com todos candidatos não aprovados//

void geraArquivoDeCandNaoAprovados(char *arqName,compNotas *todosAlunos, int qtdAlunos, CursosPesos *todosCursos)
{
	FILE *arq;
	arq = fopen(arqName, "w");
	if (arq == NULL) printf("Nao possivel abrir o arquivo %s\n", arqName);
	else
	{
		fprintf(arq, ".+*******+.NAO APROVADOS.+*******+.\n\n");
		ordenaCursosPesosPorCod(todosCursos);
		ordenaCandAlf(todosAlunos, qtdAlunos);

		for(int i = 0; i <= 113; i++) {
			fprintf(arq, "%d %s\n\n", todosCursos[i].cod, todosCursos[i].nomeCurso);

			for(int j = 0; j < qtdAlunos; j++) {
				if (todosAlunos[j].codCurso == todosCursos[i].cod && todosAlunos[j].classificacao == 0) {
					fprintf(arq, "%d %s\n", todosAlunos[j].INSC, todosAlunos[j].nome);
				} 
			}
			fprintf(arq,"\n");
		}
	}
}


// Implementação da busca do candidato pelo seu codigo //

void buscaImprimeCandidato(CursosPesos *cursosPesos, int qtdCursos, DadosTodosCursos *todosDados ,compNotas *vetor, int n, int INSC)
{
	char name[80];
	char cursoNome[50];
	bool achou = false;
	buscarNomePorInsc(todosDados, INSC, name);
	for(int i = 0; i < n; i++) {
		if (vetor[i].INSC == INSC) {
			buscarNomeDoCursoPorCod(cursosPesos, qtdCursos, vetor[i].codCurso, cursoNome);
			printf("%d %s %d/%d/%d %d %s\n", 
				vetor[i].INSC,
				name,
				vetor[i].nasc_cand.dia,
				vetor[i].nasc_cand.mes,
				vetor[i].nasc_cand.ano,
				vetor[i].codCurso,
				cursoNome);
			achou = true;
			break;
		}
	}
	if(!achou)
		printf("Candidato nao encontrado\n");
}

//busca do nome candidato pelo seu codigo de inscrição //

void buscarNomePorInsc(DadosTodosCursos *vet, int INSC, char *name)
{
	for(int j = 0; j <= 113; j++) {
		for (int x = 0; x < vet[j].num_de_candidatos; x++) {
			if (vet[j].dadosCurso[x].num_candidato == INSC) {
				strcpy(name, vet[j].dadosCurso[x].nome);
				break;
			}
		}
	}
}

//Busca do nome do curso pelo codigo do curso //

void buscarNomeDoCursoPorCod(CursosPesos *vet, int n, int codCurso, char *curso)
{
	for (int i = 0; i < n; i++) {
		if (vet[i].cod == codCurso) {
			strcpy(curso, vet[i].nomeCurso);
			break;
		}
	}
}


// Calculos para media final

double EP(int valor, double media, double desvioPd)
{
	return (500 + 100 * (((2 * valor) - media )) / desvioPd);
}


// busca cota, nome, codigo do curso e data de nascimento do candidato  //

void buscaCotaPorInscrito(DadosTodosCursos *todosCursos, compNotas *inscrito)
{
	int indice = 0;
	while (indice <= 113) {
		for (int i = 0; i < todosCursos[indice].num_de_candidatos; i++) {
			if (todosCursos[indice].dadosCurso[i].num_candidato == inscrito->INSC) {			
				// printf("%d %d %s\n", todosCursos[indice].cod_curso, todosCursos[indice].dadosCurso[i].num_candidato, todosCursos[indice].dadosCurso[i].tipoVaga);
				strcpy(inscrito->cota, todosCursos[indice].dadosCurso[i].tipoVaga);
				strcpy(inscrito->nome, todosCursos[indice].dadosCurso[i].nome);
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


// busca pelo codigo do curso pelo numero de inscrição do candidato //

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
}


// busca dos pesos do curso pelo codigo do curso //

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


// calculo na nota final //

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


//computação das notas de todos candidatos e gera um array com todas informações de todos inscritos //

void computarNotas(compNotas *&vet, int n, Acertos *acertosArray, MediaEdp m, MediaEdp dp, CursosPesos *cursosPesos, int qtdCursos, DadosTodosCursos *todosCursos)
{
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
//acertos.txt
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


//dados.txt
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

//cursos_e_vagas.txt
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

//cursos_e_pesos.txt
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

void desalocaTodosArrays(Acertos *acertos, DadosTodosCursos *dadosTodosCursos, CursosVagas *cursosVagas, CursosPesos *cursosPesos, compNotas *notasComputadas)
{
	free(acertos);

	for (int i = 0; i <= 113; i++) {
		free(dadosTodosCursos[i].dadosCurso);
	}
	free(dadosTodosCursos);
	free(cursosVagas);
	free(cursosPesos);
	free(notasComputadas);
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


// ordenação por nota final do array de notas computadas, utilizando o metodo quickSort //

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


// ordenação das prioridades para desempate //

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


// classificação dos inscritos para ordenar todos candidatos aprovados //

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
				else if (strcmp(notasOrd[j].cota, "L1") == 0 && l1 <= vagas[i].L1) {
					notasOrd[j].classificacao = l1;
					l1++;
				}
				else if (strcmp(notasOrd[j].cota, "L3") == 0 && l3 <= vagas[i].L3 ) {
					notasOrd[j].classificacao = l3;
					l3++;
				}
				else if (strcmp(notasOrd[j].cota, "L4") == 0 && l4 <= vagas[i].L4 ) {
					notasOrd[j].classificacao = l4;
					l4++;
				}
				else if (strcmp(notasOrd[j].cota, "L5") == 0 && l5 <= vagas[i].L5 ) {
					notasOrd[j].classificacao = l5;
					l5++;
				}
				else if (strcmp(notasOrd[j].cota, "L7") == 0 && l7 <= vagas[i].L7 ) {
					notasOrd[j].classificacao = l7;
					l7++;
				}
				else if (strcmp(notasOrd[j].cota, "L8") == 0 && l8 <= vagas[i].L8 ) {
					notasOrd[j].classificacao = l8;
					l8++;
				}
				else if (strcmp(notasOrd[j].cota, "L9") == 0 && l9 <= vagas[i].L9 ) {
					notasOrd[j].classificacao = l9;
					l9++;
				}
				else if (strcmp(notasOrd[j].cota, "L11") == 0 && l11 <= vagas[i].L11 ) {
					notasOrd[j].classificacao = l11;
					l11++;
				}
				else if (strcmp(notasOrd[j].cota, "L13") == 0 && l13 <= vagas[i].L13 ) {
					notasOrd[j].classificacao = l13;
					l13++;
				}
				else if (strcmp(notasOrd[j].cota, "L15") == 0 && l15 <= vagas[i].L15 ) {
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


// ordena array de notas computadas pela cota em ordem crescente //

void ordenaPorCotaAlfabetico(compNotas *inscritos, int n)
{
	compNotas aux;
	int min;
	for (int i = 0; i < n; i++) {
		min = i;
		for (int j = i+1; j < n; j++) {
			if (strcmp(inscritos[min].cota, inscritos[j].cota) > 0 ) {
				min = j;
			}
		}
		aux = inscritos[i];
		inscritos[i] = inscritos[min];
		inscritos[min] = aux;
	}

}


/*implementação da geração de um arquivo com todos alunos classificados pela nota, 
aqui todos candidatos que nao possuia classificação igual á 0 seriam impressos, 
pois na logica implementada, quem ficou fora do limite da cota foi classificado com 0 */

void gerarArquivoDosClassificadosPorNota(char *nomeArq, compNotas *inscritos, int qtd_insc, CursosPesos *cursos, int qtd_cursos)
{
	FILE *arq = fopen(nomeArq, "a");
	if (arq == NULL) printf("Ñao foi possivel abrir o arquivo, verifique se o nome digitado contem .txt no final\n");
	else 
	{
		ordenaPorCotaAlfabetico(inscritos, qtd_insc);
		fprintf(arq, "/*LISTA GERAL CLASSIFICADO POR NOTA*/\n");
		for (int i = 0; i < qtd_cursos; i++) {
			fprintf(arq, "\n%d   %s\n", cursos[i].cod, cursos[i].nomeCurso);
			fprintf(arq, "\n");
			fprintf(arq, "INSC   V_LIN  V_MAT  V_NAT  V_HUM  RED  COTA NOTA FINAL CLASSIFICAÇÃO\n");

				for (int j = 0; j < qtd_insc; j++) {
					if (inscritos[j].codCurso == cursos[i].cod && strcmp(inscritos[j].cota, "AC") == 0 && inscritos[j].classificacao != 0) {
						fprintf(arq, "%d %.2lf %.2lf %.2lf %.2lf %.2lf %s %.2lf %d\n", inscritos[j].INSC, inscritos[j].V_LIN, inscritos[j].V_MAT, inscritos[j].V_NAT, 
						inscritos[j].V_HUM, inscritos[j].RED, inscritos[j].cota, inscritos[j].NotaFinal, inscritos[j].classificacao);
					}
				}

				for (int j = 0; j < qtd_insc; j++) {
					if (inscritos[j].codCurso == cursos[i].cod && strcmp(inscritos[j].cota, "L1") == 0 && inscritos[j].classificacao != 0) {
						fprintf(arq, "%d %.2lf %.2lf %.2lf %.2lf %.2lf %s %.2lf %d\n", inscritos[j].INSC, inscritos[j].V_LIN, inscritos[j].V_MAT, inscritos[j].V_NAT, 
						inscritos[j].V_HUM, inscritos[j].RED, inscritos[j].cota, inscritos[j].NotaFinal, inscritos[j].classificacao);
					}
				}

				for (int j = 0; j < qtd_insc; j++) {
					if (inscritos[j].codCurso == cursos[i].cod && strcmp(inscritos[j].cota, "L3") == 0 && inscritos[j].classificacao != 0) {
						fprintf(arq, "%d %.2lf %.2lf %.2lf %.2lf %.2lf %s %.2lf %d\n", inscritos[j].INSC, inscritos[j].V_LIN, inscritos[j].V_MAT, inscritos[j].V_NAT, 
						inscritos[j].V_HUM, inscritos[j].RED, inscritos[j].cota, inscritos[j].NotaFinal, inscritos[j].classificacao);
					}
				}

				for (int j = 0; j < qtd_insc; j++) {
					if (inscritos[j].codCurso == cursos[i].cod && strcmp(inscritos[j].cota, "L4") == 0 && inscritos[j].classificacao != 0) {
						fprintf(arq, "%d %.2lf %.2lf %.2lf %.2lf %.2lf %s %.2lf %d\n", inscritos[j].INSC, inscritos[j].V_LIN, inscritos[j].V_MAT, inscritos[j].V_NAT, 
						inscritos[j].V_HUM, inscritos[j].RED, inscritos[j].cota, inscritos[j].NotaFinal, inscritos[j].classificacao);
					}
				}

				for (int j = 0; j < qtd_insc; j++) {
					if (inscritos[j].codCurso == cursos[i].cod && strcmp(inscritos[j].cota, "L5") == 0 && inscritos[j].classificacao != 0) {
						fprintf(arq, "%d %.2lf %.2lf %.2lf %.2lf %.2lf %s %.2lf %d\n", inscritos[j].INSC, inscritos[j].V_LIN, inscritos[j].V_MAT, inscritos[j].V_NAT, 
						inscritos[j].V_HUM, inscritos[j].RED, inscritos[j].cota, inscritos[j].NotaFinal, inscritos[j].classificacao);
					}
				}

				for (int j = 0; j < qtd_insc; j++) {
					if (inscritos[j].codCurso == cursos[i].cod && strcmp(inscritos[j].cota, "L7") == 0 && inscritos[j].classificacao != 0) {
						fprintf(arq, "%d %.2lf %.2lf %.2lf %.2lf %.2lf %s %.2lf %d\n", inscritos[j].INSC, inscritos[j].V_LIN, inscritos[j].V_MAT, inscritos[j].V_NAT, 
						inscritos[j].V_HUM, inscritos[j].RED, inscritos[j].cota, inscritos[j].NotaFinal, inscritos[j].classificacao);
					}
				}

				for (int j = 0; j < qtd_insc; j++) {
					if (inscritos[j].codCurso == cursos[i].cod && strcmp(inscritos[j].cota, "L8") == 0 && inscritos[j].classificacao != 0) {
						fprintf(arq, "%d %.2lf %.2lf %.2lf %.2lf %.2lf %s %.2lf %d\n", inscritos[j].INSC, inscritos[j].V_LIN, inscritos[j].V_MAT, inscritos[j].V_NAT, 
						inscritos[j].V_HUM, inscritos[j].RED, inscritos[j].cota, inscritos[j].NotaFinal, inscritos[j].classificacao);
					}
				}

				for (int j = 0; j < qtd_insc; j++) {
					if (inscritos[j].codCurso == cursos[i].cod && strcmp(inscritos[j].cota, "L9") == 0 && inscritos[j].classificacao != 0) {
						fprintf(arq, "%d %.2lf %.2lf %.2lf %.2lf %.2lf %s %.2lf %d\n", inscritos[j].INSC, inscritos[j].V_LIN, inscritos[j].V_MAT, inscritos[j].V_NAT, 
						inscritos[j].V_HUM, inscritos[j].RED, inscritos[j].cota, inscritos[j].NotaFinal, inscritos[j].classificacao);
					}
				}

				for (int j = 0; j < qtd_insc; j++) {
					if (inscritos[j].codCurso == cursos[i].cod && strcmp(inscritos[j].cota, "L11") == 0 && inscritos[j].classificacao != 0) {
						fprintf(arq, "%d %.2lf %.2lf %.2lf %.2lf %.2lf %s %.2lf %d\n", inscritos[j].INSC, inscritos[j].V_LIN, inscritos[j].V_MAT, inscritos[j].V_NAT, 
						inscritos[j].V_HUM, inscritos[j].RED, inscritos[j].cota, inscritos[j].NotaFinal, inscritos[j].classificacao);
					}
				}

				for (int j = 0; j < qtd_insc; j++) {
					if (inscritos[j].codCurso == cursos[i].cod && strcmp(inscritos[j].cota, "L13") == 0 && inscritos[j].classificacao != 0) {
						fprintf(arq, "%d %.2lf %.2lf %.2lf %.2lf %.2lf %s %.2lf %d\n", inscritos[j].INSC, inscritos[j].V_LIN, inscritos[j].V_MAT, inscritos[j].V_NAT, 
						inscritos[j].V_HUM, inscritos[j].RED, inscritos[j].cota, inscritos[j].NotaFinal, inscritos[j].classificacao);
					}
				}

				for (int j = 0; j < qtd_insc; j++) {
					if (inscritos[j].codCurso == cursos[i].cod && strcmp(inscritos[j].cota, "L15") == 0 && inscritos[j].classificacao != 0) {
						fprintf(arq, "%d %.2lf %.2lf %.2lf %.2lf %.2lf %s %.2lf %d\n", inscritos[j].INSC, inscritos[j].V_LIN, inscritos[j].V_MAT, inscritos[j].V_NAT, 
						inscritos[j].V_HUM, inscritos[j].RED, inscritos[j].cota, inscritos[j].NotaFinal, inscritos[j].classificacao);
					}
				}

		}
	}

}


//ordenação do array de notas computadas pelo codigo do curso em ordem crescente //
//OBS:metodo de ordenação usado quickSort //
void trocaCursoPeso(CursosPesos *a, CursosPesos *b)
{
	struct CursosPesos aux = *a;
	*a = *b;
	*b = aux;
}

int separadorCursos(int p, int r, CursosPesos *v)
{
	struct CursosPesos x;
	int i, j;
	x = v[p];
	i = p - 1;
	j = r + 1;

	while (1) {
		do {
			j--;
		} while (v[j].cod > x.cod);
		do {
			i++;
		} while (v[i].cod < x.cod);

		if ( i < j)
			trocaCursoPeso(&v[i], &v[j]);
		else
			return j;
	}
}

void quickSortCursoPorCod(int p, int r, CursosPesos *v)
{ 
	int q;
	if (p < r) {
		q = separadorCursos(p, r, v);
		quickSortCursoPorCod(p, q, v);
		quickSortCursoPorCod(q+1, r, v);
	}
}