#include <stdio.h>

int	is_palindrome(char *s);

int	main(void)
{
	char	a[] = "level";
	char	b[] = "hello";
	char	c[] = "42024";

	printf("\"level\" → %s\n", is_palindrome(a) ? "회문" : "회문 아님");
	printf("\"hello\" → %s\n", is_palindrome(b) ? "회문" : "회문 아님");
	printf("\"42024\" → %s\n", is_palindrome(c) ? "회문" : "회문 아님");
	return (0);
}

int	is_palindrome(char *s)
{
	int	left;
	int	right;

	left = 0;
	right = 0;
	while (s[right])
		right++;
	right--;
	while (left < right)
	{
		if (s[left] != s[right])
			return (0);
		left++;
		right--;
	}
	return (1);
}
