# ============================================================
# libsbs 정적 라이브러리 Makefile (참고 정답)
# ============================================================

NAME    = libsbs.a

CC      = cc
CFLAGS  = -Wall -Wextra -Werror
AR      = ar
ARFLAGS = rcs
RM      = rm -f

SRCS    = sbs_isalpha.c \
          sbs_toupper.c \
          sbs_strlen.c \
          sbs_strdup.c

OBJS    = $(SRCS:.c=.o)

# 기본 타겟: 라이브러리 생성
all: $(NAME)

# .a 아카이브: 오브젝트들을 ar로 묶음
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

# 패턴 규칙: .c → .o (libsbs.h 의존)
%.o: %.c libsbs.h
	$(CC) $(CFLAGS) -c $< -o $@

# 오브젝트만 삭제
clean:
	$(RM) $(OBJS)

# 오브젝트 + 라이브러리 삭제
fclean: clean
	$(RM) $(NAME)

# 전체 재빌드
re: fclean all

.PHONY: all clean fclean re
