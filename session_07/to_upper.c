#include <stdio.h>

void	to_upper(char *s);

int	main(void)
{
	char	s[] = "Hello, 42!";

	to_upper(s);
	printf("%s\n", s);
	return (0);
}

void	to_upper(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] = s[i] - 32;
		i++;
	}
}
