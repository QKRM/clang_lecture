#include <stdio.h>

void	divmod(int a, int b, int *quot, int *rem);
void	min_max(int a, int b, int *min, int *max);

int	main(void)
{
	int	q;
	int	r;
	int	lo;
	int	hi;

	divmod(17, 5, &q, &r);
	printf("17 / 5 → 몫=%d 나머지=%d\n", q, r);
	min_max(8, 3, &lo, &hi);
	printf("min=%d max=%d\n", lo, hi);
	return (0);
}

void	divmod(int a, int b, int *quot, int *rem)
{
	*quot = a / b;
	*rem = a % b;
}

void	min_max(int a, int b, int *min, int *max)
{
	if (a < b)
	{
		*min = a;
		*max = b;
	}
	else
	{
		*min = b;
		*max = a;
	}
}
