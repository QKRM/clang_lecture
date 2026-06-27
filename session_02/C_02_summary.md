# 2차시: 변수, 자료형, 연산자

## 학습 목표

1. `sizeof`로 각 자료형의 실제 크기를 확인할 수 있다
2. 정수 나눗셈과 실수 나눗셈의 차이를 설명하고, 형 변환으로 전환할 수 있다
3. 산술/비교/논리 연산자를 올바르게 사용할 수 있다
4. `unsigned char`와 `size_t`가 libsbs 구현에서 왜 필요한지 설명할 수 있다

---

## 핵심 개념

### 1. 기본 자료형

| 자료형 | 크기 | 범위 | 용도 |
|--------|------|------|------|
| `char` | 1 B | -128 ~ 127 | 문자 1개, 작은 정수 |
| `unsigned char` | 1 B | 0 ~ 255 | 바이트 단위 메모리 처리 |
| `int` | 4 B | ±21억 | 일반 정수 |
| `long` | 8 B | 매우 큰 정수 | 큰 정수 |
| `float` | 4 B | 7자리 정밀도 | 실수 |
| `double` | 8 B | 15자리 정밀도 | 정밀한 실수 |

> 크기는 시스템마다 다를 수 있음 — 항상 `sizeof`로 직접 확인

---

### 2. sizeof 연산자

```c
printf("char   : %zu 바이트\n", sizeof(char));
printf("int    : %zu 바이트\n", sizeof(int));
printf("double : %zu 바이트\n", sizeof(double));
printf("int*   : %zu 바이트\n", sizeof(int *));
```

> `sizeof`의 반환 타입은 `size_t` → 출력 시 반드시 `%zu` 사용 (아니면 -Wformat 경고)

---

### 3. unsigned와 size_t

| 자료형 | 범위 |
|--------|------|
| `char` | -128 ~ 127 |
| `unsigned char` | 0 ~ 255 |
| `int` | -2,147,483,648 ~ 2,147,483,647 |
| `unsigned int` | 0 ~ 4,294,967,295 |

**size_t**: 크기/인덱스 표현 타입. `sizeof`의 반환 타입. `#include <stddef.h>`에 정의.

**libsbs 연결**:
```c
void *memset(void *s, int c, size_t n);  /* man 3 memset */
size_t strlen(const char *s);            /* man 3 strlen */
```

---

### 4. 변수 선언과 초기화

```c
/* 선언만 — 쓰레기값 주의! */
int x;

/* 선언 + 초기화 — 올바른 방법 */
int    score = 100;
char   grade = 'A';
double pi    = 3.14159;

/* const: 값이 변하지 않는 변수 */
const int    MAX = 1024;
const double PI  = 3.141592653589793;
```

> 초기화되지 않은 변수를 사용하면 `-Wuninitialized` 경고 → `-Werror`로 컴파일 실패

---

### 5. 산술 연산자

```c
int a = 17, b = 5;

a + b   // 22
a - b   // 12
a * b   // 85
a / b   // 3  ← 정수 나눗셈! 소수점 버림
a % b   // 2  ← 나머지
```

**정수 나눗셈 → 실수 나눗셈**:
```c
double r = (double)a / b;  // 3.4
```

---

### 6. 증감 / 대입 연산자

```c
int a = 5;

a++;     // 후위: 현재 값 사용 후 증가
++a;     // 전위: 먼저 증가 후 사용

x += 5;  // x = x + 5
x -= 3;  // x = x - 3
x *= 2;  // x = x * 2
x /= 4;  // x = x / 4
x %= 3;  // x = x % 3
```

---

### 7. 비교 / 논리 연산자

**비교 연산자** — 결과는 1(참) 또는 0(거짓):

| 연산자 | 의미 |
|--------|------|
| `==` | 같음 |
| `!=` | 다름 |
| `>` `<` `>=` `<=` | 크기 비교 |

**논리 연산자**:
```c
x && y   // AND: 둘 다 참이어야 참
x || y   // OR:  하나라도 참이면 참
!x       // NOT: 반전
```

---

### 8. 연산자 우선순위

높은 순서: `()` → `! ++ --` → `* / %` → `+ -` → `< > <= >=` → `== !=` → `&&` → `||` → `= += ...`

> 헷갈리면 괄호를 쓰세요. `2 + 3 * 4 = 14` vs `(2 + 3) * 4 = 20`

---

### 9. 형 변환

**암묵적(Implicit)** — 컴파일러 자동 변환:
```c
int    i = 10;
double d = i;    // 10 → 10.0  (안전)

double x = 3.7;
int    n = x;    // 3.7 → 3    (소수점 버림! 경고 발생)
```

**명시적(Explicit)** — 프로그래머가 직접 지정:
```c
int    a = 10, b = 3;
double r = (double)a / b;  // 3.333...

char   c = (char)65;       // 'A'
```

**libsbs에서의 캐스팅** — `sbs_memset` 예시:
```c
void *sbs_memset(void *s, int c, size_t n)
{
    unsigned char *ptr = (unsigned char *)s;
    while (n--)
        *ptr++ = (unsigned char)c;
    return (s);
}
```

---

### 10. ASCII — 문자와 숫자의 관계

| 범위 | 문자 | 의미 |
|------|------|------|
| 0–31, 127 | 제어 문자 | 출력 불가 |
| 32–126 | 출력 가능 | isprint 범위 |
| 48–57 | '0'–'9' | 숫자 문자 |
| 65–90 | 'A'–'Z' | 대문자 |
| 97–122 | 'a'–'z' | 소문자 |

**자주 쓰는 패턴**:
```c
c >= 'A' && c <= 'Z'   // 대문자 판별
c + 32                 // 대 → 소 변환
'5' - '0'              // 숫자 문자 → 정수 (atoi의 핵심)
```

---

## 실습 코드

**calculator.c 핵심 부분**:
```c
int    a = 17;
int    b = 5;
double result_real = (double)a / b;

printf("나눗셈(정수): %d / %d = %d\n",   a, b, a / b);       // 3
printf("나눗셈(실수): %d / %d = %.6f\n", a, b, result_real); // 3.400000
```

**temperature.c 핵심 부분**:
```c
double c = 100.0;
double f = c * 9.0 / 5.0 + 32;  // 212.0

double fahr = 212.0;
double cel  = (fahr - 32) * 5.0 / 9.0;  // 100.0
```

---

## 실행 전 체크리스트

- [ ] `sizeof` 출력 시 `%zu` 서식 지정자를 사용했는가?
- [ ] 정수 나눗셈 결과가 예상과 같은가? (소수점 버림 확인)
- [ ] 실수 나눗셈 시 `(double)` 캐스팅을 붙였는가?
- [ ] 초기화 없이 사용한 변수가 없는가?
- [ ] `-Wall -Wextra -Werror` 경고 없이 컴파일되는가?

---

## 다음 차시 예고

- **3차시: 조건문과 반복문**
- `if / else if / else`, `switch`
- `for`, `while`, `do-while`, `break`, `continue`
- 실습: 구구단 출력, FizzBuzz, 숫자 맞추기 게임

---

## 트러블슈팅

| 증상 | 확인 사항 |
|------|----------|
| `%zu` 관련 경고 | `sizeof` 출력엔 `%d` 말고 `%zu` 사용 |
| 나눗셈 결과가 정수로 나옴 | `int / int = int`. `(double)a / b` 형태로 수정 |
| `-Wconversion` 경고 | `double → int` 대입 시 `(int)` 명시적 캐스팅 추가 |
| `uninitialized variable` 경고 | 변수 선언 시 반드시 초기화 |
| sizeof(long)이 4로 나옴 | 32비트 환경. Codespaces(64비트)에서는 8B |
