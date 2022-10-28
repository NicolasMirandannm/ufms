#include <stdio.h>
#include <string.h>

// struct compNotas {
// 	int INSC;
// 	double V_LIN;
// 	double V_MAT;
// 	double V_NAT;
// 	double V_HUM;
// 	double RED;
// 	char cota[3];
// 	double NotaFinal;
// 	int classificacao;
// 	int codCurso;
// 	Data nasc_cand;
// };





int main() {

	int vet[] = {1,2,3,4,5,6,7,8,9,10};

	for (int i = 0; vet[i] != NULL; i++) {
		printf("%d\n", vet[i]);
	}

	// struct aluno vet[3];
	// for (int i = 0; i < 3; i++) {
	// 	scanf("%d %s", &vet[i].nota, vet[i].cod_curso);
	// }

	// ordenaAlfabetico(vet, 3);

	// for(int i = 0; i < 3; i++) {
	// 	printf("%d %s\n", vet[i].nota, vet[i].cod_curso);
	// }

	return 0;
}


// void ordenaAlfabetico(aluno *alunos, int n)
// {
// 	aluno aux;
// 	int min;
// 	for (int i = 0; i < n; i++) {
// 		min = i;
// 		for (int j = i+1; j < n; j++) {
// 			if (strcmp(alunos[i].cod_curso, alunos[j].cod_curso) > 0 ) {
// 				min = j;
// 			}
// 		}
// 		aux = alunos[i];
// 		alunos[i] = alunos[min];
// 		alunos[min] = aux;
// 	}

// }