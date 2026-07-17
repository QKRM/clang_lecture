# ============================================================
# libsbs 종합 프로젝트 Makefile (16차시 최종 — 미니셸)
#
#   make            → libsbs.a 만들기 (지금까지 만든 전체 함수 + split)
#   make minishell  → libsbs.a를 링크한 minishell 실행 파일
#   make clean      → 중간 파일(.o) 삭제
#   make fclean     → .o + libsbs.a + minishell 삭제
#   make re         → 전부 지우고 처음부터
# ============================================================

NAME      = libsbs.a
MINISHELL = minishell

CC        = cc
CFLAGS    = -Wall -Wextra -Werror
AR        = ar
ARFLAGS   = rcs
RM        = rm -f

# 라이브러리에 들어갈 소스 (minishell.c는 여기 넣지 않는다!)
SRCS      = sbs_isalpha.c sbs_isdigit.c sbs_isalnum.c sbs_isascii.c \
            sbs_isprint.c sbs_toupper.c sbs_tolower.c \
            sbs_memset.c sbs_bzero.c sbs_memcpy.c sbs_memccpy.c \
            sbs_memchr.c sbs_memcmp.c \
            sbs_calloc.c sbs_substr.c sbs_strjoin.c sbs_itoa.c sbs_strdup.c \
            sbs_strlen.c sbs_strlcpy.c sbs_strlcat.c \
            sbs_strnlen.c sbs_strncpy.c sbs_strncat.c sbs_strcmp.c \
            sbs_strcasecmp.c sbs_strncasecmp.c \
            sbs_strchr.c sbs_strrchr.c sbs_strnstr.c \
            sbs_strncmp.c sbs_atoi.c \
            sbs_split.c sbs_free_split.c

OBJS      = $(SRCS:.c=.o)

# 기본 타겟: 라이브러리 생성
all: $(NAME)

# .a 아카이브: 오브젝트들을 ar로 묶음
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

# 패턴 규칙: .c → .o (libsbs.h가 바뀌면 전부 다시 컴파일)
%.o: %.c libsbs.h
	$(CC) $(CFLAGS) -c $< -o $@

# 미니셸: libsbs.a를 링크. 의존성에 $(NAME)을 넣어 라이브러리부터 빌드
$(MINISHELL): minishell.o $(NAME)
	$(CC) $(CFLAGS) minishell.o -L. -lsbs -o $(MINISHELL)

# 오브젝트만 삭제 (minishell.o 포함)
clean:
	$(RM) $(OBJS) minishell.o

# 오브젝트 + 라이브러리 + 실행 파일 삭제
fclean: clean
	$(RM) $(NAME) $(MINISHELL)

# 전체 재빌드
re: fclean all

.PHONY: all clean fclean re
