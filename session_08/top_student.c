#include <stdio.h>

typedef struct s_student
{
	char	name[20];
	int		age;
	int		score;
}	t_student;

t_student	*find_top(t_student *arr, int size);

int	main(void)
{
	t_student	class[3] = {
		{"Kim", 20, 95},
		{"Lee", 21, 88},
		{"Park", 22, 77}
	};
	t_student	*top;

	top = find_top(class, 3);
	printf("최고 점수: %s (%d점)\n", top->name, top->score);
	return (0);
}

t_student	*find_top(t_student *arr, int size)
{
	t_student	*top;
	int			i;

	top = &arr[0];
	i = 1;
	while (i < size)
	{
		if (arr[i].score > top->score)
			top = &arr[i];
		i++;
	}
	return (top);
}
