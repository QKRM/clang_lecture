#include <stdio.h>
#include <string.h>

typedef struct s_student
{
	char	name[20];
	int		age;
	int		score;
}	t_student;

void	print_student(t_student s);
void	set_score(t_student *p, int score);

int	main(void)
{
	t_student	s;

	strcpy(s.name, "Kim");
	s.age = 20;
	s.score = 90;
	printf("변경 전: ");
	print_student(s);
	set_score(&s, 100);
	printf("변경 후: ");
	print_student(s);
	return (0);
}

void	print_student(t_student s)
{
	printf("%s %d\n", s.name, s.score);
}

void	set_score(t_student *p, int score)
{
	p->score = score;
}
