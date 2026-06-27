#include <stdio.h>

int main(void)
{
	int dan;
	int i;

	dan = 2;
	while (dan <= 9)
	{
		printf("%d단\n", dan);
		i = 1;
		while (i <= 9)
		{
			printf("%d x %d = %d\n", dan, i, dan * i);
			i++;
		}
		printf("\n");
		dan++;
	}
	return (0);
}
