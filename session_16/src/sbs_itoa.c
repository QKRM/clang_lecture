#include "libsbs.h"
#include <stdlib.h>

/*
 * 정수 n을 사람이 읽는 문자열로 변환해 새 메모리에 만든다.
 *  - 음수 부호, INT_MIN(-2147483648)까지 처리 (long 사용)
 *  - 반환 메모리는 호출자가 free
 */
char	*sbs_itoa(int n)
{
	long	nb;
	long	tmp;
	int		sign;
	int		len;
	char	*str;

	nb = n;
	sign = 0;
	if (nb < 0)
	{
		sign = 1;
		nb = -nb;
	}
	len = 1;
	tmp = nb;
	while (tmp >= 10)
	{
		tmp /= 10;
		len++;
	}
	len += sign;
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	len--;
	while (nb >= 10)
	{
		str[len--] = (char)(nb % 10) + '0';
		nb /= 10;
	}
	str[len] = (char)nb + '0';
	if (sign)
		str[0] = '-';
	return (str);
}
