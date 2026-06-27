#include <stdio.h>

void	str_reverse(char *s);

int	main(void)
{
	char	a[] = "hello";
	char	b[] = "42seoul";

	str_reverse(a);
	str_reverse(b);
	printf("%s\n", a);
	printf("%s\n", b);
	return (0);
}

void	str_reverse(char *s)
{
	int		left;
	int		right;
	char	tmp;

	left = 0;
	right = 0;
	while (s[right])
		right++;
	right--;
	while (left < right)
	{
		tmp = s[left];
		s[left] = s[right];
		s[right] = tmp;
		left++;
		right--;
	}
}
