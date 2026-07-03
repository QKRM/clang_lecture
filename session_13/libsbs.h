#ifndef LIBSBS_H
# define LIBSBS_H

# include <stddef.h>

/* 13차시 — 문자열 함수 II */
char	*sbs_strchr(const char *s, int c);
char	*sbs_strrchr(const char *s, int c);
char	*sbs_strnstr(const char *big, const char *little, size_t len);

/* 심화(bonus) — 대소문자 무시 검색 */
char	*sbs_strcasestr(const char *big, const char *little, size_t len);

#endif
