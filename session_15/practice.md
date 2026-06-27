# 15차시 실습 - Makefile과 라이브러리 아카이브

## 실습 목표

- Makefile을 작성해 `libsbs.a`를 자동 빌드한다.
- `ar`로 정적 라이브러리를 만든다.
- `all / clean / fclean / re` 규칙을 구현한다.
- 라이브러리를 링크해 함수가 동작함을 확인한다.


> 이번 차시는 함수 구현이 아니라 **빌드 시스템**을 만듭니다. `.c` 파일은 제공됩니다(데모용 4개).

---

## 준비: 제공 파일

```
session_15/
├── libsbs.h
├── sbs_isalpha.c  sbs_toupper.c
├── sbs_strlen.c   sbs_strdup.c
├── Makefile          ← 직접 작성 (참고 정답 동봉)
├── grade.sh
└── tests/test_link.c
```

---

## 과제 1: 변수 정의

`Makefile`을 만들고 변수를 정의하세요.

요구사항:
```makefile
NAME    = libsbs.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
AR      = ar
ARFLAGS = rcs
RM      = rm -f

SRCS    = sbs_isalpha.c sbs_toupper.c sbs_strlen.c sbs_strdup.c
OBJS    = $(SRCS:.c=.o)
```

> `$(SRCS:.c=.o)`는 모든 `.c`를 `.o`로 바꾼 목록입니다.

---

## 과제 2: 라이브러리 빌드 규칙

요구사항:
- `all` 타겟이 `$(NAME)`을 만든다
- `$(NAME)`은 `$(OBJS)`를 `ar`로 묶는다
- 패턴 규칙으로 `.c`를 `.o`로 컴파일 (libsbs.h 의존)

힌트:
```makefile
all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

%.o: %.c libsbs.h
	$(CC) $(CFLAGS) -c $< -o $@
```

> 레시피 줄은 **반드시 탭(Tab)**으로 들여쓰기. 스페이스면 `missing separator` 에러.

---

## 과제 3: clean / fclean / re

요구사항:
```makefile
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

> `.PHONY`로 동명 파일과의 충돌을 막습니다(예: `clean`이라는 파일이 있어도 동작).

---

## 과제 4: 빌드 + 링크 확인

```bash
$ make                       # libsbs.a 생성
$ ar t libsbs.a              # 오브젝트 목록 확인
$ make clean                 # .o 삭제
$ make re                    # 전체 재빌드

# 라이브러리 링크 테스트
$ cc -Wall -Wextra -Werror tests/test_link.c -L. -lsbs -o run
$ ./run
LINK_OK
```

- `-L.` 현재 폴더에서 라이브러리 검색
- `-lsbs` → `libsbs.a` 링크 (`lib`/`.a` 뺀 이름)

---

## 과제 5: 채점

```bash
$ bash grade.sh
=== libsbs 15차시 채점 (Makefile) ===
✓ make → libsbs.a 생성
✓ ar 아카이브에 오브젝트 포함
✓ libsbs.a 링크 + 동작 확인
✓ clean / fclean / re 규칙 동작
결과: 4 / 4 통과
```

---

## 제출 확인 사항

- [ ] `Makefile` - 변수 정의 (NAME, CC, CFLAGS, AR, SRCS, OBJS)
- [ ] `all`, `$(NAME)`, 패턴 규칙
- [ ] `clean`, `fclean`, `re`, `.PHONY`
- [ ] 레시피가 탭으로 들여쓰기 되었는가?
- [ ] `make` → libsbs.a 생성, `-lsbs` 링크 동작
- [ ] `bash grade.sh` → 4 / 4 통과

---

## 더 생각해볼 거리

1. `make`가 바뀐 파일만 다시 컴파일하는 원리는? (타임스탬프 비교)
2. 정적 라이브러리(.a)와 동적 라이브러리(.so)의 차이는? (링크 시점)
3. `.PHONY`가 없으면 `clean`이라는 파일이 생겼을 때 무슨 일이? (규칙이 실행 안 됨)
