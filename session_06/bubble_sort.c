#include <stdio.h>

void	bubble_sort(int *arr, int size);
void	print_array(int *arr, int size);

int	main(void)
{
	int	arr[7];

	arr[0] = 5;
	arr[1] = 2;
	arr[2] = 9;
	arr[3] = 1;
	arr[4] = 7;
	arr[5] = 3;
	arr[6] = 8;
	printf("정렬 전: ");
	print_array(arr, 7);
	bubble_sort(arr, 7);
	printf("정렬 후: ");
	print_array(arr, 7);
	return (0);
}

void	bubble_sort(int *arr, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_array(int *arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");
}
