#include <stdio.h>

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

int	dist_squared(t_point a, t_point b);

int	main(void)
{
	t_point	o;
	t_point	p;
	t_point	q;
	t_point	r;

	o.x = 0;
	o.y = 0;
	p.x = 3;
	p.y = 4;
	q.x = 1;
	q.y = 1;
	r.x = 4;
	r.y = 5;
	printf("(0,0) ~ (3,4) 거리² = %d\n", dist_squared(o, p));
	printf("(1,1) ~ (4,5) 거리² = %d\n", dist_squared(q, r));
	return (0);
}

int	dist_squared(t_point a, t_point b)
{
	int	dx;
	int	dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	return (dx * dx + dy * dy);
}
