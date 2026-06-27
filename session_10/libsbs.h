#ifndef LIBSBS_H
# define LIBSBS_H

# include <stddef.h>

/* 9차시 — 문자 분류/변환 */
int		sbs_isalpha(int c);
int		sbs_isdigit(int c);
int		sbs_isalnum(int c);
int		sbs_isascii(int c);
int		sbs_isprint(int c);
int		sbs_toupper(int c);
int		sbs_tolower(int c);

/* 10차시 — 메모리 함수 I */
void	*sbs_memset(void *b, int c, size_t len);
void	sbs_bzero(void *s, size_t n);
void	*sbs_memcpy(void *dst, const void *src, size_t n);
void	*sbs_memccpy(void *dst, const void *src, int c, size_t n);
void	*sbs_memchr(const void *s, int c, size_t n);
int		sbs_memcmp(const void *s1, const void *s2, size_t n);

#endif
