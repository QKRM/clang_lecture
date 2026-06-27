# 10차시 강의 노트 - 메모리 함수 I

이번 차시부터 **메모리를 직접 다루는** 함수를 만듭니다. 9차시 문자 함수는 글자 하나를 다뤘다면, 메모리 함수는 **바이트 덩어리**(여러 칸의 메모리)를 한꺼번에 채우고·복사하고·찾고·비교합니다. 핵심 도구는 `void *`와 `unsigned char *` 두 가지입니다.

## 학습 목표

1. `void *`(범용 포인터)가 무엇이고 왜 쓰는지 설명할 수 있다.
2. `unsigned char *`로 캐스팅해 메모리를 바이트 단위로 다룰 수 있다.
3. 채우기·복사 함수 `sbs_memset`, `sbs_bzero`, `sbs_memcpy`, `sbs_memccpy`를 구현한다.
4. 찾기·비교 함수 `sbs_memchr`, `sbs_memcmp`를 구현하고 반환값 규칙을 설명한다.

---

## 1부: void 포인터 — 타입을 가리지 않는 주소

### 1.1 왜 void* 인가?

지금까지 포인터는 항상 타입이 있었습니다. `int *`는 int를, `char *`는 char를 가리켰죠(5차시). 그런데 메모리 함수는 **무엇이든** 받아야 합니다. int 배열도, 구조체도, 문자열도 채우고 복사할 수 있어야 하니까요.

그래서 "타입을 가리지 않는 주소"인 `void *`로 받습니다.

```c
void *sbs_memset(void *b, int c, size_t len);
//          ↑ int든 구조체든 문자열이든, 그 시작 주소를 받음
```

> 비유: `void *`는 "주소만 적힌 택배 송장"입니다. 안에 뭐가 들었는지(타입)는 모르고, 위치(주소)만 압니다.

### 1.2 void*는 그대로 못 쓴다 → 캐스팅

`void *`는 무엇을 가리키는지 모르므로 **그대로 역참조하거나 인덱싱할 수 없습니다.**

```c
void *b = ...;
b[0] = 5;     // ✗ 에러! void는 "한 칸이 몇 바이트"인지 모름
```

쓰려면 **구체적 타입으로 캐스팅**해야 합니다. 메모리를 1바이트씩 다룰 거라 `unsigned char *`로 바꿉니다(2부).

### 1.3 size_t — 길이 담는 타입

메모리 함수의 길이 인자는 항상 `size_t`입니다. 크기·개수를 담는 **부호 없는 정수** 타입입니다(2차시). `<stddef.h>`에 정의돼 있어 헤더에 한 줄 추가합니다.

```c
# include <stddef.h>   // size_t 사용
```

---

## 2부: 바이트 단위로 다루기 — unsigned char

### 2.1 왜 unsigned char 인가?

메모리의 최소 단위는 **1바이트**입니다. 1바이트를 정확히 표현하는 타입이 `unsigned char`(0~255)입니다.

그냥 `char`를 쓰면 안 되나? `char`는 보통 **부호가 있어** -128~127을 표현합니다. 그러면 128 이상의 바이트(예: `0xFF`)가 **음수로 해석**되어 비교·복사에서 문제가 생깁니다.

```c
char a = 0xFF;            // 부호 있는 char에선 -1로 해석될 수 있음
unsigned char b = 0xFF;  // 255로 정확히 해석
```

그래서 메모리를 다룰 땐 **항상 `unsigned char *`로 캐스팅**합니다.

```c
unsigned char *p = (unsigned char *)b;   // void* → unsigned char*
p[i] = (unsigned char)c;                 // 한 바이트씩 채움
```

> 2차시 `sbs_memset` 미리보기에서 봤던 캐스팅이 바로 이것입니다.

### 2.2 const — "읽기만 한다"는 약속

복사·비교 함수는 원본을 **읽기만** 합니다. 그 인자에 `const`를 붙여 "여기는 안 바꾼다"고 못 박습니다(5차시 심화). 실수로 바꾸면 컴파일 에러로 막아줍니다.

```c
void *sbs_memcpy(void *dst, const void *src, size_t n);
//                          ↑ src는 읽기 전용
```

### 2.3 int c 로 받는 값

`memset`/`memccpy`/`memchr`의 "값"은 `int c`로 받지만, 실제로는 1바이트만 씁니다. 쓸 때 `(unsigned char)c`로 잘라서 사용합니다(표준 관례).

---

## 3부: 채우기·복사 함수

### 3.1 sbs_memset — 특정 값으로 채우기

`b`부터 `len`바이트를 값 `c`로 채우고, `b`를 반환합니다. 버퍼를 특정 값으로 초기화할 때 씁니다.

```c
void *sbs_memset(void *b, int c, size_t len)
{
    unsigned char *p = (unsigned char *)b;
    size_t i = 0;
    while (i < len)
    {
        p[i] = (unsigned char)c;
        i++;
    }
    return (b);     // 첫 인자를 그대로 반환
}
```

### 3.2 sbs_bzero — 0으로 채우기

`memset`의 특수형입니다. `s`부터 `n`바이트를 **0으로** 채웁니다. **반환값이 없습니다(void)**. 방금 만든 `memset`을 재사용하면 한 줄입니다.

```c
void sbs_bzero(void *s, size_t n)
{
    sbs_memset(s, 0, n);
}
```

### 3.3 sbs_memcpy — 메모리 복사

`src`에서 `dst`로 `n`바이트 복사하고 `dst`를 반환합니다.

```c
void *sbs_memcpy(void *dst, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    size_t i = 0;
    while (i < n)
    {
        d[i] = s[i];
        i++;
    }
    return (dst);
}
```

> **주의: 겹치는 영역은 보장하지 않습니다.** `dst`와 `src`가 메모리에서 겹치면(예: `dst = src + 1`) 아직 복사 안 한 칸을 먼저 덮어써 결과가 깨질 수 있습니다. 그래서 `memcpy`는 **겹치지 않는 메모리끼리만** 쓰는 게 규칙입니다.

### 3.4 sbs_memccpy — 특정 문자까지 복사

`src`를 `dst`로 복사하되, 문자 `c`를 만나면 **그 문자까지 복사한 뒤 멈춥니다.** 반환값 규칙이 헷갈리니 그림으로 봅니다.

```
src = "abcXdef",  c = 'X',  n 충분히 큼
복사:  a b c X    ← 여기까지 복사하고 멈춤
                ↑ 반환은 X "다음" 위치 (d를 가리킴)

c를 끝까지 못 찾으면 → NULL
```

```c
void *sbs_memccpy(void *dst, const void *src, int c, size_t n)
{
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    size_t i = 0;
    while (i < n)
    {
        d[i] = s[i];
        if (s[i] == (unsigned char)c)
            return (d + i + 1);   // 찾음: 그 문자 "다음" 위치
        i++;
    }
    return (NULL);                 // 못 찾음
}
```

> `man 3 memccpy`로 반환값 규칙 확인. "찾으면 다음 위치(`d + i + 1`), 못 찾으면 NULL"이 핵심.

---

## 4부: 찾기·비교 함수

### 4.1 sbs_memchr — 메모리에서 바이트 찾기

`s`부터 `n`바이트 안에서 값 `c`(바이트)를 **앞에서부터** 찾습니다.

```c
void *sbs_memchr(const void *s, int c, size_t n)
{
    const unsigned char *p = (const unsigned char *)s;
    size_t i = 0;
    while (i < n)
    {
        if (p[i] == (unsigned char)c)
            return ((void *)(p + i));   // 찾은 "그 위치" (다음 아님!)
        i++;
    }
    return (NULL);                       // n바이트 안에 없음
}
```

핵심 포인트:
- 찾으면 → **그 바이트를 가리키는 포인터** (memccpy와 달리 "다음 위치"가 아님)
- 못 찾으면 → `NULL`
- `s`는 읽기만 하므로 `const void *`. 반환은 `void *`라서 `(void *)` 캐스팅이 필요합니다.

### 4.2 sbs_memcmp — 두 메모리 비교

`s1`과 `s2`의 앞 `n`바이트를 비교합니다. 처음으로 **다른 바이트**가 나오면 그 차이를 반환하고, `n`바이트 모두 같으면 0을 반환합니다.

```c
int sbs_memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *a = (const unsigned char *)s1;
    const unsigned char *b = (const unsigned char *)s2;
    size_t i = 0;
    while (i < n)
    {
        if (a[i] != b[i])
            return ((int)a[i] - (int)b[i]);   // 차이 (부호가 의미)
        i++;
    }
    return (0);
}
```

핵심 포인트:
- 반환값의 **부호**가 중요: `s1`이 크면 양수, 작으면 음수, 같으면 0
- **반드시 `unsigned char`로 비교**: `char`로 하면 0x80 이상 바이트가 음수가 되어 대소 판정이 뒤집힙니다
- 차이값은 `(int)a[i] - (int)b[i]`로 계산

---

## 5부: 채점

`libsbs.h`의 9차시 함수 **아래에** 6개 프로토타입을 추가합니다(기존을 덮어쓰지 말 것). `size_t`를 위해 `# include <stddef.h>`도 추가.

```c
void	*sbs_memset(void *b, int c, size_t len);
void	sbs_bzero(void *s, size_t n);
void	*sbs_memcpy(void *dst, const void *src, size_t n);
void	*sbs_memccpy(void *dst, const void *src, int c, size_t n);
void	*sbs_memchr(const void *s, int c, size_t n);
int		sbs_memcmp(const void *s1, const void *s2, size_t n);
```

```bash
$ bash grade.sh        # 요약
$ bash grade.sh -v     # 실패 상세
```

채점은 표준 `memset/bzero/memcpy/memccpy/memchr/memcmp`와 **버퍼 내용 + 반환값**을 비교합니다. 여러 길이·값·정지문자 조합으로 검사합니다.

> 금지: `<string.h>`, `<strings.h>`. 직접 구현해야 합니다.

---

## 핵심 정리

1. `void *` = 타입 안 가리는 주소 → 그대로 못 쓰고 **캐스팅** 필요
2. 메모리는 **`unsigned char *`** 로 바이트 단위 처리 (char는 음수 문제)
3. `memset`은 값으로 채우고 포인터 반환, `bzero`는 0으로 채우고 반환 없음
4. `memcpy`는 n바이트 복사(겹침 미보장), `src`는 `const`(읽기 전용)
5. `memccpy`는 c를 찾으면 **다음 위치**, `memchr`는 찾으면 **그 위치**, 둘 다 못 찾으면 NULL
6. `memcmp`는 첫 다른 바이트의 차이(부호가 의미), 같으면 0 — `unsigned char`로 비교

---

## 다음 차시 예고

11차시에서는 **동적 메모리(malloc)** 를 배웁니다. 스택과 힙의 차이, `malloc`/`free`로 실행 중에 메모리를 빌리고 돌려주는 법, 그리고 `malloc`으로 **새 문자열을 만드는** 함수(`sbs_calloc`, `sbs_substr`, `sbs_strjoin`, `sbs_itoa`)를 구현합니다. 오늘 만든 `libsbs.h`에 함수를 계속 추가합니다.
