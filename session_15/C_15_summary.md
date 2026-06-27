# 15차시: Makefile과 라이브러리 아카이브

## 학습 목표

1. Makefile 문법(타겟·의존성·레시피)
2. 변수와 패턴 규칙
3. ar로 정적 라이브러리
4. libsbs.a 빌드 + 링크
5. all/clean/fclean/re 규칙

---

## 핵심 개념

### 1. Makefile 기본

```makefile
타겟: 의존성
	레시피      # 반드시 탭!
```

> 레시피 들여쓰기는 탭. 스페이스면 missing separator 에러.

---

### 2. 변수 + 치환

```makefile
NAME   = libsbs.a
CFLAGS = -Wall -Wextra -Werror
SRCS   = sbs_isalpha.c sbs_strlen.c ...
OBJS   = $(SRCS:.c=.o)    # .c → .o
```

---

### 3. 패턴 규칙 + 자동 변수

```makefile
%.o: %.c libsbs.h
	$(CC) $(CFLAGS) -c $< -o $@
```

| 변수 | 의미 |
|------|------|
| `$<` | 첫 의존성(.c) |
| `$@` | 타겟(.o) |

---

### 4. ar로 .a 생성

```makefile
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
```

| 플래그 | 의미 |
|--------|------|
| r | 추가/교체 |
| c | 생성 |
| s | 심볼 인덱스 |

확인: `ar t libsbs.a`

---

### 5. 표준 규칙

```makefile
all: $(NAME)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re
```

---

### 6. 링크

```bash
cc main.c -L. -lsbs -o program
```

> -L. 현재 폴더, -lsbs → libsbs.a (lib/.a 뺀 이름)

---

## 실행 전 체크리스트

- [ ] 레시피가 탭으로 들여쓰기 되었는가?
- [ ] OBJS = $(SRCS:.c=.o) 치환을 썼는가?
- [ ] ar rcs로 .a를 만드는가?
- [ ] .PHONY를 선언했는가?
- [ ] `bash grade.sh` → 4/4?

---

## 다음 차시 예고

- **16차시: libsbs 종합 프로젝트 + 코드 리뷰**
- 9~14차시 전체 함수 통합, 최종 Makefile, 상호 코드 리뷰

---

## 트러블슈팅

| 증상 | 확인 사항 |
|------|----------|
| missing separator | 레시피를 탭으로 |
| undefined reference | -lsbs 링크, ar에 .o 포함 |
| make가 아무것도 안 함 | all 타겟, 파일 이름 확인 |
| clean이 안 됨 | .PHONY 선언 |
| -lsbs 못 찾음 | -L. 추가, libsbs.a 이름 |
