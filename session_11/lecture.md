# 11차시 강의 노트 - 동적 메모리와 malloc

## 학습 목표

1. 스택과 힙의 차이, 동적 메모리가 왜 필요한지 설명할 수 있다.
2. `malloc` / `free`로 메모리를 할당하고 반환할 수 있다.
3. `sbs_calloc`(0 초기화 할당)을 구현할 수 있다.
4. `malloc`으로 **새 문자열을 만드는** 함수(`substr`, `strjoin`, `itoa`, `strdup`)를 구현할 수 있다.
5. 메모리 누수를 이해하고 `free` 책임을 설명할 수 있다.

---

## 1부: 왜 malloc인가?

### 1.1 스택의 한계

지금까지 변수는 **스택(stack)** 에 자동으로 생겼습니다.

```c
int  arr[5];          // 스택 — 크기를 컴파일 시점에 알아야 함
char buf[100];        // 스택 — 함수 끝나면 자동 사라짐
```

스택의 두 가지 한계:
1. **크기를 미리 정해야 한다** — 실행 중에 정해지는 크기를 못 다룸
2. **함수가 끝나면 사라진다** — 함수 밖으로 데이터를 못 들고 나감

```c
char *make_name(void)
{
    char name[20] = "Kim";
    return (name);     // 위험! name은 함수 끝나면 사라짐
}
```

### 1.2 힙 — 실행 중에 직접 할당

**힙(heap)** 은 실행 중에 원하는 크기를 빌리고, 다 쓰면 돌려주는 메모리 영역입니다. `malloc`으로 빌리고 `free`로 반환합니다.

```c
#include <stdlib.h>

char *p = malloc(20);   // 힙에서 20바이트 빌림
/* ... 사용 ... */
free(p);                // 다 쓰면 반환
```

| 구분 | 스택(stack) | 힙(heap) |
|------|-------------|----------|
| 크기 결정 | 컴파일 시점 | 실행 중 자유롭게 |
| 수명 | 함수 끝나면 사라짐 | `free` 할 때까지 유지 |
| 관리 | 자동 | 직접 (`malloc`/`free`) |
| 초기화 | 안 됨 | `malloc`은 안 됨 / `calloc`은 0 |

### 1.3 malloc을 쓰는 대표 상황

- **실행 중에 크기가 정해질 때**: 사용자 입력 길이만큼 버퍼
- **함수가 새 데이터를 만들어 돌려줄 때**: 문자열을 합쳐 반환(`strjoin`)
- **데이터가 함수 밖에서도 살아남아야 할 때**: 동적 배열·연결 리스트

---

## 2부: malloc / free 사용법

### 2.1 기본 패턴

```c
int *arr = malloc(sizeof(int) * 10);   // int 10개 공간
if (arr == NULL)                        // ① 실패 검사 — 항상!
    return (NULL);
/* ... 사용 ... */
free(arr);                              // ② 반환 — 안 하면 누수
arr = NULL;                             // (선택) 댕글링 방지
```

| 단계 | 설명 |
|------|------|
| `malloc(크기)` | 바이트 수를 받아 힙에서 빌림. 성공 시 시작 주소, 실패 시 `NULL` |
| NULL 검사 | 메모리가 부족하면 `NULL`. 검사 없이 쓰면 크래시 |
| `free(p)` | 빌린 메모리를 반환. 안 하면 **메모리 누수** |

### 2.2 sizeof로 크기 계산

```c
int    *a = malloc(sizeof(int) * n);     // int n개
char   *s = malloc(sizeof(char) * (len + 1));  // 문자열 (+1은 \0)
t_point *p = malloc(sizeof(t_point));    // 구조체 1개
```

> 문자열을 만들 때는 항상 **`\0` 자리 +1**을 잊지 마세요.

### 2.3 흔한 실수

```c
char *p = malloc(5);
free(p);
printf("%c", *p);   // ✗ 이미 free한 메모리 사용 (use-after-free)

free(p);
free(p);            // ✗ 두 번 free (double free) → 크래시

char *q = malloc(5);
q = malloc(5);      // ✗ 첫 메모리 주소를 잃음 → 누수
```

---

## 3부: 표준 동적 메모리 라이브러리 함수

`<stdlib.h>`에 들어 있는 동적 메모리 관련 함수들입니다. 직접 구현하기 전에 표준이 무엇을 제공하는지 알아둡니다.

| 함수 | 역할 |
|------|------|
| `malloc(size)` | size바이트 할당 (초기화 안 함) |
| `calloc(n, size)` | n×size바이트 할당 + **0으로 초기화** |
| `realloc(ptr, size)` | 기존 블록을 새 크기로 재조정 |
| `free(ptr)` | 할당 해제 |

```c
/* calloc — 0으로 초기화된 int 배열 */
int *a = calloc(10, sizeof(int));   // 전부 0

/* realloc — 배열을 키움 */
int *b = malloc(sizeof(int) * 4);
b = realloc(b, sizeof(int) * 8);    // 4 → 8칸으로 확장
```

> 오늘은 `calloc`을 직접 구현하고, `malloc`으로 **문자열을 만드는** 함수들(`substr`, `strjoin`, `itoa`)을 만듭니다. 모두 "새 메모리를 만들어 반환"하는 점이 공통입니다.

---

## 4부: 4개 함수 명세

### 4.1 sbs_calloc — 0으로 초기화된 할당

`count × size`바이트를 할당하고 0으로 채웁니다. 곱셈 오버플로를 방어합니다.

```c
void *sbs_calloc(size_t count, size_t size)
{
    void   *ptr;
    size_t  total;

    total = count * size;
    if (count != 0 && total / count != size)   // 오버플로 방어
        return (NULL);
    ptr = malloc(total);
    if (ptr == NULL)
        return (NULL);
    sbs_memset(ptr, 0, total);                  // 0 초기화 (10차시 재사용)
    return (ptr);
}
```

### 4.2 sbs_substr — 부분 문자열을 새 메모리에

문자열 `s`의 `start`부터 최대 `len`글자를 잘라 **새 메모리**에 복제합니다.

```c
char *sbs_substr(char const *s, unsigned int start, size_t len)
{
    size_t slen;
    size_t i;
    char  *sub;

    if (s == NULL)
        return (NULL);
    slen = sbs_strlen(s);
    if (start >= slen)          // 시작이 길이 넘으면 빈 문자열
        len = 0;
    else if (len > slen - start)// 남은 길이보다 크면 자름
        len = slen - start;
    sub = malloc(len + 1);      // +1은 \0
    if (sub == NULL)
        return (NULL);
    i = 0;
    while (i < len)
    {
        sub[i] = s[start + i];
        i++;
    }
    sub[i] = '\0';
    return (sub);
}
```

엣지 케이스: `start`가 길이 이상이면 `""`, `len`이 남은 길이보다 크면 끝까지만.

### 4.3 sbs_strjoin — 두 문자열을 합쳐 새 메모리에

`s1` + `s2`를 이어붙인 **새 문자열**을 만듭니다. 이것이 "malloc으로 문자열 만들기"의 대표 예입니다.

```c
char *sbs_strjoin(char const *s1, char const *s2)
{
    size_t l1, l2, i = 0, j = 0;
    char  *res;

    if (s1 == NULL || s2 == NULL)   // NULL 검사를 먼저! (안 하면 아래 strlen에서 크래시)
        return (NULL);
    l1 = sbs_strlen(s1);
    l2 = sbs_strlen(s2);
    res = malloc(l1 + l2 + 1);      // 두 길이 합 + \0
    if (res == NULL)
        return (NULL);
    while (i < l1) { res[i] = s1[i]; i++; }
    while (j < l2) { res[i + j] = s2[j]; j++; }
    res[i + j] = '\0';
    return (res);
}
```

> 원본 `s1`, `s2`는 건드리지 않고 **새 메모리**에 결과를 만듭니다. 이 함수는 12차시 `strlcat`(고정 버퍼)과 대조됩니다 — strjoin은 필요한 만큼 새로 할당.

### 4.4 sbs_itoa — 숫자를 문자열로

정수 `n`을 사람이 읽는 문자열로 만듭니다. 자릿수만큼 메모리를 할당하는 것이 핵심.

```c
char *sbs_itoa(int n)
{
    long  nb = n;
    int   sign = 0;
    int   len = 1;
    long  tmp;
    char *str;

    if (nb < 0) { sign = 1; nb = -nb; }   // INT_MIN 위해 long
    tmp = nb;
    while (tmp >= 10) { tmp /= 10; len++; }  // 자릿수 세기
    len += sign;                             // 부호 자리
    str = malloc(len + 1);
    if (str == NULL)
        return (NULL);
    str[len] = '\0';
    len--;
    while (nb >= 10) { str[len--] = nb % 10 + '0'; nb /= 10; }
    str[len] = nb + '0';
    if (sign) str[0] = '-';
    return (str);
}
```

핵심: 먼저 **자릿수를 세어** 정확한 크기를 malloc. `INT_MIN`은 `long`으로 받아 부호 처리(14차시 atoi와 같은 함정).

### 4.5 sbs_strdup — 문자열 복제

기존 문자열을 **새 메모리에 그대로 복사**해 돌려줍니다. "원본과 똑같지만 독립된 복사본"이 필요할 때 씁니다.

```c
char *sbs_strdup(const char *s)
{
    size_t len = sbs_strlen(s);
    size_t i = 0;
    char  *dup = malloc(len + 1);   // 원본 길이 + \0

    if (dup == NULL)
        return (NULL);
    while (i < len)
    {
        dup[i] = s[i];
        i++;
    }
    dup[len] = '\0';
    return (dup);
}
```

핵심 포인트:
- `malloc(len + 1)` — `\0` 자리까지 +1
- NULL 검사 필수, 복사 후 `\0` 종결
- 반환 메모리는 **원본과 다른 독립 주소** — 호출자가 free

> `strjoin`이 "두 문자열을 합쳐 새로" 만든다면, `strdup`은 "한 문자열을 그대로 새로" 만듭니다. 둘 다 malloc으로 새 메모리를 반환하는 한 묶음입니다.

---

## 5부: 메모리 누수와 free 책임

`malloc`으로 만든 메모리는 **호출자가 free**해야 합니다.

```c
char *full = sbs_strjoin("Hello, ", "world!");
printf("%s\n", full);
free(full);            // 호출자 책임!
```

누수 점검:
```bash
$ gcc -g main.c sbs_strjoin.c sbs_strlen.c -o test
$ valgrind --leak-check=full ./test    # leak 0 bytes 목표
```

> 함수가 malloc한 메모리를 누가 free할지 **문서로 명시**하는 것이 좋은 습관입니다(이 과정은 "호출자가 free").

---

## 핵심 정리

1. 스택은 크기 고정·자동 소멸, 힙은 실행 중 할당·`free`까지 유지
2. `malloc(size)` → NULL 검사 → 사용 → `free` (누수 방지)
3. 문자열 만들 때 크기는 `길이 + 1`(\0 자리)
4. `calloc`은 할당 + 0 초기화 + 오버플로 방어
5. `substr`/`strjoin`/`itoa`/`strdup`는 모두 **새 메모리를 만들어 반환**
6. malloc한 메모리는 **호출자가 free** (use-after-free·double-free·누수 주의)

---

## 다음 차시 예고

12차시부터 문자열 함수입니다. `sbs_strlen`으로 시작해 `sbs_strlcpy`, `sbs_strlcat`의 버퍼 안전 처리를 다룹니다. 오늘 만든 malloc 감각(strjoin)과 대조하며, 고정 버퍼 vs 동적 할당의 차이를 익힙니다.
