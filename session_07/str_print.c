#include <stdio.h>

void	str_print(char *s);

int	main(void)
{
	char	msg[] = "hello world";

	str_print(msg);
	return (0);
}

void	str_print(char *s)
{
	char	*p;

	p = s;
	while (*p)
	{
		printf("%c", *p);
		p++;
	}
	printf("\n");
}
