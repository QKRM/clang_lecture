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

	strcpy(s.name, "Kim");
	s.age = 20;
	s.score = 95;
	printf("이름: %s, 나이: %d, 점수: %d\n", s.name, s.age, s.score);
	return (0);
}
