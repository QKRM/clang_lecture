#include <stdio.h>

int main(void)
{
	const int	answer = 42;
	int			guess;
	int			tries;

	guess = 0;
	tries = 0;
	while (1)
	{
		printf("숫자를 맞춰보세요 (1~100): ");
		if (scanf("%d", &guess) != 1)
			break;
		tries++;
		if (guess > answer)
			printf("더 작게!\n");
		else if (guess < answer)
			printf("더 크게!\n");
		else
		{
			printf("정답! %d번 만에 맞혔습니다.\n", tries);
			break;
		}
	}
	return (0);
}
