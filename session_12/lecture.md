# 12차시 강의 노트 - 문자열 함수 I (strlen, strlcpy, strlcat)

이번 차시부터 **문자열 함수**를 만듭니다. 7차시에서 문자열은 `char` 배열 + 끝의 `\0`(null terminator)이라고 배웠죠. 오늘은 길이를 재는 `strlen`과, **버퍼를 넘지 않는 안전한** 복사·이어붙이기 `strlcpy`·`strlcat`을 구현합니다.

## 학습 목표

1. `sbs_strlen`을 구현하고 `\0` 처리를 이해한다.
2. 버퍼 오버플로우가 왜 위험한지, "버퍼 안전" 함수가 왜 필요한지 설명한다.
3. `sbs_strlcpy`의 크기 처리와 반환값을 구현한다.
4. `sbs_strlcat`의 이어붙이기와 반환값 규칙을 구현한다.
5. `sbs_strnlen`, `sbs_strncpy`, `sbs_strncat`, `sbs_strcmp`를 구현한다.

---

## 1부: sbs_strlen — 길이 재기

문자열의 길이는 `\0`(끝 표시) **직전까지의 글자 수**입니다. `\0`을 만날 때까지 한 칸씩 세면 됩니다.

```c
size_t sbs_strlen(const char *s)
{
    size_t len = 0;
    while (s[len])      // s[len]이 '\0'(=0, 거짓)이면 멈춤
        len++;
    return (len);
}
```

동작 추적 — `"cat"`:

```
s = 'c' 'a' 't' '\0'
     0   1   2    3
len=0: s[0]='c' (참) → len=1
len=1: s[1]='a' (참) → len=2
len=2: s[2]='t' (참) → len=3
len=3: s[3]='\0'(거짓) → 멈춤 → 반환 3
```

- 반환 타입은 `size_t`(부호 없는 크기 타입, 2차시)
- 원본을 읽기만 하므로 `const char *`

> 거의 모든 문자열 함수가 "길이"를 알아야 합니다. 그래서 `sbs_strlen`을 **가장 먼저 만들고**, 다른 함수들이 이걸 재사용합니다.

---

## 2부: 버퍼 오버플로우 — 왜 안전 함수가 필요한가

### 2.1 strcpy의 위험

표준 `strcpy(dst, src)`는 `dst`가 **얼마나 큰지 모릅니다.** `src`가 `dst`보다 길면, 정해진 칸을 넘어 **옆 메모리를 덮어씁니다.**

```c
char dst[4];               // 4칸짜리 버퍼
strcpy(dst, "hello");      // 'h''e''l''l''o''\0' = 6바이트!
```

```
dst 영역:  [ ][ ][ ][ ] | 옆 메모리...
복사:       h  e  l  l    o  \0   ← 4칸을 넘어 침범!
                          ↑↑ 다른 변수·데이터를 망가뜨림
```

이게 **버퍼 오버플로우**입니다. 프로그램이 갑자기 죽거나, 심하면 해커가 악용하는 **심각한 보안 취약점**이 됩니다.

### 2.2 strlcpy / strlcat의 해법

크기 인자 `dstsize`(버퍼 전체 크기)를 받아서 **절대 그 칸을 넘지 않습니다.** 그리고 항상 `\0`로 끝맺습니다(dstsize>0일 때).

| 함수 | 역할 |
|------|------|
| `strlcpy(dst, src, size)` | 안전 복사 |
| `strlcat(dst, src, size)` | 안전 이어붙이기 |

> BSD 계열에서 만든 안전 버전입니다. 게다가 반환값으로 "원래 만들려던 전체 길이"를 알려줘, **잘렸는지 감지**할 수 있습니다.

---

## 3부: sbs_strlcpy — 안전 복사

`src`를 `dst`로 복사하되 **최대 `dstsize-1`글자 + `\0`** 까지만. 반환값은 **`src`의 전체 길이**입니다.

```c
size_t sbs_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t srclen = sbs_strlen(src);
    size_t i;

    if (dstsize == 0)           // 쓸 공간이 0이면
        return (srclen);        // 아무것도 안 쓰고 길이만 반환
    i = 0;
    while (src[i] && i < dstsize - 1)   // \0 자리 한 칸 남김
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';              // 항상 끝맺음
    return (srclen);
}
```

핵심 포인트:
- **`dstsize - 1`까지만** 복사 — 마지막 한 칸은 `\0` 자리로 비워둠
- `dstsize == 0`이면 예외 처리(쓸 칸 자체가 없음)
- 반환값은 "복사한 글자 수"가 **아니라 `src` 전체 길이**

왜 반환이 src 길이? **잘림을 감지**하려고요.

```c
char buf[4];
size_t n = sbs_strlcpy(buf, "hello", 4);
// buf = "hel\0"  (3글자만 들어감)
// n   = 5        (원래 hello는 5글자였다)
if (n >= 4)        // 반환값 >= dstsize  →  잘렸다!
    printf("문자열이 잘렸습니다\n");
```

---

## 4부: sbs_strlcat — 안전 이어붙이기

`dst`의 기존 문자열 **뒤에** `src`를 이어붙입니다. 버퍼 안전. 반환값 규칙이 가장 까다롭습니다.

```c
size_t sbs_strlcat(char *dst, const char *src, size_t dstsize)
{
    size_t srclen = sbs_strlen(src);
    size_t dstlen;
    size_t i;

    if (dstsize == 0)
        return (srclen);
    dstlen = 0;
    while (dstlen < dstsize && dst[dstlen])   // dst 길이를 dstsize 안에서만 측정
        dstlen++;
    if (dstlen == dstsize)                     // dst에 \0이 없는 비정상 버퍼
        return (dstsize + srclen);
    i = 0;
    while (src[i] && dstlen + i < dstsize - 1)
    {
        dst[dstlen + i] = src[i];
        i++;
    }
    dst[dstlen + i] = '\0';
    return (dstlen + srclen);                  // 원래 만들려던 전체 길이
}
```

동작 — `dst="ab\0..."`(크기 8)에 `src="XYZ"` 이어붙이기:

```
처음:  a b \0 _ _ _ _ _      dstlen=2 (기존 길이)
이어:  a b  X Y Z \0 _ _     src를 dstlen 뒤부터
반환:  2(기존) + 3(src) = 5
```

핵심 포인트:
- dst 길이를 **`dstsize` 안에서만** 측정 (넘어가면 위험하니 안전장치)
- 만약 `dstsize` 안에 `\0`이 없으면(비정상) → `dstsize + srclen` 반환
- 정상이면 반환 = `dstlen + srclen`(원래 만들려던 전체 길이)

> `man 3 strlcat`로 반환값 규칙을 꼭 확인하세요. 두 경우(정상 / `\0` 없음)를 나눠서 처리하는 게 포인트입니다.

---

## 5부: n글자 계열 + 비교

### 5.1 sbs_strnlen — 길이를 maxlen까지만

`strlen`은 `\0`까지 끝없이 세지만, `strnlen`은 **`maxlen`을 넘지 않습니다.** 신뢰할 수 없는 입력의 길이를 잴 때 안전합니다.

```c
size_t sbs_strnlen(const char *s, size_t maxlen)
{
    size_t len = 0;
    while (len < maxlen && s[len])   // \0 만나거나 maxlen 도달하면 멈춤
        len++;
    return (len);
}
```

### 5.2 sbs_strncpy — 최대 n글자 복사

`src`를 `dst`로 **최대 n글자** 복사합니다. 표준 동작의 두 특징을 꼭 지켜야 합니다.

```c
char *sbs_strncpy(char *dst, const char *src, size_t n)
{
    size_t i = 0;
    while (i < n && src[i])     // src를 n까지 복사
    {
        dst[i] = src[i];
        i++;
    }
    while (i < n)               // src가 짧으면 남는 칸을 \0으로 채움
    {
        dst[i] = '\0';
        i++;
    }
    return (dst);
}
```

> **주의**: `strlcpy`와 다릅니다. ① src가 짧으면 남은 칸을 전부 `\0`으로 **패딩**합니다. ② src가 n 이상으로 길면 `dst`가 `\0`로 끝나지 **않을 수** 있습니다(표준 strncpy의 함정).

### 5.3 sbs_strncat — 최대 n글자 이어붙이기

`dst` 뒤에 `src`를 **최대 n글자** 붙이고, **항상 `\0`로 끝맺습니다.**

```c
char *sbs_strncat(char *dst, const char *src, size_t n)
{
    size_t dstlen = 0;
    size_t i = 0;
    while (dst[dstlen])             // dst 끝 찾기
        dstlen++;
    while (i < n && src[i])         // src를 n까지 이어붙임
    {
        dst[dstlen + i] = src[i];
        i++;
    }
    dst[dstlen + i] = '\0';         // 항상 종결
    return (dst);
}
```

### 5.4 sbs_strcmp — 문자열 비교

두 문자열을 **끝까지** 비교합니다(길이 제한 없음). 처음 다른 글자의 차이를 반환, 같으면 0.

```c
int sbs_strcmp(const char *s1, const char *s2)
{
    size_t i = 0;
    while (s1[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
```

> 14차시 `strncmp`는 n글자 제한이 있지만, `strcmp`는 `\0`까지 끝까지 봅니다. 둘 다 `unsigned char`로 비교해야 부호가 정확합니다.

---

## 6부: 채점

`strlen`/`strnlen`/`strncpy`/`strncat`/`strcmp`는 표준 함수와 직접 비교합니다. `strlcpy`/`strlcat`은 리눅스 표준 라이브러리(glibc)에 없을 수 있어 **테스트 안에 정답 동작을 구현**해 비교합니다.

```bash
$ bash grade.sh
✓ sbs_strlen    (...)
✓ sbs_strlcpy   (...)
✓ sbs_strlcat   (...)
✓ sbs_strnlen   (...)
✓ sbs_strncpy   (...)
✓ sbs_strncat   (...)
✓ sbs_strcmp    (...)
결과: 7 / 7 통과
```

> 금지: `<string.h>`, `<strings.h>`. 직접 구현해야 합니다.

---

## 핵심 정리

1. `sbs_strlen`은 `\0`까지 세고 `size_t` 반환 → 다른 함수가 재사용
2. `strcpy`는 버퍼 크기를 몰라 **버퍼 오버플로우**(보안 취약점) 위험
3. `strlcpy/strlcat`은 `dstsize`로 안전, 항상 `\0` 종결, 반환은 "만들려던 길이"
4. `strnlen`은 `maxlen`까지만 세서 안전
5. `strncpy`는 짧으면 `\0` 패딩, 길면 `\0` 안 붙을 수 있음(strlcpy와 차이)
6. `strncat`은 최대 n글자 붙이고 **항상** `\0` 종결
7. `strcmp`는 끝까지 비교(부호 의미), `unsigned char`로 비교

---

## 다음 차시 예고

13차시에서는 문자열 함수 II(`sbs_strchr`, `sbs_strrchr`, `sbs_strnstr`)를 구현합니다. 문자열에서 문자를 **순방향·역방향**으로 찾고, **부분 문자열**을 검색합니다. 오늘의 `sbs_strlen`을 계속 활용합니다.
