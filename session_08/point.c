#include <stdio.h>

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

int	main(void)
{
	t_point	p;

	p.x = 3;
	p.y = 4;
	printf("p = (%d, %d)\n", p.x, p.y);
	return (0);
}
