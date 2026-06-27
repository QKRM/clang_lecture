# 9차시 실습 - 헤더 파일 + 문자 분류 함수 구현

## 실습 목표

- `libsbs.h`를 직접 작성한다 (인클루드 가드 + 7개 프로토타입).
- 문자 분류·변환 함수 7개를 구현한다.
- `bash grade.sh`로 표준 함수와 비교해 자동 채점한다.


> **표준 헤더 우회 금지**: `<ctype.h>`를 include하거나 표준 `isalpha` 등을 호출하면 안 됩니다. 직접 구현해야 합니다. 채점 스크립트가 검사합니다.

---

## 준비: 파일 구조 확인

```
session_09/
├── libsbs.h            ← 직접 작성
├── sbs_isalpha.c       ← 직접 작성 (7개)
├── sbs_isdigit.c
├── sbs_isalnum.c
├── sbs_isascii.c
├── sbs_isprint.c
├── sbs_toupper.c
├── sbs_tolower.c
├── grade.sh            ← 제공됨 (수정 금지)
└── tests/              ← 제공됨 (수정 금지)
```

---

## 과제 1: libsbs.h 작성

`libsbs.h` 파일을 만들고 인클루드 가드와 7개 함수 프로토타입을 작성하세요.

요구사항:
- 인클루드 가드 `#ifndef LIBSBS_H / #define LIBSBS_H / #endif`
- 7개 함수 선언 (모두 `int` 반환, `int c` 매개변수)

작성 예시:
```c
#ifndef LIBSBS_H
# define LIBSBS_H

int   sbs_isalpha(int c);
int   sbs_isdigit(int c);
int   sbs_isalnum(int c);
int   sbs_isascii(int c);
int   sbs_isprint(int c);
int   sbs_toupper(int c);
int   sbs_tolower(int c);

#endif
```

> 각 .c 파일은 첫 줄에 `#include "libsbs.h"`를 넣습니다.

---

## 과제 2: sbs_isalpha

`sbs_isalpha.c` — 알파벳(a-z, A-Z)이면 0이 아닌 값, 아니면 0.

```c
#include "libsbs.h"

int sbs_isalpha(int c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
```

검증: `man 3 isalpha`로 표준 명세 확인.

---

## 과제 3: sbs_isdigit

`sbs_isdigit.c` — 숫자 문자(0-9)이면 참.

힌트:
```c
return (c >= '0' && c <= '9');
```

---

## 과제 4: sbs_isalnum

`sbs_isalnum.c` — 알파벳 또는 숫자이면 참. **이미 만든 함수를 재사용**하세요.

힌트:
```c
return (sbs_isalpha(c) || sbs_isdigit(c));
```

> 작은 함수를 조합하는 연습. `sbs_isalpha`, `sbs_isdigit`는 같은 헤더로 선언되어 있어 바로 호출 가능.

---

## 과제 5: sbs_isascii / sbs_isprint

`sbs_isascii.c` — ASCII 범위(0~127)이면 참.
`sbs_isprint.c` — 출력 가능 문자(32~126)이면 참.

힌트:
```c
/* isascii */ return (c >= 0 && c <= 127);
/* isprint */ return (c >= 32 && c <= 126);
```

> 경계값 주의: 127은 ascii지만 print 아님(제어 문자 DEL). 32(공백)는 print.

---

## 과제 6: sbs_toupper / sbs_tolower

`sbs_toupper.c` — 소문자면 대문자로, **아니면 원래 값 그대로**.
`sbs_tolower.c` — 대문자면 소문자로, **아니면 원래 값 그대로**.

힌트:
```c
int sbs_toupper(int c)
{
    if (c >= 'a' && c <= 'z')
        return (c - 32);
    return (c);   // 대상 아니면 그대로!
}
```

> **자주 실수**: 변환 대상이 아닐 때 그대로 반환하는 `return (c);`를 빠뜨림. 숫자·기호도 그대로 나와야 표준과 일치.

---

## 과제 7: 채점 실행

모든 함수를 구현했으면 채점 스크립트를 돌립니다.

```bash
$ bash grade.sh
```

> zip으로 받았다면 `bash grade.sh`로 실행하세요(실행 권한이 없어도 `bash`로 직접 돌리면 됩니다). `./grade.sh`로 쓰고 싶으면 `chmod +x grade.sh` 한 번 실행.

출력 예시:
```
=== libsbs 9차시 채점 ===
✓ sbs_isalpha   (256/256)
✓ sbs_isdigit   (256/256)
✓ sbs_isalnum   (256/256)
✓ sbs_isascii   (256/256)
✓ sbs_isprint   (256/256)
✓ sbs_toupper   (256/256)
✓ sbs_tolower   (256/256)
결과: 7 / 7 통과
```

실패하면 상세 확인:
```bash
$ bash grade.sh -v
✗ sbs_toupper   (254/256)
  입력 'a'(97): 기대 65, 실제 97   ← return (c - 32) 빠짐?
```

---

## 제출 확인 사항

- [ ] `libsbs.h` - 인클루드 가드 + 7개 프로토타입
- [ ] `sbs_isalpha.c` ~ `sbs_tolower.c` - 7개 파일
- [ ] 각 .c 첫 줄에 `#include "libsbs.h"`
- [ ] `<ctype.h>` 등 표준 헤더로 우회하지 않았는가?
- [ ] `bash grade.sh` → 7 / 7 통과
- [ ] 변환 함수가 대상 아닌 값을 그대로 반환하는가?

---

## 심화 과제 (선택) — fd 출력 함수

기본 7개를 끝냈으면 [advanced.md](advanced.md)의 fd 출력 함수에 도전하세요. `write` 시스템 콜과 재귀를 씁니다.

- `sbs_putchar_fd(char c, int fd)` — fd에 한 글자
- `sbs_putstr_fd(char *s, int fd)` — fd에 문자열 (NULL 방어)
- `sbs_putnbr_fd(int n, int fd)` — fd에 정수 (재귀, **INT_MIN 함정** 주의)

가장 어려운 부분은 `sbs_putnbr_fd`의 `INT_MIN(-2147483648)` 처리입니다. `-n`이 오버플로 나므로 `long`으로 받아야 합니다(advanced.md 참고).

```bash
$ bash grade.sh
=== libsbs 9차시 채점 ===
✓ sbs_isalpha   (256/256)
...
결과: 7 / 7 통과
--- BONUS (심화) ---
✓ sbs_putchar_fd   (1/1)
✓ sbs_putstr_fd    (1/1)
✓ sbs_putnbr_fd    (6/6)
보너스: 3 / 3 통과
```

> 심화는 `<unistd.h>`(write) 허용. 기본 7개는 여전히 `<ctype.h>` 금지.

---

## 더 생각해볼 거리

1. `sbs_isalnum`이 `sbs_isalpha`를 호출할 수 있는 이유는? (같은 헤더에 선언 → 컴파일러가 안다)
2. 표준 `isalpha`는 음수나 256 이상 입력에 어떻게 동작할까? (`man 3 isalpha`의 주의사항)
3. 인클루드 가드가 없으면 어떤 에러가 날까? (중복 선언 — 직접 빼고 실험해보기)
4. `sbs_putnbr_fd`에서 `long`을 안 쓰면 어떤 입력에서 깨질까? (`-2147483648` — `-n`이 int 범위 초과)
