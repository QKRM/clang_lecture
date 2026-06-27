#include <stdio.h>

int	main(void)
{
	int		arr[5];
	int		*p;
	int		i;

	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	arr[3] = 4;
	arr[4] = 5;
	p = arr;
	i = 0;
	while (i < 5)
	{
		printf("*(p + %d) = %d\n", i, *(p + i));
		i++;
	}
	printf("--- 포인터를 직접 이동 ---\n");
	p = arr;
	while (p < arr + 5)
	{
		printf("%d ", *p);
		p++;
	}
	printf("\n");
	return (0);
}
