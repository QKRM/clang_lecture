#include <stdio.h>

int main(void)
{
	printf("=== 자료형 크기 표 (단위: 바이트) ===\n");
	printf("%-20s %s\n", "자료형", "크기");
	printf("%-20s %s\n", "--------------------", "------");
	printf("%-20s %zu\n", "char",          sizeof(char));
	printf("%-20s %zu\n", "unsigned char", sizeof(unsigned char));
	printf("%-20s %zu\n", "short",         sizeof(short));
	printf("%-20s %zu\n", "unsigned short",sizeof(unsigned short));
	printf("%-20s %zu\n", "int",           sizeof(int));
	printf("%-20s %zu\n", "unsigned int",  sizeof(unsigned int));
	printf("%-20s %zu\n", "long",          sizeof(long));
	printf("%-20s %zu\n", "unsigned long", sizeof(unsigned long));
	printf("%-20s %zu\n", "float",         sizeof(float));
	printf("%-20s %zu\n", "double",        sizeof(double));
	printf("%-20s %zu\n", "long double",   sizeof(long double));
	printf("%-20s %zu\n", "pointer (int*)",sizeof(int *));
	printf("\n");
	printf("=== 리터럴 크기 ===\n");
	printf("sizeof(42)     = %zu  (정수 리터럴 → int)\n", sizeof(42));
	printf("sizeof(42L)    = %zu  (long 리터럴)\n",       sizeof(42L));
	printf("sizeof(3.14)   = %zu  (실수 리터럴 → double)\n", sizeof(3.14));
	printf("sizeof(3.14f)  = %zu  (float 리터럴)\n",     sizeof(3.14f));
	printf("sizeof('A')    = %zu  (문자 리터럴 → int)\n",  sizeof('A'));
	return (0);
}
