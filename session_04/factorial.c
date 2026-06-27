#include <stdio.h>

int	fact_loop(int n);
int	fact_rec(int n);

int	main(void)
{
	int	n;

	n = 1;
	while (n <= 5)
	{
		printf("n=%d  loop=%d  rec=%d\n", n, fact_loop(n), fact_rec(n));
		n++;
	}
	return (0);
}

int	fact_loop(int n)
{
	int	result;
	int	i;

	result = 1;
	i = 2;
	while (i <= n)
	{
		result *= i;
		i++;
	}
	return (result);
}

int	fact_rec(int n)
{
	if (n <= 1)
		return (1);
	return (n * fact_rec(n - 1));
}
