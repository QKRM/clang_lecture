#include <strings.h>
#include <string.h>
#include <stdio.h>
#include "libsbs.h"

/* 표준 strncasecmp를 정답으로. 부호(양/음/0)만 비교. */
static int	sign(int x)
{
	if (x > 0)
		return (1);
	if (x < 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	int		pass;
	int		total;
	int		verbose;
	char	*a[] = {"Hello", "HELLO", "abcZ", "ABC", "MixEd", "Apple", ""};
	char	*b[] = {"help", "world", "abcz", "abx", "mixer", "apple", "X"};
	size_t	n[] = {3, 2, 4, 2, 5, 5, 3};
	int		i;

	verbose = (argc > 1 && strcmp(argv[1], "-v") == 0);
	pass = 0;
	total = 0;
	i = 0;
	while (i < 7)
	{
		int ra = strncasecmp(a[i], b[i], n[i]);
		int rb = sbs_strncasecmp(a[i], b[i], n[i]);
		total++;
		if (sign(ra) == sign(rb))
			pass++;
		else if (verbose)
			printf("  \"%s\" vs \"%s\" n=%zu 부호 %d/%d\n",
				a[i], b[i], n[i], sign(ra), sign(rb));
		i++;
	}
	printf("%d/%d\n", pass, total);
	return (pass != total);
}
