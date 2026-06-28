#ifndef LIBSBS_H
# define LIBSBS_H

# include <stddef.h>

/* 12차시 — 문자열 함수 I (길이·복사·이어붙이기·비교) */
size_t	sbs_strlen(const char *s);
size_t	sbs_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	sbs_strlcat(char *dst, const char *src, size_t dstsize);
size_t	sbs_strnlen(const char *s, size_t maxlen);
char	*sbs_strncpy(char *dst, const char *src, size_t n);
char	*sbs_strncat(char *dst, const char *src, size_t n);
int		sbs_strcmp(const char *s1, const char *s2);
int		sbs_strcasecmp(const char *s1, const char *s2);
int		sbs_strncasecmp(const char *s1, const char *s2, size_t n);

#endif
