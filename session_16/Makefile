# ============================================================
# libsbs 종합 프로젝트 Makefile (16차시 최종 — 미니셸)
#
#   폴더 구조:
#     src/   libsbs 소스(sbs_*.c) 전부
#     obj/   컴파일 결과(.o) — make가 자동 생성
#     ./     libsbs.h, minishell.c, Makefile
#
#   make            → libsbs.a 만들기 (src/의 전체 함수 + split)
#   make minishell  → libsbs.a를 링크한 minishell 실행 파일
#   make clean      → obj/ 삭제
#   make fclean     → obj/ + libsbs.a + minishell 삭제
#   make re         → 전부 지우고 처음부터
# ============================================================

NAME      = libsbs.a
MINISHELL = minishell

CC        = cc
CFLAGS    = -Wall -Wextra -Werror
AR        = ar
ARFLAGS   = rcs
RM        = rm -f

SRC_DIR   = src
OBJ_DIR   = obj

# 라이브러리에 들어갈 함수 이름(확장자 없이). minishell은 여기 넣지 않는다!
NAMES     = sbs_isalpha sbs_isdigit sbs_isalnum sbs_isascii \
            sbs_isprint sbs_toupper sbs_tolower \
            sbs_memset sbs_bzero sbs_memcpy sbs_memccpy \
            sbs_memchr sbs_memcmp \
            sbs_calloc sbs_substr sbs_strjoin sbs_itoa sbs_strdup \
            sbs_strlen sbs_strlcpy sbs_strlcat \
            sbs_strnlen sbs_strncpy sbs_strncat sbs_strcmp \
            sbs_strcasecmp sbs_strncasecmp \
            sbs_strchr sbs_strrchr sbs_strnstr \
            sbs_strncmp sbs_atoi \
            sbs_split sbs_free_split

SRCS      = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(NAMES)))
OBJS      = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(NAMES)))

# 기본 타겟: 라이브러리 생성
all: $(NAME)

# .a 아카이브: obj/의 오브젝트들을 ar로 묶음
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

# 패턴 규칙: src/%.c → obj/%.o  (obj/가 없으면 먼저 만든다: | $(OBJ_DIR))
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c libsbs.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I. -c $< -o $@

# obj/ 디렉토리 생성 (order-only 의존성)
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# 미니셸: libsbs.a를 링크. minishell.o도 obj/에 만든다.
$(MINISHELL): $(OBJ_DIR)/minishell.o $(NAME)
	$(CC) $(CFLAGS) $(OBJ_DIR)/minishell.o -L. -lsbs -o $(MINISHELL)

$(OBJ_DIR)/minishell.o: minishell.c libsbs.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I. -c minishell.c -o $@

# obj/ 통째로 삭제 (RM = rm -f 이므로 -r 붙여 폴더까지)
clean:
	$(RM) -r $(OBJ_DIR)

# obj/ + 라이브러리 + 실행 파일 삭제
fclean: clean
	$(RM) $(NAME) $(MINISHELL)

# 전체 재빌드
re: fclean all

.PHONY: all clean fclean re
