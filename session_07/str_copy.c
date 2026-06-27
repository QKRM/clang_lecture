#include <stdio.h>

void	str_copy(char *dst, char *src);

int	main(void)
{
	char	src[] = "hello world";
	char	dst[32];

	str_copy(dst, src);
	printf("복사 결과: %s\n", dst);
	return (0);
}

void	str_copy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}
