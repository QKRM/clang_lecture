#include <stdio.h>

int	main(void)
{
	int		n;
	int		*p;
	int		**pp;

	n = 42;
	p = &n;
	pp = &p;
	printf("n     = %d\n", n);
	printf("*p    = %d\n", *p);
	printf("**pp  = %d\n", **pp);
	printf("--- 주소 ---\n");
	printf("&n    = %p\n", (void *)&n);
	printf("p     = %p\n", (void *)p);
	printf("*pp   = %p (p의 값 = n의 주소)\n", (void *)*pp);
	**pp = 100;
	printf("**pp = 100 실행 후 n = %d\n", n);
	return (0);
}
