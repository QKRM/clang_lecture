# 1차시: GitHub Codespaces 세팅 + C언어 첫걸음

## 학습 목표

1. GitHub Codespaces를 직접 생성하고 gcc가 동작함을 확인할 수 있다
2. `gcc -Wall -Wextra -Werror`로 C 프로그램을 컴파일하고 실행할 수 있다
3. C 소스 파일의 기본 구조(`#include`, `main`, `return`)를 설명할 수 있다
4. `printf`로 다양한 형식의 출력을 작성할 수 있다
5. `man 3 함수명`으로 표준 라이브러리 함수의 명세를 확인할 수 있다

---

## 핵심 개념

### 1. C언어의 역사

| 연도 | 사건 |
|------|------|
| 1969 | UNIX 탄생 — Ken Thompson + Dennis Ritchie (Bell Labs) |
| 1972 | **C언어 탄생** — Dennis Ritchie. UNIX를 C언어로 재작성 |
| 1991 | **Linux 커널** — Linus Torvalds (21세). 전부 C언어로 작성. 현재 서버의 96% |
| 2005 | **Git** — 역시 Linus Torvalds. 기존 도구 유료화에 반발해 2주 만에 직접 제작 |

> C언어로 만들어진 것: Linux 커널, Git, CPython 인터프리터, nginx, Redis 등

---

### 2. GitHub Codespaces 세팅

**생성 순서**

1. `github.com` 로그인
2. `+` → New repository → 이름: `libsbs` → README 체크 → Create
3. 리포지토리 페이지 → `<> Code` → Codespaces 탭 → **Create codespace on main**
4. 약 1~2분 대기 후 브라우저에 VS Code 환경이 열림

**환경 확인**

```bash
$ gcc --version
gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0
```

> ⚠ README 체크를 빠뜨리면 Codespace 생성이 안 됩니다.

---

### 3. 터미널 기본 명령어

| 명령어 | 설명 |
|--------|------|
| `pwd` | 현재 디렉토리 경로 확인 |
| `ls` | 파일 목록 출력 |
| `ls -la` | 숨김 파일 포함, 상세 정보 출력 |
| `mkdir 폴더명` | 폴더 생성 |
| `cd 폴더명` | 폴더 이동 |
| `cd ..` | 상위 폴더로 이동 |
| `touch 파일명` | 빈 파일 생성 |
| `clear` | 터미널 화면 지우기 |

> **Tab 자동완성**: 파일명/폴더명 입력 중 Tab 키를 누르면 자동 완성됨. 필수 습관.

---

### 4. 첫 번째 C 프로그램 구조

```c
#include <stdio.h>

int main(void)
{
    printf("Hello, World!\n");
    return (0);
}
```

| 코드 | 의미 |
|------|------|
| `#include <stdio.h>` | 전처리기 지시문. `printf` 사용을 위해 필수 |
| `int main(void)` | 진입점. C 프로그램은 항상 main에서 시작 |
| `printf("...\n")` | 화면에 출력. `\n`은 줄바꿈 |
| `return (0);` | 0 = 정상 종료. 운영체제가 이 값으로 성공/실패 판단 |

> 권장 코드 스타일: 여는 중괄호 `{`는 새 줄에, `return (0);`처럼 반환값에 괄호 사용

---

### 5. 컴파일과 실행

```bash
# 컴파일
$ gcc -Wall -Wextra -Werror hello.c -o hello

# 실행
$ ./hello
Hello, World!
```

**컴파일 과정**: 소스(.c) → 전처리 → 컴파일 → 어셈블 → 링킹 → 실행 파일

**필수 컴파일 옵션**

| 옵션 | 의미 |
|------|------|
| `-Wall` | 대부분의 경고(warning) 표시 |
| `-Wextra` | 추가적인 경고 표시 |
| `-Werror` | 경고를 에러로 처리 → 경고가 있으면 컴파일 실패 |

> `-Werror`는 권장 사항. 경고 하나도 없는 코드 작성이 목표.

---

### 6. printf 서식 지정자와 이스케이프 문자

**서식 지정자**

| 지정자 | 의미 |
|--------|------|
| `%d` | 정수 (int) |
| `%f` | 실수 (float, double) |
| `%.2f` | 소수점 둘째 자리까지 (자릿수 지정) |
| `%c` | 문자 (char) |
| `%s` | 문자열 (char 배열) |
| `%p` | 포인터 주소 (16진수) |

**이스케이프 문자**

| 이스케이프 | 의미 |
|-----------|------|
| `\n` | 줄바꿈 |
| `\t` | 탭 |
| `\"` | 큰따옴표 자체 |
| `\\` | 백슬래시 자체 |
| `\0` | null 문자 — 문자열의 끝 표시 (이후 차시에서 매우 중요) |

> `%%`로 `%` 기호 자체를 출력할 수 있다 (`printf("100%%")` → `100%`)

---

### 7. 경고와 에러 — `-Wall -Wextra -Werror` 체험

`warning_demo.c`에는 의도적인 두 가지 문제가 들어 있다.

```c
int result = 42;   /* unused variable — 선언했지만 한 번도 안 씀 */
int x;             /* uninitialized — 초기화 없이 바로 출력에 사용 */
printf("계산 결과: %d\n", x);
```

**실습 순서**

```bash
# 1단계: 경고 없이 컴파일 → 성공하지만 위험한 코드
$ gcc warning_demo.c -o warning_demo

# 2단계: 엄격 모드 → 컴파일 실패, 에러 메시지 확인
$ gcc -Wall -Wextra -Werror warning_demo.c -o warning_demo

# 과제: 경고를 모두 없애고 2단계도 통과하도록 수정
```

| 경고 메시지 | 원인 | 수정법 |
|-------------|------|--------|
| `unused variable 'result'` | 선언만 하고 사용 안 함 | 삭제하거나 실제로 사용 |
| `'x' is used uninitialized` | 초기화 없이 값 읽기 | `int x = 0;` 처럼 초기화 |

---

### 8. bash에서 표준 함수 정의 확인

앞으로 직접 구현할 함수들의 명세를 `man` 명령어로 확인한다.

```bash
# 함수 명세 확인 (Section 3 = C Library Functions)
$ man 3 strlen

# 헤더 파일에서 직접 선언 확인
$ grep "strlen" /usr/include/string.h
extern size_t strlen (const char *__s)
     __THROW __attribute_pure__ __nonnull ((1));
```

**man page 구조**

| 섹션 | 내용 |
|------|------|
| `NAME` | 함수 이름과 한 줄 설명 |
| `SYNOPSIS` | 함수 원형 — 헤더, 반환형, 매개변수 |
| `DESCRIPTION` | 상세 동작 설명 |
| `RETURN VALUE` | **반환값 설명 — 구현할 때 가장 중요** |

> 앞으로의 수업에서 `man 3 memset`, `man 3 strchr`, `man 3 atoi` 등을 보며 함수를 직접 구현한다.

---

## 실습 코드

**hello.c** — 첫 번째 C 프로그램
```c
#include <stdio.h>

int main(void)
{
    printf("Hello, World!\n");
    return (0);
}
```

**format.c** — 서식 지정자 총정리
```c
int    age    = 21;
double height = 175.5;
char   grade  = 'A';
char   name[] = "Linus";

printf("정수  (%%d)     : %d\n", age);
printf("실수  (%%.2f)   : %.2f\n", height);
printf("문자  (%%c)     : %c\n", grade);
printf("문자열(%%s)     : %s\n", name);
printf("주소  (%%p)     : %p\n", (void *)&age);
```

**warning_demo.c** — 경고 체험 (수정 과제)
```c
int result = 42;            /* unused variable */
int x;                      /* uninitialized   */
printf("계산 결과: %d\n", x);
```

```bash
# 공통 컴파일/실행 패턴
$ gcc -Wall -Wextra -Werror <파일명>.c -o <출력명>
$ ./<출력명>
```

---

## 실행 전 체크리스트

- [ ] Codespace가 완전히 로딩되었는가? (`gcc --version` 출력 확인)
- [ ] `hello.c` 파일이 생성되었는가? (`ls`로 확인)
- [ ] `#include <stdio.h>`가 첫 줄에 있는가?
- [ ] 모든 문장 끝에 `;` 세미콜론이 있는가?
- [ ] `-Wall -Wextra -Werror` 옵션을 붙여 컴파일했는가?
- [ ] 실행 시 `./` 를 앞에 붙였는가?
- [ ] `format.c` 컴파일 시 `%zu` 없이 `%p`에 `(void *)`를 붙였는가?
- [ ] `warning_demo.c` 수정 과제를 완료했는가? (`-Werror` 통과 확인)

---

## 다음 차시 예고

- **2차시: 변수, 자료형, 연산자**
- `int`, `char`, `float`, `double` — 각 타입의 크기와 범위
- `sizeof` 연산자로 타입별 크기 직접 확인
- 형 변환(casting), 연산자 우선순위
- 실습: 간단한 계산기 프로그램 작성

---

## 트러블슈팅

| 증상 | 확인 사항 |
|------|----------|
| Codespace가 안 열림 | README 체크 여부 확인, 브라우저 팝업 차단 해제 |
| `gcc: command not found` | Codespace 완전 로딩 전. 잠시 대기 후 재시도 |
| 컴파일해도 아무 메시지 없음 | 정상. 에러 없으면 메시지 없이 실행 파일 생성됨 |
| `./hello: Permission denied` | `chmod +x hello` 실행 후 재시도 |
| 경고가 에러로 처리됨 | `-Werror` 때문. 경고를 모두 수정해야 컴파일 성공 |
