#include <stdio.h>

int	str_length(char *s);

int	main(void)
{
	char	a[] = "hello";
	char	b[] = "";
	char	c[] = "42 seoul";

	printf("\"hello\" → %d\n", str_length(a));
	printf("\"\" → %d\n", str_length(b));
	printf("\"42 seoul\" → %d\n", str_length(c));
	return (0);
}

int	str_length(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
