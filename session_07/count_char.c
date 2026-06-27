#include <stdio.h>

int	count_char(char *s, char target);

int	main(void)
{
	char	s[] = "banana";

	printf("\"banana\"에서 'a' → %d\n", count_char(s, 'a'));
	printf("\"banana\"에서 'n' → %d\n", count_char(s, 'n'));
	printf("\"banana\"에서 'z' → %d\n", count_char(s, 'z'));
	return (0);
}

int	count_char(char *s, char target)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == target)
			count++;
		i++;
	}
	return (count);
}
