# 11차시 실습 - 동적 메모리와 malloc

## 실습 목표

- `malloc` / `free`로 동적 메모리를 다룬다.
- `sbs_calloc`(0 초기화 할당)을 구현한다.
- `malloc`으로 **새 문자열을 만드는** 함수 `substr`, `strjoin`, `itoa`를 구현한다.
- `valgrind`로 메모리 누수를 점검한다.


> **금지**: `<string.h>`, `<strings.h>`. 동적 메모리에 필요한 `<stdlib.h>`(malloc/free)는 허용.

---

## 준비: libsbs.h에 추가

```c
void	*sbs_calloc(size_t count, size_t size);
char	*sbs_substr(char const *s, unsigned int start, size_t len);
char	*sbs_strjoin(char const *s1, char const *s2);
char	*sbs_itoa(int n);
char	*sbs_strdup(const char *s);
```

> 의존 함수 `sbs_memset`(calloc용), `sbs_strlen`(substr/strjoin용)도 같은 폴더에 둡니다(제공됨).

---

## 과제 1: sbs_calloc

`sbs_calloc.c` — `count × size`바이트 할당 + 0 초기화.

요구사항:
- 곱셈 오버플로 방어 (`total / count != size`면 NULL)
- `malloc` 실패 시 NULL
- `sbs_memset`으로 0 초기화

힌트:
```c
#include <stdlib.h>

total = count * size;
if (count != 0 && total / count != size)
    return (NULL);
ptr = malloc(total);
if (ptr == NULL)
    return (NULL);
sbs_memset(ptr, 0, total);
return (ptr);
```

---

## 과제 2: sbs_substr

`sbs_substr.c` — `s`의 `start`부터 최대 `len`글자를 새 메모리에 복제.

요구사항:
- `s`가 NULL이면 NULL
- `start`가 문자열 길이 이상이면 빈 문자열(`""`)
- `len`이 남은 길이보다 크면 끝까지만
- `malloc(len + 1)` (\0 자리)

힌트:
```c
slen = sbs_strlen(s);
if (start >= slen)
    len = 0;
else if (len > slen - start)
    len = slen - start;
sub = malloc(len + 1);
/* s[start + i]를 복사, 끝에 \0 */
```

출력 예시:
```
substr("hello world", 6, 5) → "world"
substr("hello", 10, 5)      → ""
```

---

## 과제 3: sbs_strjoin

`sbs_strjoin.c` — 두 문자열을 이어붙인 **새 메모리**를 만든다.

요구사항:
- `s1` 또는 `s2`가 NULL이면 NULL
- 크기 = `len(s1) + len(s2) + 1`
- 원본은 건드리지 않음

힌트:
```c
l1 = sbs_strlen(s1);
l2 = sbs_strlen(s2);
res = malloc(l1 + l2 + 1);
/* s1 복사 후 이어서 s2 복사, 끝에 \0 */
```

출력 예시:
```
strjoin("Hello, ", "world!") → "Hello, world!"
strjoin("42", "seoul")       → "42seoul"
```

> 이것이 "malloc으로 문자열 만들기"의 핵심 예제. 새 메모리에 결과를 만듭니다.

---

## 과제 4: sbs_itoa

`sbs_itoa.c` — 정수 `n`을 문자열로 변환해 새 메모리에 만든다.

요구사항:
- 음수 부호 처리
- **`INT_MIN(-2147483648)`** 까지 (long으로 받아 부호 뒤집기)
- 먼저 자릿수를 세어 정확한 크기 malloc

힌트:
```c
long nb = n;
if (nb < 0) { sign = 1; nb = -nb; }   // long이라 안전
tmp = nb;
while (tmp >= 10) { tmp /= 10; len++; }   // 자릿수
len += sign;
str = malloc(len + 1);
str[len] = '\0';
len--;
while (nb >= 10) { str[len--] = nb % 10 + '0'; nb /= 10; }
str[len] = nb + '0';
if (sign) str[0] = '-';
```

출력 예시:
```
itoa(42)          → "42"
itoa(-42)         → "-42"
itoa(-2147483648) → "-2147483648"
```

> 14차시 atoi와 정반대(문자열→숫자 vs 숫자→문자열). INT_MIN 함정도 같습니다.

---

## 과제 5: sbs_strdup

`sbs_strdup.c` — 문자열을 새 메모리에 그대로 복제한다.

요구사항:
- 길이를 재서 `malloc(len + 1)` (\0 자리)
- `malloc` 실패 시 NULL
- 복사 후 `\0` 종결, 원본과 **다른 독립 주소**

힌트:
```c
size_t len = sbs_strlen(s);
char  *dup = malloc(len + 1);
if (dup == NULL)
    return (NULL);
/* s를 dup로 한 글자씩 복사, 끝에 \0 */
```

출력 예시:
```
strdup("hello") → "hello" (원본과 다른 주소의 복사본)
strdup("")      → "" (빈 문자열도 복제)
```

> `strjoin`은 둘을 합쳐 새로, `strdup`은 하나를 그대로 새로. 둘 다 malloc 문자열 만들기.

---

## 과제 6: 채점 + 누수 점검

```bash
$ bash grade.sh
=== libsbs 11차시 채점 ===
✓ sbs_calloc    (...)
✓ sbs_substr    (6/6)
✓ sbs_strjoin   (5/5)
✓ sbs_itoa      (6/6)
✓ sbs_strdup    (5/5)
결과: 5 / 5 통과
```

메모리 누수 점검(권장):
```bash
$ valgrind --leak-check=full ./a.out    # leak 0 bytes
```

> 채점은 결과 문자열 일치 + **원본과 다른 독립 메모리**인지 확인합니다.

---

## 제출 확인 사항

- [ ] `libsbs.h`에 5개 프로토타입 추가
- [ ] `sbs_calloc.c` - 오버플로 방어 + 0 초기화
- [ ] `sbs_substr.c` - 부분 문자열, 엣지(start/len 초과)
- [ ] `sbs_strjoin.c` - 두 문자열 합쳐 새 메모리
- [ ] `sbs_itoa.c` - 숫자→문자열, INT_MIN 처리
- [ ] `sbs_strdup.c` - 문자열 복제, 독립 메모리
- [ ] 모든 malloc에 NULL 검사
- [ ] `<string.h>` 미사용 (stdlib 허용)
- [ ] `bash grade.sh` → 5 / 5 통과

---

## 더 생각해볼 거리

1. `substr`/`strjoin`이 만든 메모리는 누가 free해야 하나? (호출자)
2. `strjoin`과 12차시 `strlcat`의 차이는? (새 할당 vs 고정 버퍼)
3. `itoa`에서 `long`을 안 쓰면 어떤 입력에서 깨질까? (`-2147483648`)
4. `malloc` 후 `free`를 빠뜨리면 무슨 일이? (메모리 누수 — valgrind로 확인)
