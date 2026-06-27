# 9차시: 헤더 파일 + 문자 분류 함수 구현

## 학습 목표

1. 헤더 파일(.h)의 역할과 선언/정의 분리를 설명한다
2. `#include "..."`와 `<...>`의 차이를 안다
3. 인클루드 가드로 중복 포함을 막는다
4. 문자 분류·변환 함수 7개를 구현한다
5. `bash grade.sh`로 자동 채점한다

---

## 핵심 개념

### 1. 헤더 = 선언, 소스 = 정의

```c
/* libsbs.h — 선언 */
int sbs_isalpha(int c);

/* sbs_isalpha.c — 정의 */
#include "libsbs.h"
int sbs_isalpha(int c) { ... }
```

> 함수가 많아지면 프로토타입을 헤더에 모으고, .c는 첫 줄에 그 헤더를 include.

---

### 2. include 두 형식

```c
#include <stdio.h>     // 시스템 헤더 (표준 경로)
#include "libsbs.h"    // 내 헤더 (현재 폴더 우선)
```

---

### 3. 인클루드 가드

```c
#ifndef LIBSBS_H
# define LIBSBS_H

/* 프로토타입들 */

#endif
```

> 중복 include 시 두 번째부터 건너뛰어 중복 선언 에러 방지. 세 줄이 한 세트.

---

### 4. 분류 함수 (is*)

조건 만족 → 0이 아닌 값, 아니면 0.

```c
int sbs_isalpha(int c)   // (a-z) || (A-Z)
int sbs_isdigit(int c)   // (0-9)
int sbs_isalnum(int c)   // isalpha || isdigit  ← 재사용
int sbs_isascii(int c)   // 0~127
int sbs_isprint(int c)   // 32~126
```

| 함수 | 참 범위 |
|------|---------|
| isalpha | 'a'-'z', 'A'-'Z' |
| isdigit | '0'-'9' |
| isascii | 0 ~ 127 |
| isprint | 32 ~ 126 (공백~`~`) |

---

### 5. 변환 함수

**대상이 아니면 원래 값 그대로** 반환 (핵심!).

```c
int sbs_toupper(int c)
{
    if (c >= 'a' && c <= 'z')
        return (c - 32);
    return (c);   // ← 빠뜨리지 말 것
}
/* sbs_tolower: 'A'-'Z'면 c + 32, 아니면 c */
```

---

### 6. 채점

```bash
bash grade.sh        # 요약
bash grade.sh -v     # 실패 상세
```

3단계: ①`<ctype.h>` 우회 검사 → ②`-Wall -Wextra -Werror` 컴파일 → ③libc와 0~255 전수 비교.

---

## 실행 전 체크리스트

- [ ] `libsbs.h`에 인클루드 가드 + 7개 프로토타입이 있는가?
- [ ] 각 .c 첫 줄에 `#include "libsbs.h"`가 있는가?
- [ ] `<ctype.h>`를 쓰지 않았는가?
- [ ] 변환 함수가 대상 아닌 값을 그대로 반환하는가?
- [ ] `bash grade.sh` → 7 / 7 통과?

---

## 다음 차시 예고

- **10차시: 메모리 함수 I** (`sbs_memset`, `sbs_bzero`, `sbs_memcpy`, `sbs_memccpy`)
- `void *`(범용 포인터), 바이트 단위 복사
- `libsbs.h`에 함수 계속 추가, 같은 채점 방식

---

## 트러블슈팅

| 증상 | 확인 사항 |
|------|----------|
| `libsbs.h: No such file` | .c와 같은 폴더에 헤더 있는지, `"libsbs.h"`(따옴표)인지 |
| `redefinition` / 중복 선언 | 인클루드 가드 누락 |
| 컴파일 실패(경고) | `-Werror`. 미사용 변수·초기화 누락 확인 |
| toupper가 숫자도 바꿈 | 대상 아닐 때 `return (c);` 확인 |
| 테스트 빌드 실패 | 헤더 프로토타입과 정의의 시그니처 불일치 |
| 채점이 0/7 | 파일명 정확한지 (`sbs_isalpha.c` 등) |
