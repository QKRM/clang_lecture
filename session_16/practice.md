# 16차시 실습 - 종합 프로젝트: 미니셸 만들기

## 실습 목표

- 새 함수 `sbs_split`으로 입력을 단어 배열로 쪼갠다.
- `sbs_free_split`으로 `char **`를 누수 없이 해제한다.
- `echo` · `upper` · `len` · `help` · `exit` 내장 명령을 구현한다.
- libsbs 전체를 링크해 `minishell`을 완성한다.


> **금지**: `sbs_split.c`에서 `<string.h>`, `<strings.h>` 사용. `<stdlib.h>`(malloc)는 허용.

---

## 준비: 실습 파일 내려받기

페이지 맨 위 **실습 파일 내려받기**로 `session_16_starter.zip`을 받으세요. 9~14차시에 만든 함수 전체가 라이브러리로 들어 있고, 여러분이 채울 부분만 비어 있습니다.

```
session_16_starter/
├── libsbs.h                 전체 프로토타입 (split 2개 포함)
├── sbs_*.c                  9~14차시 함수 32개 (제공)
├── sbs_split.c              ⭐ 직접 구현 (스켈레톤)
├── sbs_free_split.c         ⭐ 직접 구현 (스켈레톤)
├── minishell.c              ⭐ 내장 명령 채우기 (스켈레톤)
├── Makefile                 제공 (libsbs.a + minishell)
├── tests/test_split.c       split 단위 테스트
├── grade.sh                 채점 스크립트
└── README.md
```

```bash
$ unzip session_16_starter.zip
$ cd session_16_starter
```

> 정답은 이 페이지 맨 아래 **정답 코드**에 있습니다. 먼저 직접 해본 뒤 확인하세요.

---

## 과제 1: sbs_split — 단어 세기

`sbs_split.c`의 `count_words`부터 완성하세요. 구분자로 나뉜 단어가 몇 개인지 셉니다.

요구사항:
- 연속된 구분자는 하나로 취급
- 앞뒤 구분자는 무시

힌트:
```c
static size_t count_words(const char *s, char c)
{
    size_t count = 0, i = 0;
    while (s[i])
    {
        while (s[i] == c)              // 구분자 건너뛰기
            i++;
        if (s[i])                      // 단어 시작
        {
            count++;
            while (s[i] && s[i] != c)  // 단어 끝까지
                i++;
        }
    }
    return (count);
}
```

---

## 과제 2: sbs_split — 잘라서 복사

배열을 malloc하고, 단어마다 `sbs_substr`로 잘라 채우세요.

요구사항:
- 배열 크기는 `단어 수 + 1` (마지막 NULL 자리)
- 각 단어는 `sbs_substr(s, start, 길이)`로 복사
- 마지막 칸에 `NULL`
- `s == NULL`이면 `NULL` 반환

힌트:
```c
arr = (char **)malloc(sizeof(char *) * (words + 1));
if (arr == NULL)
    return (NULL);
// while (k < words): 구분자 건너뛰고 → start 기억 → 단어 끝 찾고
//                    → arr[k] = sbs_substr(s, start, i - start);
arr[k] = NULL;
```

> `sbs_substr`은 11차시에 만든 함수입니다. 시작 위치와 길이만 주면 잘라서 새 메모리에 복사해줍니다. 다시 만들지 마세요.

---

## 과제 3: sbs_free_split — 2단계 해제

`char **`는 malloc이 여러 번(배열 + 단어들) 됐습니다. 순서대로 해제하세요.

힌트:
```c
void sbs_free_split(char **arr)
{
    size_t i = 0;
    if (arr == NULL)
        return ;
    while (arr[i])       // 단어부터
    {
        free(arr[i]);
        i++;
    }
    free(arr);           // 배열은 마지막
}
```

> **순서 주의**: 배열을 먼저 free하면 단어들의 주소를 잃어 해제 못 합니다. 안쪽부터.

확인 — split 단위 테스트:
```bash
$ make
$ cc -Wall -Wextra -Werror -I. tests/test_split.c -L. -lsbs -o tsplit
$ ./tsplit
SPLIT_OK
```

---

## 과제 4: 내장 명령 구현

`minishell.c`의 빈 내장 명령들을 채우세요.

- `builtin_echo(args)` — `args[1]`부터 공백으로 이어 출력
- `builtin_upper(args)` — 각 글자를 `sbs_toupper`로 대문자
- `builtin_len(args)` — 각 인자를 `sbs_strlen`으로 길이 출력
- `builtin_help()` — 명령 목록 출력

힌트(echo):
```c
size_t i = 1;
while (args[i])
{
    printf("%s", args[i]);
    if (args[i + 1])
        printf(" ");
    i++;
}
printf("\n");
```

---

## 과제 5: 디스패치 + 메인 루프

`run_command`에서 `args[0]`을 `sbs_strcmp`로 판별해 알맞은 내장 명령을 부르세요.

요구사항:
- `args[0] == NULL`(빈 줄)을 **가장 먼저** 검사 (NULL 역참조 방지)
- `exit`는 종료 신호(예: `return 1`)
- 없는 명령은 `minishell: 이름: command not found`

힌트:
```c
if (args[0] == NULL)
    return (0);
if (sbs_strcmp(args[0], "exit") == 0)
    return (1);
if (sbs_strcmp(args[0], "echo") == 0)
    builtin_echo(args);
else if (...)
    ...
else
    printf("minishell: %s: command not found\n", args[0]);
return (0);
```

메인 루프(15차시 껍데기 + 3줄):
```c
args = sbs_split(line, ' ');
if (args == NULL)
    break ;
done = run_command(args);
sbs_free_split(args);      // 잊으면 메모리 누수!
```

---

## 과제 6: 빌드 + 실행

```bash
$ make minishell
$ ./minishell
minishell$ echo hello world
hello world
minishell$ upper abc def
ABC DEF
minishell$ len hello
hello: 5
minishell$ nosuch
minishell: nosuch: command not found
minishell$ exit
bye
$
```

Ctrl+D로도 종료되는지, 그냥 Enter(빈 줄)를 쳐도 안 죽는지 확인하세요.

---

## 과제 7: 채점

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

실패 시 `bash grade.sh -v`로 상세 로그를 확인하세요.

---

## 제출 확인 사항

- [ ] `sbs_split.c` - 단어 세기 + 잘라 복사, 끝에 NULL, `<string.h>` 미사용
- [ ] `sbs_free_split.c` - 단어 먼저, 배열 마지막
- [ ] `minishell.c` - echo/upper/len/help 구현
- [ ] `run_command` - `args[0]==NULL` 먼저 검사, exit 종료
- [ ] 메인 루프에서 `sbs_free_split` 호출(누수 방지)
- [ ] `minishell.c`가 SRCS에 **안** 들어갔는가
- [ ] `bash grade.sh` → 5 / 5 통과

---

## 더 생각해볼 거리

1. `sbs_split`이 배열을 `단어 수 + 1`로 만드는 이유는? (마지막 NULL 자리 — strlen의 \0과 같은 발상)
2. `char **`를 free할 때 배열을 먼저 free하면 왜 안 되나? (단어들의 주소를 잃어 누수)
3. `run_command`에서 `args[0]==NULL`을 안 보면 어떤 입력에서 죽나? (빈 줄 → NULL 역참조)
4. `echo`가 여러 공백을 하나로 합치는 이유는? (split이 연속 구분자를 무시하니까)
5. 진짜 셸처럼 `ls`를 실행하려면 무엇이 더 필요할까? (`fork` + `execve` — 자식 프로세스에서 외부 프로그램 실행. 다음 단계 주제)
