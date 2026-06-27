#include <stdio.h>

int	main(void)
{
	int		n;
	int		*p;

	n = 42;
	p = &n;
	printf("n   값   = %d\n", n);
	printf("n   주소 = %p\n", (void *)&n);
	printf("p   값   = %p\n", (void *)p);
	printf("*p  값   = %d\n", *p);
	*p = 100;
	printf("*p로 수정 후 n = %d\n", n);
	return (0);
}
