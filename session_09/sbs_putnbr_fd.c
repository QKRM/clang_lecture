#include "libsbs.h"
#include <unistd.h>

void	sbs_putnbr_fd(int n, int fd)
{
	long	nb;
	char	c;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		sbs_putnbr_fd((int)(nb / 10), fd);
	c = (char)(nb % 10) + '0';
	write(fd, &c, 1);
}
