#include <stdio.h>

int main(void)
{
	int    age    = 21;
	double height = 175.5;
	char   grade  = 'A';
	char   name[] = "Linus";

	printf("=== printf 서식 지정자 데모 ===\n");
	printf("정수  (%%d)     : %d\n", age);
	printf("실수  (%%f)     : %f\n", height);
	printf("실수  (%%.2f)   : %.2f\n", height);
	printf("문자  (%%c)     : %c\n", grade);
	printf("문자열(%%s)     : %s\n", name);
	printf("주소  (%%p)     : %p\n", (void *)&age);
	printf("\n=== 이스케이프 문자 ===\n");
	printf("줄바꿈 (\\n) : 첫 번째 줄\n두 번째 줄\n");
	printf("탭     (\\t) : col1\tcol2\tcol3\n");
	printf("큰따옴표   : \"따옴표 안 텍스트\"\n");
	printf("백슬래시   : 경로\\파일명\n");
	return (0);
}
