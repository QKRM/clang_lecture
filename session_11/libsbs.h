#ifndef LIBSBS_H
# define LIBSBS_H

# include <stddef.h>

/* 10차시에서 가져온 의존 함수 (calloc / 문자열 함수가 내부에서 사용) */
void	*sbs_memset(void *b, int c, size_t len);
size_t	sbs_strlen(const char *s);

/* 11차시 — 동적 메모리(malloc) 함수 */
void	*sbs_calloc(size_t count, size_t size);
char	*sbs_substr(char const *s, unsigned int start, size_t len);
char	*sbs_strjoin(char const *s1, char const *s2);
char	*sbs_itoa(int n);
char	*sbs_strdup(const char *s);

#endif
