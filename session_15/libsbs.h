#ifndef LIBSBS_H
# define LIBSBS_H

# include <stddef.h>

/* 데모용 일부 함수 (실제 과정에서는 9~14차시 전체가 들어감) */
int		sbs_isalpha(int c);
int		sbs_toupper(int c);
size_t	sbs_strlen(const char *s);
char	*sbs_strdup(const char *s);
int		sbs_strcmp(const char *s1, const char *s2);

#endif
