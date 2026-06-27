#include <stdio.h>

void	swap(int *a, int *b);

int	main(void)
{
	int	x;
	int	y;

	x = 3;
	y = 7;
	printf("교환 전: x = %d, y = %d\n", x, y);
	swap(&x, &y);
	printf("교환 후: x = %d, y = %d\n", x, y);
	return (0);
}

void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
