#include <stdio.h>
#include <string.h>

typedef struct s_student
{
	char	name[20];
	int		age;
	int		score;
}	t_student;

int	main(void)
{
	t_student	s;
	t_student	*p;

	strcpy(s.name, "Kim");
	s.age = 20;
	s.score = 95;
	p = &s;
	printf("p->age = %d\n", p->age);
	p->age++;
	printf("나이 +1 후 s.age = %d\n", s.age);
	return (0);
}
