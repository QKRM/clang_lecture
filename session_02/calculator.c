#include <stdio.h>

int main(void)
{
	int    a = 17;
	int    b = 5;
	double result_real;

	result_real = (double)a / b;
	printf("=== 계산기 ===\n");
	printf("a = %d, b = %d\n\n", a, b);
	printf("덧셈        : %d + %d = %d\n",    a, b, a + b);
	printf("뺄셈        : %d - %d = %d\n",    a, b, a - b);
	printf("곱셈        : %d * %d = %d\n",    a, b, a * b);
	printf("나눗셈(정수): %d / %d = %d\n",    a, b, a / b);
	printf("나눗셈(실수): %d / %d = %.6f\n",  a, b, result_real);
	printf("나머지      : %d %% %d = %d\n",   a, b, a % b);
	printf("\n=== 증감 연산자 ===\n");
	printf("a++ (후위) : a = %d → ", a);
	a++;
	printf("%d\n", a);
	printf("++a (전위) : a = %d → ", a);
	++a;
	printf("%d\n", a);
	return (0);
}
