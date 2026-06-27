#ifndef LIBSBS_H
# define LIBSBS_H

# include <stddef.h>

/* 12차시 — 문자열 함수 I */
size_t	sbs_strlen(const char *s);
size_t	sbs_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	sbs_strlcat(char *dst, const char *src, size_t dstsize);

#endif
