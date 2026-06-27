#include <stdio.h>

int	sum_array(int *arr, int size);
int	max_array(int *arr, int size);

int	main(void)
{
	int	arr[6];

	arr[0] = 12;
	arr[1] = 7;
	arr[2] = 30;
	arr[3] = 5;
	arr[4] = 18;
	arr[5] = 9;
	printf("합계 = %d\n", sum_array(arr, 6));
	printf("최댓값 = %d\n", max_array(arr, 6));
	return (0);
}

int	sum_array(int *arr, int size)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < size)
	{
		sum += arr[i];
		i++;
	}
	return (sum);
}

int	max_array(int *arr, int size)
{
	int	i;
	int	max;

	max = arr[0];
	i = 1;
	while (i < size)
	{
		if (arr[i] > max)
			max = arr[i];
		i++;
	}
	return (max);
}
