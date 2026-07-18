# 16차시: 종합 프로젝트 — 미니셸 만들기

## 학습 목표

1. 셸 껍데기(REPL)에 명령 해석·실행 채우기
2. `sbs_split`으로 입력을 단어 배열로 쪼개기
3. echo/upper/len/help/exit 내장 명령 구현
4. libsbs 전체를 링크해 minishell 완성
5. `char **` 메모리 구조와 해제

---

## 핵심 개념

### 1. 셸의 알맹이 3단계

```
"echo hi"  ──split──▶  {"echo","hi",NULL}  ──strcmp──▶  builtin_echo
   입력          쪼개기          단어 배열         판별          실행
```

15차시 껍데기(REPL)의 "그냥 되돌려 출력" 자리를 이 3단계로 교체.

---

### 2. sbs_split — char ** 반환

```c
char **sbs_split(const char *s, char c);
// "echo hi" → {"echo", "hi", NULL}
```

- 배열 끝은 **NULL**, 크기는 **단어 수 + 1**
- 연속·앞뒤 구분자는 무시(빈 단어 안 만듦)
- 2단계: ① 단어 세기 → ② `sbs_substr`로 잘라 복사

```c
words = count_words(s, c);
arr = malloc(sizeof(char *) * (words + 1));   // +1 = NULL 자리
// 단어마다: arr[k] = sbs_substr(s, start, i - start);
arr[k] = NULL;
```

---

### 3. char ** 해제 — 순서가 핵심

```c
while (arr[i]) free(arr[i++]);   // ① 단어부터
free(arr);                        // ② 배열은 마지막
```

> 배열을 먼저 free하면 단어 주소를 잃어 누수. **안쪽→바깥쪽.**

---

### 4. 디스패치 (run_command)

```c
if (args[0] == NULL) return (0);          // 빈 줄 먼저! (NULL 역참조 방지)
if (sbs_strcmp(args[0], "exit") == 0) return (1);
if (sbs_strcmp(args[0], "echo") == 0) builtin_echo(args);
else if ...
else printf("minishell: %s: command not found\n", args[0]);
```

---

### 5. 내장 명령 (전부 libsbs 조합)

| 명령 | 쓰는 함수 |
|------|-----------|
| echo | 인자 이어 출력 |
| upper | 9차시 sbs_toupper |
| len | 12차시 sbs_strlen |
| exit | 12차시 sbs_strcmp |

---

### 6. 메인 루프 (15차시 + 3줄)

```c
printf("minishell$ "); fflush(stdout);       // 15차시
if (fgets(line, BUF_SIZE, stdin) == NULL) break;
strip_newline(line);
args = sbs_split(line, ' ');                 // +
if (args == NULL) break;                     // +
done = run_command(args);                    // +
sbs_free_split(args);                        // + (누수 방지!)
```

---

### 7. 빌드 (src / obj 분리)

```
src/  = libsbs 소스(sbs_*.c)     obj/ = 컴파일 결과(.o, 자동 생성)
```

```makefile
SRC_DIR = src
OBJ_DIR = obj
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c libsbs.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I. -c $< -o $@
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(MINISHELL): $(OBJ_DIR)/minishell.o $(NAME)   # minishell.c는 라이브러리에서 제외
	$(CC) $(CFLAGS) $(OBJ_DIR)/minishell.o -L. -lsbs -o $(MINISHELL)
clean:
	$(RM) -r $(OBJ_DIR)
```

> `| $(OBJ_DIR)`(order-only)로 폴더 먼저 생성, `-I.`로 루트의 libsbs.h를 찾음.

---

## 실행 전 체크리스트

- [ ] sbs_split 끝에 NULL, 크기 단어수+1?
- [ ] sbs_free_split 단어→배열 순서?
- [ ] run_command가 args[0]==NULL 먼저 검사?
- [ ] 메인 루프에서 sbs_free_split 호출?
- [ ] minishell.c가 SRCS에 없나?
- [ ] `bash grade.sh` → 5/5?

---

## 과정 완료

9~16차시: 헤더 → 문자 함수 → 메모리 함수 → 동적 메모리 → 문자열 함수 → Makefile/라이브러리 → **미니셸**.
표준 라이브러리를 직접 구현하고, 그것으로 동작하는 프로그램을 만들었다.

**libsbs 과정 수료. 수고하셨습니다.**

> 다음 단계: cd/pwd(chdir/getcwd), 외부 명령 실행(fork+execve).

---

## 트러블슈팅

| 증상 | 확인 사항 |
|------|----------|
| 빈 줄 입력 시 크래시 | run_command에서 args[0]==NULL 먼저 |
| 메모리 누수(valgrind) | sbs_free_split 호출 빠짐 |
| free 중 크래시 | 배열을 단어보다 먼저 free함 |
| echo 공백 여러 개 | 정상 — split이 연속 구분자 무시 |
| undefined reference: sbs_split | SRCS에 sbs_split.c 추가, -lsbs 순서 |
| multiple definition of main | minishell.c를 SRCS에 넣었다 |
