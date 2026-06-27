#include <stdio.h>

typedef struct s_student
{
	char	name[20];
	int		age;
	int		score;
}	t_student;

int	main(void)
{
	t_student	class[3] = {
		{"Kim", 20, 95},
		{"Lee", 21, 88},
		{"Park", 22, 77}
	};
	int			i;

	i = 0;
	while (i < 3)
	{
		printf("[%d] %-4s %d %d\n", i, class[i].name,
			class[i].age, class[i].score);
		i++;
	}
	return (0);
}
