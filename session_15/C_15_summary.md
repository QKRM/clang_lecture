# 15차시: Makefile과 라이브러리 아카이브

## 학습 목표

1. Makefile 문법(타겟·의존성·레시피)
2. 변수와 패턴 규칙
3. ar로 정적 라이브러리
4. libsbs.a 빌드 + 링크
5. all/clean/fclean/re 규칙
6. libsbs 활용 프로그램(wordinfo) 만들기
7. 미니셸 뼈대(REPL 루프) 이해 — 16차시 예고

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
> **순서**: 라이브러리는 소스 **뒤에**. `cc -lsbs main.c`는 undefined reference.

---

### 7. libsbs 활용 프로그램 (wordinfo)

```makefile
$(WORDINFO): main.o $(NAME)      # 의존성에 라이브러리!
	$(CC) $(CFLAGS) main.o -L. -lsbs -o $(WORDINFO)
```

```bash
$ ./wordinfo hello     # 길이 5 / 대문자 HELLO / 알파벳 예
```

> **main.c는 SRCS에 넣지 않는다.** 라이브러리는 부품 모음 — main이 박히면 다른 프로그램과 충돌.
> size_t 출력은 `%zu` (`%d`면 -Werror에서 터짐).

---

### 8. 미니셸 뼈대 — REPL 루프 (16차시 예고)

셸 = **프롬프트 → 읽기 → 해석·실행 → 반복**. bash도 같은 구조.

```c
while (1)
{
    printf("minishell$ ");
    if (fgets(line, BUF_SIZE, stdin) == NULL)   /* Ctrl+D = EOF */
        break ;
    strip_newline(line);                        /* sbs_strlen 사용 */
    if (sbs_strcmp(line, "exit") == 0)          /* 문자열 비교는 == 아님! */
        break ;
    printf("입력: %s\n", line);                 /* ← 16차시에 해석기로 교체 */
}
```

| 단계 | 15차시 | 16차시 |
|------|--------|--------|
| 프롬프트/읽기/반복 | ✅ | 그대로 |
| 해석 | 그냥 되돌려 출력 | split으로 단어 쪼개기 |
| 실행 | 없음 | echo/pwd/help 구현 |

> `fgets`: 공백 포함 한 줄, **버퍼 크기를 받아** 오버플로우 없음(12차시 안전 함수와 같은 사상).
> 껍데기인데도 `sbs_strlen`(개행 제거)·`sbs_strcmp`("exit" 판정)가 이미 일한다.

---

## 실행 전 체크리스트

- [ ] 레시피가 탭으로 들여쓰기 되었는가?
- [ ] OBJS = $(SRCS:.c=.o) 치환을 썼는가?
- [ ] ar rcs로 .a를 만드는가?
- [ ] SRCS에 main.c / minishell.c가 안 들어갔는가?
- [ ] .PHONY를 선언했는가?
- [ ] make wordinfo / make minishell 동작하는가?
- [ ] `bash grade.sh` → 6/6?

---

## 다음 차시 예고

- **16차시: 미니셸 완성**
- 오늘 만든 껍데기의 '해석·실행' 자리에 진짜 명령 해석기 삽입
- split으로 단어 쪼개기 + echo/pwd/help/exit 내장 명령 구현
- 9~14차시 함수 총출동 — 과정의 마지막 조립

---

## 트러블슈팅

| 증상 | 확인 사항 |
|------|----------|
| missing separator | 레시피를 탭으로 |
| undefined reference | -lsbs가 소스 **뒤에** 있는지, ar에 .o 포함 |
| make가 아무것도 안 함 | all 타겟, 파일 이름 확인 |
| clean이 안 됨 | .PHONY 선언 |
| -lsbs 못 찾음 | -L. 추가, 이름이 libsbs.a인지 |
| multiple definition of main | SRCS에 main.c를 넣었다 |
| %zu 경고 | size_t는 %d 아니라 %zu |
| minishell이 exit 안 먹음 | strip_newline 빠짐("exit\n" != "exit") |
| Ctrl+D에 무한 루프 | fgets NULL 처리 누락 |
