#include <stdio.h>

int	main(void)
{
	int		a;
	int		b;
	int		*p;

	a = 10;
	b = 20;
	p = &a;
	printf("p가 a를 가리킴: *p = %d\n", *p);
	*p = 11;
	printf("*p = 11 실행 → a = %d (b = %d)\n", a, b);
	p = &b;
	printf("p가 b를 가리킴: *p = %d\n", *p);
	*p = 21;
	printf("*p = 21 실행 → b = %d (a = %d)\n", b, a);
	return (0);
}
