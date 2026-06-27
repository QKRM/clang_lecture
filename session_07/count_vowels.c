#include <stdio.h>

int	is_vowel(char c);
int	count_vowels(char *s);

int	main(void)
{
	char	a[] = "Hello World";
	char	b[] = "AEIOU";
	char	c[] = "xyz";

	printf("\"Hello World\" → %d\n", count_vowels(a));
	printf("\"AEIOU\" → %d\n", count_vowels(b));
	printf("\"xyz\" → %d\n", count_vowels(c));
	return (0);
}

int	is_vowel(char c)
{
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
		return (1);
	return (0);
}

int	count_vowels(char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (is_vowel(s[i]))
			count++;
		i++;
	}
	return (count);
}
