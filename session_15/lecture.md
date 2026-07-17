# 15차시 강의 노트 - Makefile과 라이브러리 아카이브

## 학습 목표

1. Makefile이 무엇을 대신해주는지 한 문장으로 설명한다.
2. Makefile의 기본 문법(타겟·의존성·레시피)을 이해한다.
3. 변수와 패턴 규칙으로 중복을 줄인다.
4. `ar`로 정적 라이브러리(`libsbs.a`)를 만든다.
5. `all / clean / fclean / re` 표준 규칙을 작성한다.
6. `libsbs.a`를 **링크해서 쓰는 프로그램**을 직접 만든다.
7. 16차시에 만들 **미니셸**의 뼈대(REPL 루프)를 이해한다.

---

## 0부: 들어가며 — Makefile이 대체 뭔데?

### 한 문장 요약

> **Makefile은 "이 프로그램은 이렇게 만든다"를 적어둔 조립 설명서다.**
> 설명서를 한 번 써두면, 그 다음부터는 `make` 한 단어로 빌드가 끝난다.

### 지금까지 우리가 하던 일

9차시부터 컴파일할 때마다 이렇게 쳤습니다.

```bash
$ cc -Wall -Wextra -Werror sbs_strlen.c sbs_strlcpy.c sbs_strlcat.c tests/test_strlen.c -o run
```

함수가 4개일 땐 참을 만합니다. 그런데 16차시에는 함수가 **30개가 넘습니다.** 매번 30개 파일 이름을 손으로 칠 건가요? 오타 하나 나면 또 처음부터.

### Makefile이 해결하는 3가지

**① 긴 명령어를 이름 하나로 줄인다**

```bash
$ make          # 위의 그 긴 cc 명령을 대신 실행
```

**② 바뀐 파일만 다시 컴파일한다 (이게 진짜 핵심)**

`make`는 파일의 **수정 시각(타임스탬프)** 을 봅니다.

```
sbs_strlen.c  (오후 3시 수정)  →  sbs_strlen.o  (오후 2시 생성)
                                   ↑ 소스가 더 최신! 다시 컴파일해야 함

sbs_strdup.c  (오전 9시 수정)  →  sbs_strdup.o  (오후 2시 생성)
                                   ↑ .o가 더 최신. 건너뛴다
```

30개 파일 중 1개만 고쳤으면 **1개만** 다시 컴파일합니다. 프로젝트가 커질수록 이 차이가 몇 초 vs 몇 분이 됩니다.

**③ 팀원 누구나 똑같이 빌드한다**

"이거 어떻게 빌드해요?" → "`make` 치세요." 끝. 컴파일 옵션(`-Wall -Wextra -Werror`)을 빠뜨리는 사람도 없어집니다.

### 오늘 만들 것

```
sbs_*.c  ──(make)──▶  libsbs.a  ──(링크)──▶  wordinfo   (libsbs 활용 프로그램)
                                    └──────▶  minishell  (16차시 셸의 껍데기)
```

즉 오늘은 **① 라이브러리를 만들고 ② 그걸 실제로 갖다 쓰는 것**까지 합니다. 지금까지 만든 함수들이 처음으로 "진짜 프로그램"이 되는 날입니다.

---

## 1부: Makefile 기본 문법

### 1.1 규칙 하나의 생김새

Makefile은 **규칙(rule)** 의 모음입니다. 규칙 하나는 세 부분입니다.

```makefile
타겟: 의존성
	레시피     # ← 반드시 탭(Tab)으로 들여쓰기!
```

- **타겟(target)**: 만들려는 것. 보통 파일 이름
- **의존성(prerequisites)**: 타겟을 만드는 데 필요한 재료
- **레시피(recipe)**: 실제로 실행할 셸 명령

읽는 법: *"타겟은 의존성으로 만든다. 만드는 방법은 레시피다."*

```makefile
hello: hello.c
	cc -Wall -Wextra -Werror hello.c -o hello
```

> "hello라는 파일은 hello.c로 만든다. 만드는 법은 이 cc 명령이다."

### 1.2 탭 함정 (제일 많이 걸림)

레시피 줄은 **반드시 탭 문자**로 시작해야 합니다. 스페이스 4칸은 안 됩니다. 눈으로는 똑같아 보이는데 make는 거부합니다.

```
Makefile:3: *** missing separator.  Stop.
```

이 에러가 뜨면 99% 탭 문제입니다. VS Code에서 Makefile을 열면 자동으로 탭을 쓰지만, 복사·붙여넣기 하면 스페이스로 바뀔 수 있으니 주의하세요.

### 1.3 make는 어떻게 판단하나

```bash
$ make hello
```

1. `hello` 파일이 있나? 없으면 → 레시피 실행
2. 있으면 → `hello.c`가 `hello`보다 최신인가?
   - 최신이면(소스를 고쳤으면) → 레시피 실행
   - 아니면 → `make: 'hello' is up to date.` 하고 아무것도 안 함

이 타임스탬프 비교가 앞에서 말한 "바뀐 것만 다시 만들기"의 정체입니다.

---

## 2부: 변수와 패턴 규칙

### 2.1 변수 — 반복 줄이기

```makefile
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
NAME    = libsbs.a

SRCS    = sbs_isalpha.c sbs_toupper.c sbs_strlen.c sbs_strdup.c sbs_strcmp.c
OBJS    = $(SRCS:.c=.o)
```

- 정의: `이름 = 값`
- 사용: `$(이름)`

`$(SRCS:.c=.o)`는 **치환 참조**입니다. "SRCS의 모든 `.c`를 `.o`로 바꾼 목록"이 됩니다.

```
SRCS = sbs_isalpha.c sbs_toupper.c ...
OBJS = sbs_isalpha.o sbs_toupper.o ...      ← 자동으로 이렇게 됨
```

파일이 늘어나면 **SRCS 한 줄만** 고치면 됩니다. OBJS는 따라옵니다.

### 2.2 패턴 규칙 — 규칙 하나로 전부 처리

파일마다 규칙을 쓰면 이렇게 됩니다.

```makefile
sbs_isalpha.o: sbs_isalpha.c
	cc -Wall -Wextra -Werror -c sbs_isalpha.c -o sbs_isalpha.o
sbs_toupper.o: sbs_toupper.c
	cc -Wall -Wextra -Werror -c sbs_toupper.c -o sbs_toupper.o
```

30개면 30번 반복입니다. 패턴 규칙 하나로 끝냅니다.

```makefile
%.o: %.c libsbs.h
	$(CC) $(CFLAGS) -c $< -o $@
```

- `%` — 와일드카드. "모든 `.o`는 같은 이름의 `.c`로 만든다"
- `libsbs.h`를 의존성에 넣은 이유: **헤더를 고치면 전부 다시 컴파일**해야 하니까

### 2.3 자동 변수

레시피 안에서 쓰는 특수 변수입니다.

| 변수 | 의미 | 위 예시에서 |
|------|------|------------|
| `$<` | 첫 번째 의존성 | `sbs_strlen.c` |
| `$@` | 타겟 이름 | `sbs_strlen.o` |
| `$^` | 의존성 전부 | `sbs_strlen.c libsbs.h` |

> `-c` 옵션은 "컴파일만 하고 링크는 하지 마라"는 뜻입니다. 그래야 `.o`(오브젝트 파일)가 나오고, 나중에 `ar`로 묶을 수 있습니다.

---

## 3부: ar로 정적 라이브러리 만들기

### 3.1 정적 라이브러리란?

여러 `.o`를 하나로 묶은 **압축 파일 같은 것**입니다. 확장자는 `.a`(archive).

```
sbs_isalpha.o ┐
sbs_toupper.o ├──(ar)──▶  libsbs.a
sbs_strlen.o  ┘
```

왜 묶나요? 프로그램을 빌드할 때 `.o` 30개를 일일이 나열하는 대신 `-lsbs` 한 마디로 끝나기 때문입니다. 남에게 코드를 안 주고 기능만 줄 수도 있습니다.

### 3.2 ar 명령

```bash
$ ar rcs libsbs.a sbs_isalpha.o sbs_toupper.o sbs_strlen.o
```

| 플래그 | 의미 |
|--------|------|
| `r` | 아카이브에 추가(이미 있으면 교체) |
| `c` | 아카이브가 없으면 새로 생성 |
| `s` | 심볼 인덱스 생성 — 링커가 함수를 빨리 찾게 해줌 |

Makefile에서:

```makefile
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)   # ar rcs libsbs.a sbs_*.o
```

### 3.3 이름 규칙 (중요)

라이브러리 이름은 반드시 **`lib` + 이름 + `.a`** 형태여야 합니다.

```
libsbs.a   →  링크할 때 -lsbs     (lib와 .a를 뗀 이름)
```

`sbs.a`로 만들면 `-lsbs`로 못 찾습니다. 이건 관례가 아니라 링커의 규칙입니다.

### 3.4 아카이브 확인

```bash
$ ar t libsbs.a       # t = table, 들어있는 목록 보기
sbs_isalpha.o
sbs_toupper.o
sbs_strlen.o
sbs_strdup.o
sbs_strcmp.o
```

빠진 게 있으면 SRCS를 확인하세요.

---

## 4부: 표준 규칙 + 링크

### 4.1 all / clean / fclean / re

C 프로젝트에서 널리 쓰는 관례 규칙 4개입니다.

```makefile
all: $(NAME)              # 기본 빌드

clean:
	$(RM) $(OBJS)         # 중간 파일(.o)만 삭제

fclean: clean
	$(RM) $(NAME)         # .o + 결과물까지 삭제

re: fclean all            # 전부 지우고 처음부터

.PHONY: all clean fclean re
```

- `make`만 치면 **맨 위 타겟**이 실행됩니다. 그래서 `all`을 맨 위에 둡니다.
- `fclean: clean` — fclean은 clean을 의존성으로 가집니다. clean을 먼저 하고 나서 자기 레시피를 실행합니다.
- `re: fclean all` — 레시피 없이 의존성만 있습니다. "fclean 하고 all 해라"는 뜻.

### 4.2 .PHONY가 필요한 이유

`clean`은 파일 이름이 아니라 **동작 이름**입니다. 그런데 만약 폴더에 `clean`이라는 **파일**이 실수로 생기면?

make는 "clean이라는 타겟(=파일)이 이미 있고, 의존성도 없으니 만들 필요 없네" 하고 **아무것도 안 합니다.**

```bash
$ touch clean       # clean이라는 파일 생성
$ make clean
make: 'clean' is up to date.     # ← .o가 안 지워짐!
```

`.PHONY: clean`이라고 선언하면 "이건 파일이 아니라 동작"이라고 알려줘서 항상 실행됩니다.

### 4.3 라이브러리 링크

```bash
$ cc -Wall -Wextra -Werror main.c -L. -lsbs -o wordinfo
```

| 옵션 | 의미 |
|------|------|
| `-L.` | 라이브러리를 **현재 폴더(`.`)** 에서 찾아라 |
| `-lsbs` | `libsbs.a`를 링크해라 (`lib`/`.a` 뗀 이름) |

> **순서 주의**: `-lsbs`는 `main.c` **뒤에** 와야 합니다. 링커는 왼쪽에서 오른쪽으로 읽으면서 "아직 못 찾은 함수"를 모으기 때문에, 라이브러리가 먼저 나오면 아직 찾을 게 없어서 그냥 지나칩니다. `cc -lsbs main.c`는 `undefined reference` 에러가 납니다.

---

## 5부: libsbs를 실제로 써보기 — wordinfo

라이브러리를 만들었으면 **써봐야** 의미가 있습니다. 우리가 만든 함수만으로 동작하는 작은 프로그램을 만듭니다.

### 5.1 무엇을 만드나

```bash
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

명령줄 인자로 받은 단어마다 길이·대문자·알파벳 여부를 출력합니다. 쓰는 함수는 전부 `sbs_` 버전입니다.

### 5.2 코드

```c
#include <stdio.h>
#include <stdlib.h>
#include "libsbs.h"

static void print_upper(const char *s)
{
    int i = 0;
    while (s[i])
    {
        printf("%c", sbs_toupper((unsigned char)s[i]));
        i++;
    }
}

int main(int argc, char **argv)
{
    int   i;
    char  *copy;

    if (argc < 2)
    {
        printf("사용법: ./wordinfo 단어 [단어...]\n");
        return (1);
    }
    i = 1;
    while (i < argc)
    {
        copy = sbs_strdup(argv[i]);     /* 11차시 strdup */
        if (copy == NULL)
            return (1);
        printf("[%s]\n", copy);
        printf("  길이   : %zu\n", sbs_strlen(copy));   /* 12차시 */
        printf("  대문자 : ");
        print_upper(copy);                              /* 9차시 toupper */
        printf("\n");
        free(copy);                     /* strdup은 malloc → free 필수 */
        i++;
    }
    return (0);
}
```

### 5.3 여기서 짚을 점

**① `main.c`는 라이브러리에 넣지 않는다**

```makefile
SRCS = sbs_isalpha.c sbs_toupper.c ...    # main.c 없음!
```

라이브러리는 **부품 모음**입니다. `main`은 프로그램의 시작점이라 부품이 아닙니다. 라이브러리에 `main`이 들어 있으면 나중에 그 라이브러리를 쓰는 다른 프로그램과 `main`이 충돌합니다.

**② `%zu`로 size_t 출력**

`sbs_strlen`은 `size_t`를 반환합니다. `%d`로 찍으면 `-Wall`에서 경고(→ `-Werror` 때문에 에러)가 납니다. `size_t`는 `%zu`입니다.

**③ Makefile에 프로그램 타겟 추가**

```makefile
$(WORDINFO): main.o $(NAME)
	$(CC) $(CFLAGS) main.o -L. -lsbs -o $(WORDINFO)
```

의존성에 `$(NAME)`을 넣은 게 핵심입니다. "wordinfo를 만들려면 libsbs.a가 먼저 있어야 한다"고 알려주면, make가 알아서 라이브러리부터 만듭니다.

---

## 6부: 16차시 예고 — 미니셸의 뼈대

16차시에는 **셸(shell)** 을 직접 만듭니다. 오늘은 그 **껍데기**까지만 만들어 둡니다.

### 6.1 셸이란 무엇인가

여러분이 매일 쓰는 그것입니다.

```bash
$ ls
$ cd session_15
$ make
```

`$`를 찍고 기다리다가, 여러분이 명령을 치면, 그걸 해석해서 실행하고, 다시 `$`를 찍는 프로그램. bash, zsh 모두 셸입니다. **터미널 창 자체가 아니라, 그 안에서 도는 프로그램**입니다.

### 6.2 셸의 심장 — REPL 루프

셸이 하는 일은 놀랍도록 단순한 4단계 반복입니다.

```
    ┌──────────────────────────────┐
    │  1. 프롬프트 출력 ($ 찍기)     │
    │  2. 한 줄 읽기   (Read)       │
    │  3. 해석·실행    (Eval)       │
    │  4. 결과 출력    (Print)      │
    └──────────┬───────────────────┘
               │
               └──▶ 1번으로 (Loop)
```

이걸 **REPL**(Read-Eval-Print Loop)이라 부릅니다. 파이썬 대화형 셸, 브라우저 콘솔, 다 같은 구조입니다.

### 6.3 오늘 만들 부분 / 16차시에 만들 부분

| 단계 | 오늘(15차시) | 16차시 |
|------|-------------|--------|
| 1. 프롬프트 | ✅ `minishell$ ` 출력 | 그대로 |
| 2. 읽기 | ✅ `fgets`로 한 줄 | 그대로 |
| 3. 해석 | ❌ 그냥 되돌려 출력 | **단어로 쪼개기(split)** |
| 3. 실행 | ❌ 없음 | **echo/pwd/help 등 명령 구현** |
| 4. 반복 | ✅ `exit` 치면 종료 | 그대로 |

즉 오늘은 **루프와 입출력**이라는 뼈대를 세우고, 16차시에 **알맹이(명령 해석기)** 를 끼워 넣습니다.

### 6.4 껍데기 코드

```c
#include <stdio.h>
#include <stdlib.h>
#include "libsbs.h"

#define BUF_SIZE 1024

/* fgets는 Enter(\n)까지 담아온다. 그대로 두면 "exit\n" != "exit". */
static void strip_newline(char *line)
{
    size_t len = sbs_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
}

int main(void)
{
    char line[BUF_SIZE];

    while (1)
    {
        printf("minishell$ ");                      /* 1. 프롬프트 */
        if (fgets(line, BUF_SIZE, stdin) == NULL)   /* 2. 읽기 */
        {
            printf("\n");
            break ;                                 /* Ctrl+D = 입력 끝 */
        }
        strip_newline(line);
        if (sbs_strcmp(line, "exit") == 0)          /* 3. 해석(아주 초보적) */
            break ;
        if (sbs_strcmp(line, "") == 0)
            continue ;                              /* 그냥 Enter면 무시 */
        printf("입력: %s\n", line);                 /* 4. 출력 */
    }
    printf("bye\n");
    return (0);
}
```

실행하면:

```
$ ./minishell
minishell$ hello
입력: hello
minishell$ 
minishell$ exit
bye
$
```

### 6.5 여기서 libsbs가 실제로 일한다

껍데기밖에 없는데도 우리 함수 2개가 이미 쓰이고 있습니다.

- **`sbs_strlen`** → 줄 끝의 `\n` 위치를 찾으려면 길이를 알아야 함
- **`sbs_strcmp`** → 입력이 정확히 `"exit"`인지 판정. **C에서 문자열 비교는 `==`가 아니라 strcmp**(12차시 0부에서 배운 그것)

12차시에 "문자열 함수가 어디에 쓰이냐"고 물었죠. 여기 있습니다.

### 6.6 새로 나온 것들

**`fgets(line, BUF_SIZE, stdin)`**

표준 입력에서 최대 `BUF_SIZE - 1`글자를 읽어 `line`에 담고 `\0`을 붙입니다. `scanf("%s")`와 달리 **공백을 포함한 한 줄 전체**를 읽고, **버퍼 크기를 받으므로 오버플로우가 안 납니다.** 12차시에서 배운 "크기를 받는 안전한 함수"의 또 다른 예입니다.

**`fgets`가 NULL을 반환하는 때**

입력이 끝났을 때입니다. 키보드로는 **Ctrl+D**를 누르면 "더 이상 입력 없음(EOF)" 신호가 갑니다. 이걸 처리 안 하면 Ctrl+D를 눌렀을 때 무한 루프에 빠집니다.

**`while (1)` + `break`**

셸은 사용자가 끝내라고 할 때까지 도는 게 정상입니다. 무한 루프는 여기선 버그가 아니라 설계입니다.

### 6.7 16차시 맛보기 — 알맹이는 이렇게 생겼다

16차시에는 3번(해석·실행) 자리에 이런 게 들어갑니다.

```c
/* 16차시에 만들 것 (미리보기) */
char **args = sbs_split(line, ' ');       /* "echo hi" → {"echo", "hi", NULL} */

if (sbs_strcmp(args[0], "echo") == 0)
    builtin_echo(args);
else if (sbs_strcmp(args[0], "pwd") == 0)
    builtin_pwd();
else if (sbs_strcmp(args[0], "help") == 0)
    builtin_help();
else
    printf("minishell: %s: command not found\n", args[0]);

free_args(args);                          /* split이 malloc했으니 해제 */
```

보이나요? **전부 우리가 만든 함수**입니다. 문자열 쪼개기(11차시 malloc + 12차시 strlen), 명령 비교(strcmp), 메모리 해제(free). 16차시는 새로운 걸 배우는 시간이 아니라, **지금까지 만든 걸 조립하는 시간**입니다.

> 미리 생각해보세요: `"echo   hello   world"` 처럼 공백이 여러 개면 어떻게 쪼개야 할까요? 빈 칸은 건너뛰어야겠죠. 이게 16차시 split의 핵심 난제입니다.

---

## 7부: 채점

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

1. `make`로 `libsbs.a`가 생기는가
2. 아카이브에 `.o`가 들어있는가
3. 링크해서 함수가 동작하는가(`-lsbs`)
4. `clean`/`fclean`/`re`가 제대로 동작하는가
5. `make wordinfo`가 빌드되고 올바른 결과를 내는가
6. `make minishell`이 빌드되고 입력/종료가 동작하는가

---

## 핵심 정리

1. Makefile은 **조립 설명서**. 타겟·의존성·레시피, 레시피는 **탭** 들여쓰기
2. make는 **타임스탬프**를 비교해 바뀐 파일만 다시 컴파일
3. 변수와 `$(SRCS:.c=.o)`로 중복 제거 — 파일 추가는 SRCS 한 줄만
4. 패턴 규칙 `%.o: %.c`, 자동 변수 `$<`(소스) `$@`(타겟)
5. `ar rcs libsbs.a *.o`로 정적 라이브러리 생성, 이름은 반드시 `lib***.a`
6. `all/clean/fclean/re` + `.PHONY`(동작은 파일이 아니다)
7. `-L. -lsbs`로 링크, **라이브러리는 소스 뒤에** 써야 함
8. `main.c`는 라이브러리에 넣지 않는다 (부품 아님)
9. 셸 = **REPL 루프**(프롬프트 → 읽기 → 해석·실행 → 반복)
10. 껍데기에서도 `sbs_strlen`(개행 제거) · `sbs_strcmp`("exit" 비교)가 이미 일한다

---

## 다음 차시 예고

16차시는 **미니셸 완성**입니다. 오늘 만든 껍데기의 3단계(해석·실행) 자리에 진짜 명령 해석기를 넣습니다. 입력을 단어로 쪼개고(`split`), 명령 이름을 비교하고(`strcmp`), `echo`·`pwd`·`help`·`exit` 같은 내장 명령을 직접 구현합니다. 9~14차시에 만든 함수들이 총출동하는, 이 과정의 마지막 조립입니다.
