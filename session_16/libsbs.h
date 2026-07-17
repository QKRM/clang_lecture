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

/* 10차시 — 메모리 함수 */
void	*sbs_memset(void *b, int c, size_t len);
void	sbs_bzero(void *s, size_t n);
void	*sbs_memcpy(void *dst, const void *src, size_t n);
void	*sbs_memccpy(void *dst, const void *src, int c, size_t n);
void	*sbs_memchr(const void *s, int c, size_t n);
int		sbs_memcmp(const void *s1, const void *s2, size_t n);

/* 11차시 — 동적 메모리(malloc) */
void	*sbs_calloc(size_t count, size_t size);
char	*sbs_substr(char const *s, unsigned int start, size_t len);
char	*sbs_strjoin(char const *s1, char const *s2);
char	*sbs_itoa(int n);
char	*sbs_strdup(const char *s);

/* 12차시 — 문자열 함수 I */
size_t	sbs_strlen(const char *s);
size_t	sbs_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	sbs_strlcat(char *dst, const char *src, size_t dstsize);
size_t	sbs_strnlen(const char *s, size_t maxlen);
char	*sbs_strncpy(char *dst, const char *src, size_t n);
char	*sbs_strncat(char *dst, const char *src, size_t n);
int		sbs_strcmp(const char *s1, const char *s2);
int		sbs_strcasecmp(const char *s1, const char *s2);
int		sbs_strncasecmp(const char *s1, const char *s2, size_t n);

/* 13차시 — 문자열 함수 II */
char	*sbs_strchr(const char *s, int c);
char	*sbs_strrchr(const char *s, int c);
char	*sbs_strnstr(const char *big, const char *little, size_t len);

/* 14차시 — 문자열 비교와 변환 */
int		sbs_strncmp(const char *s1, const char *s2, size_t n);
int		sbs_atoi(const char *str);

/* 16차시 — 미니셸용 문자열 쪼개기 */
char	**sbs_split(const char *s, char c);
void	sbs_free_split(char **arr);

#endif
