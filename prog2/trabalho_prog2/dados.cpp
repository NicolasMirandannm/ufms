#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data {
	int dia;
	int mes;
	int ano;
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

void lerDados(FILE *arq, Dados *vet, int n)
{
	for (int i = 0; i < n; i++) {
		fscanf(arq, "%d %[^1234567890] %d/%d/%d %s", &vet[i].num_candidato, vet[i].nome, &vet[i].nascimento.dia, &vet[i].nascimento.mes, &vet[i].nascimento.ano, vet[i].tipoVaga);
		//printf("%d - %d %s %d/%d/%d %s\n", i, vet[i].num_candidato, vet[i].nome, vet[i].nascimento.dia, vet[i].nascimento.mes, vet[i].nascimento.ano, vet[i].tipoVaga);
	}
}


int main() {

	FILE *dados;

	// Tratando o arquivo de dados;
	struct DadosTodosCursos *dadosTodosCursos;
	int ND, codigo_do_curso;
	dados = fopen("dados.txt", "r");
	if (dados == NULL) printf("Nao foi possivel abrir o arquivo de dados.txt\n");
	else {

		dadosTodosCursos = (DadosTodosCursos*) calloc (113, sizeof(DadosTodosCursos));
		if ( dadosTodosCursos ==  NULL) printf("vetor gigante de dados de todos os cursos nao pode ser alocado\n");
		int indice = 0;
		while( feof(dados) == 0) {

			fscanf(dados, "%d %d", &codigo_do_curso, &ND);

			dadosTodosCursos[indice].cod_curso = codigo_do_curso;
			dadosTodosCursos[indice].num_de_candidatos = ND;
			dadosTodosCursos[indice].dadosCurso = (Dados*) calloc (ND, sizeof(Dados));
			if (dadosTodosCursos[indice].dadosCurso == NULL) printf("Vetor de dados não pode ser alocado!\n");
			lerDados(dados, dadosTodosCursos[indice].dadosCurso, ND);

			//free(dadosTodosCursos[indice].dadosCurso);
			indice++;
		}
		fclose(dados);
		
		printf("\n\n");
		
		printf("%d %d %d %s %d/%d/%d %s\n", dadosTodosCursos[0].cod_curso, dadosTodosCursos[0].num_de_candidatos, dadosTodosCursos[0].dadosCurso[0].num_candidato, dadosTodosCursos[0].dadosCurso[0].nome, dadosTodosCursos[0].dadosCurso[0].nascimento.dia, dadosTodosCursos[0].dadosCurso[0].nascimento.mes, dadosTodosCursos[0].dadosCurso[0].nascimento.ano, dadosTodosCursos[0].dadosCurso[0].tipoVaga);
	}
	

	 free(dadosTodosCursos);

  return 0;
}