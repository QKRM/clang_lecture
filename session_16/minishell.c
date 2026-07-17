#include <stdio.h>
#include <stdlib.h>
#include "libsbs.h"

/*
 * minishell — libsbs로 만든 아주 작은 셸 (16차시 종합 프로젝트)
 *
 * 15차시에 만든 '껍데기'(REPL 루프)에 이번엔 알맹이를 채운다:
 *   1) 입력 한 줄을 sbs_split으로 단어 배열로 쪼갠다
 *   2) 첫 단어(명령 이름)를 sbs_strcmp로 판별한다
 *   3) 해당 내장(builtin) 명령을 실행한다
 *   4) 배열을 free하고 다시 1번으로
 *
 * fork/exec 같은 외부 프로그램 실행은 쓰지 않는다. 모든 명령은
 * 우리가 직접 구현한 내장 명령이다. 지금까지 만든 libsbs 함수만으로
 * 돌아간다는 점이 핵심이다.
 */

#define BUF_SIZE 1024

/* fgets가 함께 담아온 줄 끝 개행(\n)을 지운다 (15차시와 동일) */
static void	strip_newline(char *line)
{
	size_t	len;

	len = sbs_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

/* echo: 명령 뒤의 인자들을 공백으로 이어 그대로 출력 */
static void	builtin_echo(char **args)
{
	size_t	i;

	i = 1;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}

/* upper: 인자들을 대문자로 바꿔 출력 (9차시 sbs_toupper) */
static void	builtin_upper(char **args)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			printf("%c", sbs_toupper((unsigned char)args[i][j]));
			j++;
		}
		if (args[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}

/* len: 각 인자의 길이를 출력 (12차시 sbs_strlen) */
static void	builtin_len(char **args)
{
	size_t	i;

	if (args[1] == NULL)
	{
		printf("len: 인자가 필요합니다\n");
		return ;
	}
	i = 1;
	while (args[i])
	{
		printf("%s: %zu\n", args[i], sbs_strlen(args[i]));
		i++;
	}
}

static void	builtin_help(void)
{
	printf("사용 가능한 명령:\n");
	printf("  echo [말...]   입력한 말을 그대로 출력\n");
	printf("  upper [말...]  대문자로 출력\n");
	printf("  len [말...]    각 말의 길이 출력\n");
	printf("  help          이 도움말\n");
	printf("  exit          종료\n");
}

/*
 * 명령 해석 + 실행.
 *  - 반환 1: 셸을 종료하라는 신호(exit)
 *  - 반환 0: 계속
 */
static int	run_command(char **args)
{
	if (args[0] == NULL)
		return (0);
	if (sbs_strcmp(args[0], "exit") == 0)
		return (1);
	if (sbs_strcmp(args[0], "echo") == 0)
		builtin_echo(args);
	else if (sbs_strcmp(args[0], "upper") == 0)
		builtin_upper(args);
	else if (sbs_strcmp(args[0], "len") == 0)
		builtin_len(args);
	else if (sbs_strcmp(args[0], "help") == 0)
		builtin_help();
	else
		printf("minishell: %s: command not found\n", args[0]);
	return (0);
}

int	main(void)
{
	char	line[BUF_SIZE];
	char	**args;
	int		done;

	done = 0;
	while (!done)
	{
		printf("minishell$ ");
		fflush(stdout);
		if (fgets(line, BUF_SIZE, stdin) == NULL)
		{
			printf("\n");
			break ;
		}
		strip_newline(line);
		args = sbs_split(line, ' ');
		if (args == NULL)
			break ;
		done = run_command(args);
		sbs_free_split(args);
	}
	printf("bye\n");
	return (0);
}
