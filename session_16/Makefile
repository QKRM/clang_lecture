# ============================================================
# libsbs 종합 정적 라이브러리 Makefile (16차시 최종)
#   9~14차시에서 구현한 26개 함수를 하나로 통합
# ============================================================

NAME    = libsbs.a

CC      = cc
CFLAGS  = -Wall -Wextra -Werror
AR      = ar
ARFLAGS = rcs
RM      = rm -f

SRCS    = sbs_isalpha.c sbs_isdigit.c sbs_isalnum.c sbs_isascii.c \
          sbs_isprint.c sbs_toupper.c sbs_tolower.c \
          sbs_memset.c sbs_bzero.c sbs_memcpy.c sbs_memccpy.c \
          sbs_memchr.c sbs_memcmp.c \
          sbs_calloc.c sbs_substr.c sbs_strjoin.c sbs_itoa.c sbs_strdup.c \
          sbs_strlen.c sbs_strlcpy.c sbs_strlcat.c \
          sbs_strnlen.c sbs_strncpy.c sbs_strncat.c sbs_strcmp.c \
          sbs_strchr.c sbs_strrchr.c sbs_strnstr.c \
          sbs_strncmp.c sbs_atoi.c

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

%.o: %.c libsbs.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
