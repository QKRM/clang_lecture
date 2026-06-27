#include <stdio.h>

typedef struct s_rect
{
	int	width;
	int	height;
}	t_rect;

int	area(t_rect r);
int	perimeter(t_rect r);

int	main(void)
{
	t_rect	r;

	r.width = 5;
	r.height = 3;
	printf("사각형 %dx%d → 넓이=%d, 둘레=%d\n",
		r.width, r.height, area(r), perimeter(r));
	return (0);
}

int	area(t_rect r)
{
	return (r.width * r.height);
}

int	perimeter(t_rect r)
{
	return (2 * (r.width + r.height));
}
