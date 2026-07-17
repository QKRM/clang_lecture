# ============================================================
# libsbs 정적 라이브러리 + 활용 프로그램 Makefile (참고 정답)
#
#   make            → libsbs.a 만들기
#   make progs      → libsbs.a를 링크한 wordinfo / minishell 만들기
#   make clean      → 중간 파일(.o) 삭제
#   make fclean     → .o + 라이브러리 + 실행 파일 삭제
#   make re         → 전부 지우고 처음부터 다시
# ============================================================

NAME      = libsbs.a
WORDINFO  = wordinfo
MINISHELL = minishell

CC        = cc
CFLAGS    = -Wall -Wextra -Werror
AR        = ar
ARFLAGS   = rcs
RM        = rm -f

# 라이브러리에 들어갈 소스 (프로그램의 main.c는 여기 넣지 않는다!)
SRCS      = sbs_isalpha.c \
            sbs_toupper.c \
            sbs_strlen.c \
            sbs_strdup.c \
            sbs_strcmp.c

OBJS      = $(SRCS:.c=.o)

# 기본 타겟: 라이브러리 생성
all: $(NAME)

# .a 아카이브: 오브젝트들을 ar로 묶음
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

# 패턴 규칙: .c → .o (libsbs.h가 바뀌면 전부 다시 컴파일)
%.o: %.c libsbs.h
	$(CC) $(CFLAGS) -c $< -o $@

# ---- libsbs.a를 링크하는 프로그램들 ----
# 의존성에 $(NAME)을 넣어야 라이브러리가 먼저 만들어진다.
$(WORDINFO): main.o $(NAME)
	$(CC) $(CFLAGS) main.o -L. -lsbs -o $(WORDINFO)

$(MINISHELL): minishell.o $(NAME)
	$(CC) $(CFLAGS) minishell.o -L. -lsbs -o $(MINISHELL)

# 프로그램 둘 다 빌드
progs: $(WORDINFO) $(MINISHELL)

# 오브젝트만 삭제
clean:
	$(RM) $(OBJS) main.o minishell.o

# 오브젝트 + 라이브러리 + 실행 파일 삭제
fclean: clean
	$(RM) $(NAME) $(WORDINFO) $(MINISHELL)

# 전체 재빌드
re: fclean all

.PHONY: all progs clean fclean re
