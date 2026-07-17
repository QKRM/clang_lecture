#include "libsbs.h"
#include <stdlib.h>

/*
 * sbs_split이 만든 배열을 통째로 해제한다.
 *  - 각 단어(문자열)를 먼저 free
 *  - 마지막에 배열 자체를 free
 *  - NULL을 넣어도 안전(아무것도 안 함)
 */
void	sbs_free_split(char **arr)
{
	size_t	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
