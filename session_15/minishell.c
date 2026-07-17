#include <stdio.h>
#include <stdlib.h>
#include "libsbs.h"

/*
 * minishell (15차시 버전 — '껍데기'만)
 *
 * 셸의 심장은 아래 4단계를 무한 반복하는 루프다:
 *   1) 프롬프트를 찍고
 *   2) 한 줄을 읽고
 *   3) 해석해서 실행하고
 *   4) 다시 1번으로
 * 이 반복을 REPL(Read-Eval-Print Loop)이라 부른다. bash도 구조는 같다.
 *
 * 15차시에서는 1·2·4단계만 만든다. 3단계(해석/실행)는 지금은
 * "입력한 걸 그대로 되돌려주기"로 때우고, 16차시에서 진짜 명령
 * 해석기로 채운다.
 *
 * 여기서도 표준 함수 대신 우리가 만든 함수를 쓴다:
 *   - sbs_strlen : 줄 끝의 개행(\n)을 찾아 지울 때
 *   - sbs_strcmp : 입력이 "exit"인지 비교할 때
 */

#define BUF_SIZE 1024

/*
 * fgets는 사용자가 누른 Enter(\n)까지 함께 담아온다.
 * 그대로 두면 "exit\n" != "exit" 라서 비교가 실패한다. 그래서 지운다.
 */
static void	strip_newline(char *line)
{
	size_t	len;

	len = sbs_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

int	main(void)
{
	char	line[BUF_SIZE];

	while (1)
	{
		printf("minishell$ ");
		/*
		 * 프롬프트에는 개행이 없다. stdout은 줄 단위로 모았다가 내보내므로,
		 * 개행이 올 때까지 화면에 안 나올 수 있다. fflush로 지금 당장 내보낸다.
		 */
		fflush(stdout);
		/* fgets가 NULL → 입력이 끝났다는 뜻 (Ctrl+D) */
		if (fgets(line, BUF_SIZE, stdin) == NULL)
		{
			printf("\n");
			break ;
		}
		strip_newline(line);
		if (sbs_strcmp(line, "exit") == 0)
			break ;
		if (sbs_strcmp(line, "") == 0)
			continue ;
		/* 16차시에서 이 자리에 '명령 해석 + 실행'이 들어간다 */
		printf("입력: %s\n", line);
	}
	printf("bye\n");
	return (0);
}
