#include <stdio.h>

struct Date
{
	int day;
	int month;
	int year;
};

struct Event
{
	char name[60];
	Date date;
};

int main() {

	Event array[5];

	for (int i = 0; i < 5; i++) {
		scanf("%s", array[i].name);
		scanf("%d/%d/%d", &array[i].date.day , &array[i].date.month , &array[i].date.year );
	}

	int month, year;

	do
	{
		scanf("%d/%d", &month, &year);
		for (int i = 0; i < 5; i++) {

		if (array[i].date.month == month && array[i].date.year == year) {
			printf("%s\n", array[i].name);
		}
	}

	} while (month > 0);

	

	return 0;
}