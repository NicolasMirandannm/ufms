#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lerTexto(char *teste, char *teste1)
{
	// while (*teste1 != '\0') {
	// 	*teste = *teste1;
	// 	++teste1;
	// 	++teste;
	// }
	strcpy(teste, teste1);
}

int main() {
	
	char teste1[] = "hello world";
	char teste[20];
	lerTexto(teste, teste1);
	printf("%s\n", teste);
	return 0;
}