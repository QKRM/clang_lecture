#include <stdio.h>

void	try_change(int x);

int	main(void)
{
	int	a;

	a = 5;
	printf("호출 전: a = %d\n", a);
	try_change(a);
	printf("호출 후: a = %d\n", a);
	return (0);
}

void	try_change(int x)
{
	x = 999;
	printf("함수 안: x = %d\n", x);
}
