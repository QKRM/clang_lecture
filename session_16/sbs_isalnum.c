#include "libsbs.h"

int	sbs_isalnum(int c)
{
	if (sbs_isalpha(c) || sbs_isdigit(c))
		return (1);
	return (0);
}
