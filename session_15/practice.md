# 15차시 실습 - Makefile과 라이브러리 아카이브

## 실습 목표

- Makefile을 작성해 `libsbs.a`를 자동 빌드한다.
- `ar`로 정적 라이브러리를 만든다.
- `all / clean / fclean / re` 규칙을 구현한다.
- 라이브러리를 링크해 **직접 쓰는 프로그램**(wordinfo)을 빌드한다.
- 16차시에 완성할 **미니셸의 껍데기**를 빌드해 돌려본다.


> 이번 차시는 함수 구현이 아니라 **빌드 시스템**을 만듭니다. `.c` 파일은 전부 제공됩니다. 여러분이 쓸 것은 **Makefile 하나**입니다.

---

## 준비: 실습 파일 내려받기

페이지 맨 위의 **실습 파일 내려받기** 버튼으로 `session_15_starter.zip`을 받으세요. Makefile을 만드는 데 필요한 모든 파일이 들어 있습니다(**Makefile만 빠져 있습니다 — 그게 오늘 과제**).

```
session_15_starter/
├── libsbs.h              헤더 (함수 5개 프로토타입)
├── sbs_isalpha.c         ┐
├── sbs_toupper.c         │
├── sbs_strlen.c          ├─ 라이브러리에 들어갈 소스 (SRCS)
├── sbs_strdup.c          │
├── sbs_strcmp.c          ┘
├── main.c                wordinfo 프로그램 (libsbs 활용)
├── minishell.c           미니셸 껍데기 (16차시 예고)
├── tests/test_link.c     링크 테스트
├── grade.sh              채점 스크립트
└── README.md             과제 요약
```

Codespaces에 올리는 법:

```bash
$ unzip session_15_starter.zip
$ cd session_15_starter
$ ls
```

> Makefile 정답은 이 페이지 맨 아래 **정답 코드**에 있습니다. 먼저 직접 써본 뒤에 여세요.

---

## 과제 1: 변수 정의

`Makefile`을 새로 만들고 변수부터 정의하세요.

요구사항:
```makefile
NAME      = libsbs.a
WORDINFO  = wordinfo
MINISHELL = minishell

CC        = cc
CFLAGS    = -Wall -Wextra -Werror
AR        = ar
ARFLAGS   = rcs
RM        = rm -f

SRCS      = sbs_isalpha.c sbs_toupper.c sbs_strlen.c sbs_strdup.c sbs_strcmp.c
OBJS      = $(SRCS:.c=.o)
```

> **주의**: `SRCS`에 `main.c`나 `minishell.c`를 넣지 마세요. 라이브러리는 부품 모음이라 `main`이 들어가면 안 됩니다.

---

## 과제 2: 라이브러리 빌드 규칙

요구사항:
- `all` 타겟이 `$(NAME)`을 만든다 (맨 위에 둘 것)
- `$(NAME)`은 `$(OBJS)`를 `ar`로 묶는다
- 패턴 규칙으로 `.c`를 `.o`로 컴파일 (`libsbs.h` 의존)

힌트:
```makefile
all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

%.o: %.c libsbs.h
	$(CC) $(CFLAGS) -c $< -o $@
```

> 레시피 줄은 **반드시 탭(Tab)**으로 들여쓰기. 스페이스면 `missing separator` 에러.

확인:
```bash
$ make
$ ar t libsbs.a        # 5개 .o가 보여야 함
```

---

## 과제 3: clean / fclean / re

요구사항:
```makefile
clean:
	$(RM) $(OBJS) main.o minishell.o

fclean: clean
	$(RM) $(NAME) $(WORDINFO) $(MINISHELL)

re: fclean all

.PHONY: all progs clean fclean re
```

> `clean`은 프로그램의 `.o`(main.o, minishell.o)도 지워야 합니다. `fclean`은 실행 파일까지.

확인:
```bash
$ make clean       # .o 사라짐, libsbs.a는 남음
$ make fclean      # 전부 사라짐
$ make re          # 처음부터 다시 빌드
```

---

## 과제 4: wordinfo — libsbs를 쓰는 프로그램

`main.c`(제공)를 `libsbs.a`와 링크하는 규칙을 추가하세요.

요구사항:
- 타겟 이름은 `$(WORDINFO)`
- 의존성에 `main.o`와 **`$(NAME)`** 둘 다 (라이브러리가 먼저 있어야 하니까)
- `-L. -lsbs`로 링크

힌트:
```makefile
$(WORDINFO): main.o $(NAME)
	$(CC) $(CFLAGS) main.o -L. -lsbs -o $(WORDINFO)
```

확인:
```bash
$ make wordinfo
$ ./wordinfo hello C99
[hello]
  길이   : 5
  대문자 : HELLO
  알파벳 : 예
[C99]
  길이   : 3
  대문자 : C99
  알파벳 : 아니오
```

> `-lsbs`를 `main.o` **앞에** 쓰면 `undefined reference` 에러가 납니다. 링커는 왼쪽→오른쪽으로 읽습니다.

---

## 과제 5: minishell — 셸 껍데기 빌드

`minishell.c`(제공)도 같은 방식으로 링크하세요.

힌트:
```makefile
$(MINISHELL): minishell.o $(NAME)
	$(CC) $(CFLAGS) minishell.o -L. -lsbs -o $(MINISHELL)

progs: $(WORDINFO) $(MINISHELL)
```

확인:
```
$ make minishell
$ ./minishell
minishell$ hello
입력: hello
minishell$ 안녕 세계
입력: 안녕 세계
minishell$ exit
bye
$
```

Ctrl+D로도 종료되는지 확인하세요.

```bash
$ make progs       # wordinfo + minishell 한 번에
```

---

## 과제 6: 코드 읽기 — minishell.c 분석

`minishell.c`를 열어 다음 질문에 답해보세요. (코드를 고칠 필요는 없습니다)

1. `strip_newline`은 왜 필요한가? 그 호출을 지우고 빌드해서 `exit`를 쳐보세요. 무슨 일이 일어나나요?
2. `sbs_strcmp(line, "exit")` 대신 `line == "exit"`로 쓰면 왜 안 되나요?
3. `fgets`가 `NULL`을 반환하는 경우는 언제인가요? 그때 `break`를 안 하면?
4. `while (1)`이 무한 루프인데 왜 버그가 아닌가요?

> 답은 강의 노트 6부에 있습니다. 직접 실험해보면 더 오래 남습니다.

---

## 과제 7: 채점

```bash
$ bash grade.sh
=== libsbs 15차시 채점 (Makefile) ===
✓ make → libsbs.a 생성
✓ ar 아카이브에 오브젝트 포함
✓ libsbs.a 링크 + 동작 확인
✓ clean / fclean / re 규칙 동작
✓ make wordinfo — libsbs 활용 프로그램 동작
✓ make minishell — 프롬프트/입력/exit 동작
결과: 6 / 6 통과
```

실패 시 `bash grade.sh -v`로 상세 로그를 확인하세요.

---

## 제출 확인 사항

- [ ] `Makefile` - 변수 정의 (NAME, CC, CFLAGS, AR, SRCS, OBJS)
- [ ] `all`, `$(NAME)`, 패턴 규칙 `%.o: %.c libsbs.h`
- [ ] `clean`, `fclean`, `re`, `.PHONY`
- [ ] 레시피가 **탭**으로 들여쓰기 되었는가?
- [ ] `SRCS`에 `main.c` / `minishell.c`가 **안** 들어갔는가?
- [ ] `make wordinfo` → `./wordinfo hello` 동작
- [ ] `make minishell` → 프롬프트/입력/`exit` 동작
- [ ] `bash grade.sh` → 6 / 6 통과

---

## 더 생각해볼 거리

1. `make`가 바뀐 파일만 다시 컴파일하는 원리는? (타임스탬프 비교)
2. 정적 라이브러리(.a)와 동적 라이브러리(.so)의 차이는? (링크 시점 — .a는 실행 파일 안에 복사되어 박히고, .so는 실행할 때 따로 불러옴)
3. `.PHONY`가 없으면 `clean`이라는 파일이 생겼을 때 무슨 일이? (규칙이 실행 안 됨)
4. `main.c`를 `SRCS`에 넣으면 어떤 문제가 생길까? (libsbs.a에 main이 박혀서 다른 프로그램과 충돌)
5. `minishell$ echo hello`를 치면 지금은 `입력: echo hello`가 나옵니다. 진짜 `hello`만 출력하려면 뭐가 더 필요할까요? (16차시 — 단어 쪼개기 + 명령 구현)
