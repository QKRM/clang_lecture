#include <stdio.h>

void	print_value(const int *p);

int	main(void)
{
	int	n;

	n = 7;
	printf("값 읽기: ");
	print_value(&n);
	return (0);
}

void	print_value(const int *p)
{
	printf("%d\n", *p);
	/* *p = 100;  // 주석을 풀면 컴파일 에러: const 값은 수정 불가 */
}
