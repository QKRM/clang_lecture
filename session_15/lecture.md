# 15차시 강의 노트 - Makefile과 라이브러리 아카이브

## 학습 목표

1. Makefile의 기본 문법(타겟·의존성·레시피)을 이해한다.
2. 변수와 패턴 규칙으로 중복을 줄일 수 있다.
3. `ar`로 정적 라이브러리(`.a`)를 만들 수 있다.
4. `libsbs.a`를 빌드하고 다른 프로그램에 링크할 수 있다.
5. `all / clean / fclean / re` 표준 규칙을 작성할 수 있다.

---

## 1부: Makefile이 필요한 이유

지금까지 함수마다 `gcc ...`를 손으로 쳤습니다. 파일이 23개가 되면 매번 모두 컴파일하는 것은 비효율적입니다. **Makefile**은 빌드 규칙을 적어두고 `make` 한 번으로 자동 빌드합니다. 바뀐 파일만 다시 컴파일합니다.

```bash
$ make          # 빌드
$ make clean    # 중간 파일 정리
```

---

## 2부: Makefile 기본 문법

### 2.1 타겟 · 의존성 · 레시피

```makefile
타겟: 의존성
	레시피     # ← 반드시 탭(Tab)으로 들여쓰기!
```

- **타겟**: 만들려는 것(파일명 또는 동작 이름)
- **의존성**: 타겟을 만드는 데 필요한 것
- **레시피**: 실행할 명령 (앞에 **탭** 필수, 스페이스 아님)

```makefile
hello: hello.c
	cc -Wall -Wextra -Werror hello.c -o hello
```

> 레시피 들여쓰기는 **반드시 탭**입니다. 스페이스면 `missing separator` 에러.

### 2.2 변수

반복을 줄입니다.

```makefile
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
NAME    = libsbs.a

SRCS    = sbs_isalpha.c sbs_toupper.c sbs_strlen.c sbs_strdup.c
OBJS    = $(SRCS:.c=.o)      # .c를 .o로 치환
```

`$(SRCS:.c=.o)`는 "SRCS의 모든 `.c`를 `.o`로 바꾼 목록"입니다.

### 2.3 패턴 규칙과 자동 변수

```makefile
%.o: %.c libsbs.h
	$(CC) $(CFLAGS) -c $< -o $@
```

- `%.o: %.c` — 모든 `.o`는 같은 이름 `.c`로 만든다
- `$<` — 첫 번째 의존성(여기선 `.c`)
- `$@` — 타겟 이름(여기선 `.o`)

---

## 3부: ar로 정적 라이브러리 만들기

### 3.1 정적 라이브러리란?

여러 `.o`(오브젝트 파일)를 하나의 **아카이브** `.a`로 묶은 것입니다. 다른 프로그램이 이 라이브러리를 링크해 함수를 씁니다.

### 3.2 ar 명령

```bash
$ ar rcs libsbs.a sbs_isalpha.o sbs_toupper.o ...
```

| 플래그 | 의미 |
|--------|------|
| `r` | 아카이브에 추가(있으면 교체) |
| `c` | 아카이브 새로 생성 |
| `s` | 인덱스(심볼 테이블) 생성 — 링크 속도 |

Makefile에서:

```makefile
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)   # ar rcs libsbs.a *.o
```

### 3.3 아카이브 확인

```bash
$ ar t libsbs.a       # 들어있는 오브젝트 목록
sbs_isalpha.o
sbs_toupper.o
...
```

---

## 4부: 표준 규칙 + 링크

### 4.1 all / clean / fclean / re

42 계열과 많은 C 프로젝트가 쓰는 관례 규칙입니다.

```makefile
all: $(NAME)              # 기본 빌드

clean:
	$(RM) $(OBJS)         # .o만 삭제

fclean: clean
	$(RM) $(NAME)         # .o + .a 삭제

re: fclean all           # 전체 재빌드

.PHONY: all clean fclean re   # 동명 파일과 충돌 방지
```

> `.PHONY`는 "이 타겟은 파일이 아니라 동작"이라고 알려, `clean`이라는 파일이 있어도 항상 실행되게 합니다.

### 4.2 라이브러리 링크

```bash
# libsbs.a를 링크해 프로그램 빌드
$ cc -Wall -Wextra -Werror main.c -L. -lsbs -o program
```

- `-L.` — 현재 디렉토리에서 라이브러리를 찾음
- `-lsbs` — `libsbs.a`를 링크 (`lib`와 `.a`를 뺀 이름)

---

## 5부: 채점

채점 스크립트가 다음을 확인합니다:

```bash
$ bash grade.sh
=== libsbs 15차시 채점 (Makefile) ===
✓ make → libsbs.a 생성
✓ ar 아카이브에 오브젝트 포함
✓ libsbs.a 링크 + 동작 확인
✓ clean / fclean / re 규칙 동작
결과: 4 / 4 통과
```

1. `make`로 `libsbs.a`가 생기는가
2. 아카이브에 `.o`가 들어있는가
3. 링크해서 함수가 동작하는가(`-lsbs`)
4. `clean`/`fclean`/`re`가 제대로 동작하는가

---

## 핵심 정리

1. Makefile: 타겟·의존성·레시피, 레시피는 **탭** 들여쓰기
2. 변수와 `$(SRCS:.c=.o)`로 중복 제거
3. 패턴 규칙 `%.o: %.c`, 자동 변수 `$<`(소스) `$@`(타겟)
4. `ar rcs libsbs.a *.o`로 정적 라이브러리 생성
5. `all/clean/fclean/re` + `.PHONY` 표준 규칙
6. `-L. -lsbs`로 라이브러리 링크

---

## 다음 차시 예고

16차시는 종합 프로젝트입니다. 9~14차시에서 만든 모든 함수를 하나의 `libsbs`로 통합하고, 전체를 빌드하는 Makefile을 완성합니다. 동료와 코드 리뷰를 하고 최종 빌드를 확인합니다.
