#include <stdio.h>

int	add(int a, int b);
int	sub(int a, int b);
int	mul(int a, int b);
int	divide(int a, int b);

int	main(void)
{
	int	a;
	int	b;

	a = 12;
	b = 4;
	printf("add: %d\n", add(a, b));
	printf("sub: %d\n", sub(a, b));
	printf("mul: %d\n", mul(a, b));
	printf("divide: %d\n", divide(a, b));
	return (0);
}

int	add(int a, int b)
{
	return (a + b);
}

int	sub(int a, int b)
{
	return (a - b);
}

int	mul(int a, int b)
{
	return (a * b);
}

int	divide(int a, int b)
{
	if (b == 0)
		return (0);
	return (a / b);
}
