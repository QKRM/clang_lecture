# 16차시 강의 노트 - 종합 프로젝트: 미니셸 만들기

## 학습 목표

1. 15차시에 만든 셸 껍데기(REPL)에 **명령 해석·실행**을 채워 넣는다.
2. 새 함수 `sbs_split`으로 입력을 단어 배열로 쪼갠다.
3. `echo` · `upper` · `len` · `help` · `exit` 내장 명령을 구현한다.
4. 지금까지 만든 **libsbs 전체**를 링크해 하나의 프로그램으로 완성한다.
5. `char **`(문자열 배열)의 메모리 구조와 해제를 이해한다.

---

## 0부: 과정을 마무리하며

9차시부터 한 함수씩, 표준 라이브러리를 손으로 다시 만들었습니다. 문자 판별, 메모리 복사, 동적 할당, 문자열 처리, 그리고 그것들을 묶는 Makefile까지. 오늘은 그 **모든 것을 한꺼번에 써서** 진짜로 돌아가는 프로그램 — 작은 셸(shell) — 을 만듭니다.

새로 배우는 문법은 거의 없습니다. `sbs_split` 하나만 새로 만들고, 나머지는 전부 **이미 여러분이 만든 함수의 조합**입니다. 이게 이 과정의 목적지였습니다: 남이 준 라이브러리가 아니라 **내가 만든 라이브러리로 내 프로그램을 짠다.**

```
                여러분이 9~15차시에 만든 것
   ┌──────────────────────────────────────────┐
   │  isalpha  memcpy  calloc  strlen  strcmp  │
   │  toupper  substr  strjoin  split  ...     │  →  libsbs.a
   └──────────────────────────────────────────┘
                        │  링크(-lsbs)
                        ▼
                   minishell  ← 오늘 만들 프로그램
```

---

## 1부: 미니셸 설계

### 1.1 15차시 껍데기 복습

15차시에서 셸의 뼈대가 **REPL 루프**(프롬프트 → 읽기 → 해석·실행 → 반복)라고 배웠습니다. 그때 만든 껍데기는 3번(해석·실행)을 "입력을 그대로 되돌려 출력"으로 때웠습니다.

```c
/* 15차시: 알맹이가 빈 자리 */
printf("입력: %s\n", line);   // ← 여기를 오늘 채운다
```

### 1.2 오늘 채울 알맹이

그 자리에 들어갈 진짜 명령 처리기는 세 단계입니다.

```
"echo hello world"   (사용자가 친 한 줄)
        │
        │  ① sbs_split(line, ' ')        ← 새 함수
        ▼
   {"echo", "hello", "world", NULL}     (단어 배열)
        │
        │  ② args[0]을 sbs_strcmp로 판별
        ▼
   "echo"구나 → builtin_echo(args)       ③ 실행
        │
        ▼
   hello world                           (출력)
```

핵심은 **입력 한 줄을 단어들로 쪼개는 것**입니다. 그게 `sbs_split`이고, 오늘의 유일한 새 함수입니다.

### 1.3 이번 셸의 규칙

- **내장(builtin) 명령만** 지원합니다. `ls`나 `cat` 같은 외부 프로그램은 실행하지 않습니다(그건 `fork`/`exec`라는 다음 단계 주제).
- 지원 명령: `echo`, `upper`, `len`, `help`, `exit`.
- 모든 명령은 우리가 직접 구현합니다. libsbs 함수만으로.

---

## 2부: sbs_split — 문자열을 단어로 쪼개기

오늘의 주인공입니다. `char **`를 반환하는, 지금까지 중 가장 복잡한 함수입니다. 천천히 봅시다.

### 2.1 무엇을 반환하나

```c
char **sbs_split(const char *s, char c);
```

`s`를 구분자 `c`로 쪼개, **단어들의 배열**을 돌려줍니다. 배열의 끝은 `NULL`로 표시합니다(문자열의 끝을 `\0`으로 표시하듯이).

```
sbs_split("echo hello world", ' ')

   arr ─▶ ┌───────┐
          │  •────┼──▶ "echo\0"
          ├───────┤
          │  •────┼──▶ "hello\0"
          ├───────┤
          │  •────┼──▶ "world\0"
          ├───────┤
          │ NULL  │   ← 끝 표시
          └───────┘
```

`char **`는 "문자열을 가리키는 포인터들의 배열"입니다. 그림처럼 **2단계**입니다: 배열 한 개 + 그 안에 든 문자열 여러 개. 그래서 나중에 해제할 때도 2단계로 풀어야 합니다(4.3에서).

### 2.2 규칙 — 공백을 어떻게 다루나

15차시 끝에 던진 질문입니다. `"echo   hello"`처럼 공백이 여러 개면?

- **연속된 구분자는 하나로** 취급 → 빈 단어를 만들지 않음
- **앞뒤 구분자는 무시**

```
"  a   b  "  ──split(' ')──▶  {"a", "b", NULL}   (빈 칸은 전부 건너뜀)
```

### 2.3 2단계 전략

배열을 malloc하려면 **단어가 몇 개인지 먼저 알아야** 합니다. 그래서 두 번 훑습니다.

1. **1차: 단어 개수 세기** → 배열 크기 결정
2. **2차: 단어마다 잘라 복사** → `sbs_substr` 재사용

### 2.4 1차 — 단어 세기

```c
static size_t count_words(const char *s, char c)
{
    size_t count = 0;
    size_t i = 0;
    while (s[i])
    {
        while (s[i] == c)          // 구분자 구간 건너뛰기
            i++;
        if (s[i])                  // 단어가 시작되면
        {
            count++;               // 개수 +1
            while (s[i] && s[i] != c)  // 단어 끝까지 이동
                i++;
        }
    }
    return (count);
}
```

읽는 법: "구분자를 건너뛴다 → 글자가 있으면 그게 새 단어다(세고) → 단어 끝까지 간다 → 반복." 연속 공백이 자동으로 하나처럼 처리됩니다.

### 2.5 2차 — 잘라서 복사

```c
char **sbs_split(const char *s, char c)
{
    char   **arr;
    size_t words, i, start, k;

    if (s == NULL)
        return (NULL);
    words = count_words(s, c);
    arr = (char **)malloc(sizeof(char *) * (words + 1));   // +1은 NULL 자리
    if (arr == NULL)
        return (NULL);
    i = 0;
    k = 0;
    while (k < words)
    {
        while (s[i] == c)                 // 구분자 건너뛰기
            i++;
        start = i;                        // 단어 시작 위치 기억
        while (s[i] && s[i] != c)         // 단어 끝 찾기
            i++;
        arr[k] = sbs_substr(s, start, i - start);   // 11차시 substr 재사용!
        if (arr[k] == NULL)
            return (free_partial(arr, k), NULL);    // 중간 실패 시 정리
        k++;
    }
    arr[k] = NULL;                        // 끝 표시
    return (arr);
}
```

여기서 두 가지가 핵심입니다.

**① `sizeof(char *) * (words + 1)`** — 배열은 단어 수보다 **1 크게**. 마지막 `NULL` 자리 때문입니다. `strlen`이 `\0` 자리를 남기는 것과 똑같은 발상입니다.

**② `sbs_substr(s, start, i - start)`** — 11차시에 만든 `substr`이 여기서 빛납니다. 시작 위치와 길이만 주면 잘라서 새 메모리에 복사해줍니다. 바퀴를 다시 발명하지 않습니다.

### 2.6 중간 실패 처리

단어를 3개 만들다가 4번째 `malloc`이 실패하면? 이미 만든 3개가 **메모리 누수**로 남습니다. 그래서 정리 함수를 둡니다.

```c
static void free_partial(char **arr, size_t n)
{
    while (n > 0)
        free(arr[--n]);   // 만든 단어들을 역순으로 해제
    free(arr);            // 배열 자체도 해제
}
```

> `return (free_partial(arr, k), NULL);`의 쉼표는 "왼쪽을 실행하고, 오른쪽 값을 반환"하는 콤마 연산자입니다. 정리하고 NULL을 돌려줍니다.

---

## 3부: 내장 명령 만들기

`sbs_split`으로 `args`(단어 배열)를 얻었으면, `args[0]`이 명령 이름이고 `args[1]`부터가 인자입니다. 명령 하나가 함수 하나입니다.

### 3.1 echo — 그대로 되돌리기

```c
static void builtin_echo(char **args)
{
    size_t i = 1;                 // args[0]은 "echo"니까 1부터
    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])          // 마지막이 아니면
            printf(" ");          // 단어 사이에 공백
        i++;
    }
    printf("\n");
}
```

`echo hello world` → `hello world`. 인자가 없으면(`echo`만) 빈 줄만 출력합니다.

### 3.2 upper — 대문자로 (9차시 toupper)

```c
static void builtin_upper(char **args)
{
    size_t i = 1, j;
    while (args[i])
    {
        j = 0;
        while (args[i][j])
        {
            printf("%c", sbs_toupper((unsigned char)args[i][j]));
            j++;
        }
        if (args[i + 1])
            printf(" ");
        i++;
    }
    printf("\n");
}
```

`upper abc def` → `ABC DEF`. 9차시 `sbs_toupper`가 글자 하나씩 대문자로 바꿉니다.

### 3.3 len — 길이 재기 (12차시 strlen)

```c
static void builtin_len(char **args)
{
    size_t i = 1;
    if (args[1] == NULL)
    {
        printf("len: 인자가 필요합니다\n");
        return ;
    }
    while (args[i])
    {
        printf("%s: %zu\n", args[i], sbs_strlen(args[i]));
        i++;
    }
}
```

`len hello world` → `hello: 5` / `world: 5`.

### 3.4 help — 도움말

```c
static void builtin_help(void)
{
    printf("사용 가능한 명령:\n");
    printf("  echo [말...]   입력한 말을 그대로 출력\n");
    printf("  upper [말...]  대문자로 출력\n");
    printf("  len [말...]    각 말의 길이 출력\n");
    printf("  help          이 도움말\n");
    printf("  exit          종료\n");
}
```

---

## 4부: 조립 — 디스패치 + 메인 루프

### 4.1 run_command — 명령을 알맞은 함수로 보내기

`args[0]`을 `sbs_strcmp`로 비교해 해당 명령을 호출합니다. 이런 "이름 보고 갈래를 정하는" 구조를 **디스패치(dispatch)**라 합니다.

```c
static int run_command(char **args)
{
    if (args[0] == NULL)               // 빈 줄(공백만 입력)
        return (0);
    if (sbs_strcmp(args[0], "exit") == 0)
        return (1);                    // 1 = 종료 신호
    if (sbs_strcmp(args[0], "echo") == 0)
        builtin_echo(args);
    else if (sbs_strcmp(args[0], "upper") == 0)
        builtin_upper(args);
    else if (sbs_strcmp(args[0], "len") == 0)
        builtin_len(args);
    else if (sbs_strcmp(args[0], "help") == 0)
        builtin_help();
    else
        printf("minishell: %s: command not found\n", args[0]);
    return (0);
}
```

- `args[0] == NULL`을 **먼저** 봅니다. 빈 줄이면 `args[0]`이 없어서, 바로 `strcmp`하면 NULL을 읽어 크래시하니까요. (13차시에서 배운 NULL 역참조 함정)
- `exit`만 `1`을 반환합니다. 이 신호로 메인 루프를 끝냅니다.

### 4.2 main — 15차시 껍데기 + 알맹이

```c
int main(void)
{
    char   line[BUF_SIZE];
    char   **args;
    int    done = 0;

    while (!done)
    {
        printf("minishell$ ");
        fflush(stdout);                          // 프롬프트를 지금 화면에(15차시)
        if (fgets(line, BUF_SIZE, stdin) == NULL) // Ctrl+D
        {
            printf("\n");
            break ;
        }
        strip_newline(line);                     // 줄 끝 \n 제거(sbs_strlen)
        args = sbs_split(line, ' ');             // ① 쪼개기
        if (args == NULL)                        // malloc 실패
            break ;
        done = run_command(args);                // ②③ 판별·실행
        sbs_free_split(args);                    // ④ 해제 (누수 방지!)
    }
    printf("bye\n");
    return (0);
}
```

15차시 껍데기와 비교하면 딱 세 줄이 늘었습니다: `split` → `run_command` → `free_split`. 뼈대는 그대로입니다.

### 4.3 char ** 해제 — 왜 2번 free 하나

`sbs_split`이 malloc을 **여러 번** 했습니다: 배열 1번 + 단어마다 1번씩. 그래서 해제도 그만큼 해야 합니다. 하나라도 빠지면 메모리 누수입니다.

```c
void sbs_free_split(char **arr)
{
    size_t i = 0;
    if (arr == NULL)
        return ;
    while (arr[i])         // 단어들을 먼저 하나씩
    {
        free(arr[i]);
        i++;
    }
    free(arr);             // 배열 자체는 마지막에
}
```

```
   arr ─▶ ┌───────┐
          │  •────┼──▶ "echo"    ← free(arr[0])
          │  •────┼──▶ "hello"   ← free(arr[1])
          │  •────┼──▶ "world"   ← free(arr[2])
          │ NULL  │
          └───────┘  ← free(arr)  (배열은 맨 마지막)
```

**순서가 중요**합니다. 배열(`arr`)을 먼저 free하면, 그 안에 있던 단어들의 주소를 잃어버려 영영 해제 못 합니다. 안쪽(단어)부터, 바깥(배열)은 마지막.

---

## 5부: 빌드하고 실행하기

### 5.1 폴더 구조 — src / obj 분리

파일이 많아지면 소스와 컴파일 결과를 섞어두기 지저분합니다. 그래서 이렇게 나눕니다.

```
session_16/
├── src/          libsbs 소스(sbs_*.c) 전부 — 오늘 추가한 split 2개 포함
├── obj/          컴파일 결과(.o) — make가 자동 생성
├── libsbs.h      헤더
├── minishell.c   프로그램 소스 (라이브러리 아님)
└── Makefile
```

### 5.2 Makefile

15차시에서 배운 그대로에, **경로만** `src/` → `obj/`로 바뀝니다.

```makefile
SRC_DIR = src
OBJ_DIR = obj
# 함수 이름만 나열하고 경로/확장자는 자동으로 붙인다
NAMES = sbs_isalpha ... sbs_atoi sbs_split sbs_free_split
SRCS  = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(NAMES)))
OBJS  = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(NAMES)))

# src/%.c → obj/%.o  ( | $(OBJ_DIR)로 obj/ 폴더를 먼저 만든다 )
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c libsbs.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(MINISHELL): $(OBJ_DIR)/minishell.o $(NAME)
	$(CC) $(CFLAGS) $(OBJ_DIR)/minishell.o -L. -lsbs -o $(MINISHELL)
```

세 가지가 새로 나옵니다.

- **`| $(OBJ_DIR)`** — 파이프(`|`) 뒤는 "순서만 지키는(order-only) 의존성". "obj/ 폴더가 먼저 있어야 한다"는 뜻인데, 폴더의 수정 시각은 무시해서 불필요한 재빌드를 막습니다.
- **`-I.`** — src/에서 컴파일하지만 `libsbs.h`는 루트에 있으니, "헤더를 현재 폴더(`.`)에서도 찾아라".
- **`clean`은 `rm -rf obj`** — 이제 `.o`가 obj/ 안에 모여 있으니 폴더째 지웁니다.

`minishell.c`는 `NAMES`(라이브러리 소스)에 **넣지 않습니다.** `main`이 있으니 라이브러리가 아니라 프로그램입니다(15차시 규칙).

### 5.3 빌드 & 실행

```bash
$ make            # src/ 컴파일 → obj/*.o → libsbs.a
$ make minishell  # libsbs.a를 링크해 minishell 실행 파일
$ ./minishell
minishell$ echo hello world
hello world
minishell$ upper hello
HELLO
minishell$ len minishell
minishell: 9
minishell$ help
사용 가능한 명령:
  echo [말...]   입력한 말을 그대로 출력
  ...
minishell$ nosuch
minishell: nosuch: command not found
minishell$ exit
bye
$
```

---

## 6부: 채점

```bash
$ bash grade.sh
=== libsbs 16차시 종합 채점 (미니셸) ===
✓ make → libsbs.a 빌드
✓ sbs_split / sbs_free_split 동작 (SPLIT_OK)
✓ make minishell — 빌드
✓ minishell 동작 (echo/upper/len/미존재/exit)
✓ clean / fclean / re 동작
결과: 5 / 5 통과
🎉 libsbs 미니셸 완성! 과정을 모두 마쳤습니다.
```

1. `libsbs.a`가 빌드되는가(금지 헤더 없이)
2. `sbs_split`이 규칙대로(연속 공백·빈 문자열) 동작하는가
3. `minishell`이 빌드되는가
4. 각 내장 명령이 올바로 동작하는가
5. `clean`/`fclean`/`re`가 동작하는가

---

## 핵심 정리

1. 셸의 알맹이 = **쪼개기(split) → 판별(strcmp) → 실행(builtin)**
2. `sbs_split`은 `char **` 반환, 배열 끝은 `NULL`, 크기는 단어 수 **+1**
3. 단어 세기 → 배열 malloc → `sbs_substr`로 잘라 복사 (2단계)
4. 연속·앞뒤 구분자는 무시(빈 단어 안 만듦)
5. `char **` 해제는 **안쪽 단어부터, 배열은 마지막** — 순서 지켜야 누수 없음
6. `run_command`는 `args[0] == NULL`을 **먼저** 검사(빈 줄 NULL 역참조 방지)
7. 내장 명령은 전부 libsbs 조합: echo(strlen 흐름) · upper(toupper) · len(strlen) · exit(strcmp)
8. `minishell.c`는 라이브러리(SRCS)가 아니라 프로그램 — `-L. -lsbs`로 링크

---

## 과정을 마치며

9차시부터 16차시까지, 표준 라이브러리를 직접 구현하고 그것으로 진짜 프로그램을 만들었습니다. 여러분은 이제:

- 표준 함수가 **속으로 어떻게 동작하는지** 압니다.
- 메모리를 **바이트 단위로, 손으로** 다룹니다.
- `malloc`한 것을 빠짐없이 `free`합니다.
- 빌드 시스템(Makefile)과 라이브러리(.a)를 직접 만듭니다.
- 그 모두를 조합해 **동작하는 프로그램**을 짭니다.

이게 C의 본질입니다. 포인터·메모리·빌드를 손으로 겪은 사람만이 그 위의 모든 것(운영체제, 네트워크, 임베디드)을 두려움 없이 배웁니다. 수고하셨습니다.

> 더 해보고 싶다면: `cd`/`pwd`(디렉토리 이동, `chdir`/`getcwd`), 그리고 진짜 외부 명령 실행(`fork`+`execve`)이 다음 단계입니다. 오늘 만든 껍데기가 그대로 그 출발점이 됩니다.
