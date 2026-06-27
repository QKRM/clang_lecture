#include <stdio.h>

int	fib_loop(int n);
int	fib_rec(int n);

int	main(void)
{
	int	n;

	n = 0;
	while (n <= 10)
	{
		printf("fib(%d) = %d  (rec=%d)\n", n, fib_loop(n), fib_rec(n));
		n++;
	}
	return (0);
}

int	fib_loop(int n)
{
	int	prev;
	int	curr;
	int	next;
	int	i;

	if (n < 2)
		return (n);
	prev = 0;
	curr = 1;
	i = 2;
	while (i <= n)
	{
		next = prev + curr;
		prev = curr;
		curr = next;
		i++;
	}
	return (curr);
}

int	fib_rec(int n)
{
	if (n < 2)
		return (n);
	return (fib_rec(n - 1) + fib_rec(n - 2));
}
