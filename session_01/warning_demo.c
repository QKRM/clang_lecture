#include <stdio.h>

/*
** 교육용 경고 데모 — -Wall -Wextra -Werror 체험
**
** 아래 두 명령어를 순서대로 실행해 결과를 비교하세요.
**
** 1) 경고 무시:  gcc warning_demo.c -o warning_demo
**    → 컴파일 성공. 하지만 위험한 코드가 숨어 있습니다.
**
** 2) 경고 엄격:  gcc -Wall -Wextra -Werror warning_demo.c -o warning_demo
**    → 컴파일 실패! 에러 메시지를 읽고 문제를 찾아보세요.
**
** 수정 과제: 경고를 모두 제거해 2번 명령으로도 컴파일되게 만드세요.
*/

int main(void)
{
	int result = 42;      /* 경고: unused variable 'result' */
	int x;                /* 경고: 'x' is used uninitialized */

	printf("계산 결과: %d\n", x);
	return (0);
}
