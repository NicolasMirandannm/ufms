#include <stdio.h>
#include <stdlib.h>

#define length(x) (int) (sizeof(x) / sizeof (x[0])) 

struct Data
{
	int dia;
	int mes;
	int ano;
};



void teste(Data *data)
{
	data->dia = 0;
	for (int i = 0; i < 5; i++) {
		data->dia += 1;
	}
	data->dia /= 2;
}

void tes(int *teste) {
	printf("%d\n", length(teste));
}

int main() {
	Data test;
	teste(&test);
	printf("%d %d %d\n", test.dia, test.mes, test.ano);

	int a[19];
	int n = length(a);

	printf("tamanho do vetor 'a': %d\n", n);
	return 0;
}