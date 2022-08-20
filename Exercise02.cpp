#include <stdio.h>
#include <string.h>

int main() {

	struct
	{
		int number;
		char name[30];
		char course[30];

	} studant[5];

	for (int i = 0; i < 5; i++) {
		scanf("%d ", &studant[i].number);
		fgets(studant[i].name, 30, stdin);
		fgets(studant[i].course, 30, stdin);
	}
  char courseInput[30];
  fgets(courseInput, 30, stdin);

  for (int i = 0; i < 5; i++) {
  	if (strcmp((studant[i].course), courseInput) == 0) {
  		printf("%d %s", studant[i].number, studant[i].name);
  	}
  }
  
	return 0;
}