#include <stdio.h>

void	set_to_ten(int *p);
void	add_one(int *p);

int	main(void)
{
	int	a;

	a = 5;
	printf("시작: a = %d\n", a);
	add_one(&a);
	printf("add_one 후: a = %d\n", a);
	set_to_ten(&a);
	printf("set_to_ten 후: a = %d\n", a);
	return (0);
}

void	set_to_ten(int *p)
{
	*p = 10;
}

void	add_one(int *p)
{
	*p = *p + 1;
}
