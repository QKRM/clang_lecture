#include <stdio.h>

int	main(void)
{
	int		arr[3];
	int		*pi;
	char	cbuf[3];
	char	*pc;

	arr[0] = 10;
	arr[1] = 20;
	arr[2] = 30;
	cbuf[0] = 'A';
	cbuf[1] = 'B';
	cbuf[2] = 'C';
	pi = arr;
	pc = cbuf;
	printf("int  *: p=%p  p+1=%p  (차이 %ld바이트)\n",
		(void *)pi, (void *)(pi + 1), (long)((char *)(pi + 1) - (char *)pi));
	printf("char *: p=%p  p+1=%p  (차이 %ld바이트)\n",
		(void *)pc, (void *)(pc + 1), (long)((pc + 1) - pc));
	printf("sizeof(int *)  = %zu\n", sizeof(int *));
	printf("sizeof(char *) = %zu\n", sizeof(char *));
	return (0);
}
