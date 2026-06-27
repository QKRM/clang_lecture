#include "libsbs.h"
#include <unistd.h>

void	sbs_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
