#include <stdio.h>

int main(void)
{
	int row;
	int s;
	int star;

	row = 1;
	while (row <= 5)
	{
		s = 0;
		while (s < 5 - row)
		{
			printf(" ");
			s++;
		}
		star = 0;
		while (star < 2 * row - 1)
		{
			printf("*");
			star++;
		}
		printf("\n");
		row++;
	}
	return (0);
}
