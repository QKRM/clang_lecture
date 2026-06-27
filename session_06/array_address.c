#include <stdio.h>

int	main(void)
{
	int		arr[5];
	int		i;

	arr[0] = 10;
	arr[1] = 20;
	arr[2] = 30;
	arr[3] = 40;
	arr[4] = 50;
	i = 0;
	while (i < 5)
	{
		printf("arr[%d] = %d, 주소 = %p\n", i, arr[i], (void *)&arr[i]);
		i++;
	}
	printf("arr      = %p\n", (void *)arr);
	printf("&arr[0]  = %p\n", (void *)&arr[0]);
	return (0);
}
