# 12차시 실습 - 문자열 함수 I

## 실습 목표

- `sbs_strlen`으로 길이를 세고 다른 함수에서 재사용한다.
- 버퍼 안전 함수 `sbs_strlcpy`, `sbs_strlcat`을 구현한다.
- `bash grade.sh`로 잘림 상황까지 자동 채점한다.


> **금지**: `<string.h>`, `<strings.h>`. 직접 구현해야 합니다.

---

## 준비: libsbs.h에 추가

```c
size_t	sbs_strlen(const char *s);
size_t	sbs_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	sbs_strlcat(char *dst, const char *src, size_t dstsize);
size_t	sbs_strnlen(const char *s, size_t maxlen);
char	*sbs_strncpy(char *dst, const char *src, size_t n);
char	*sbs_strncat(char *dst, const char *src, size_t n);
int		sbs_strcmp(const char *s1, const char *s2);
```

---

## 과제 1: sbs_strlen

`sbs_strlen.c` — `\0`까지 글자 수를 세고 `size_t` 반환.

```c
size_t	sbs_strlen(const char *s)
{
    size_t len = 0;
    while (s[len])
        len++;
    return (len);
}
```

> 7차시 길이 세기와 동일. 이후 두 함수가 이걸 재사용합니다.

---

## 과제 2: sbs_strlcpy

`sbs_strlcpy.c` — 최대 `dstsize-1`글자 복사 + `\0`. 반환값은 **src 전체 길이**.

요구사항:
- `dstsize == 0`이면 아무것도 안 쓰고 srclen 반환
- `i < dstsize - 1`로 마지막 `\0` 자리 확보
- 항상 `dst[i] = '\0'`로 종결

힌트:
```c
size_t srclen = sbs_strlen(src);
if (dstsize == 0)
    return (srclen);
while (src[i] && i < dstsize - 1)
{
    dst[i] = src[i];
    i++;
}
dst[i] = '\0';
return (srclen);
```

> 반환값이 복사한 글자 수가 아니라 **src 전체 길이**임에 주의(잘림 감지용).

---

## 과제 3: sbs_strlcat

`sbs_strlcat.c` — dst 뒤에 src 이어붙이기, 버퍼 안전.

요구사항:
- dst 길이를 **dstsize 안에서만** 측정
- dst에 `\0`이 dstsize 안에 없으면 `dstsize + srclen` 반환
- 정상: 반환값 = `dstlen + srclen`

힌트:
```c
dstlen = 0;
while (dstlen < dstsize && dst[dstlen])
    dstlen++;
if (dstlen == dstsize)
    return (dstsize + srclen);
while (src[i] && dstlen + i < dstsize - 1)
{
    dst[dstlen + i] = src[i];
    i++;
}
dst[dstlen + i] = '\0';
return (dstlen + srclen);
```

> `man 3 strlcat`로 반환값 확인. 가장 까다로운 함수입니다.

---

## 과제 4: sbs_strnlen

`sbs_strnlen.c` — 길이를 최대 `maxlen`까지만 센다.

요구사항:
- `\0`을 만나거나 `maxlen`에 도달하면 멈춤

힌트:
```c
while (len < maxlen && s[len])
    len++;
return (len);
```

---

## 과제 5: sbs_strncpy

`sbs_strncpy.c` — `src`를 `dst`로 최대 `n`글자 복사.

요구사항:
- src가 짧으면 남는 칸을 `\0`으로 패딩
- src가 n 이상이면 `\0`로 안 끝날 수 있음(표준 동작)
- `dst` 반환

힌트:
```c
while (i < n && src[i]) { dst[i] = src[i]; i++; }
while (i < n)          { dst[i] = '\0';   i++; }
return (dst);
```

> `strlcpy`와 다릅니다. strncpy는 남는 칸을 \0으로 채우고, 항상 종결을 보장하진 않습니다.

---

## 과제 6: sbs_strncat

`sbs_strncat.c` — `dst` 뒤에 `src`를 최대 `n`글자 이어붙이고 **항상 `\0` 종결**.

힌트:
```c
while (dst[dstlen]) dstlen++;       // dst 끝 찾기
while (i < n && src[i]) { dst[dstlen + i] = src[i]; i++; }
dst[dstlen + i] = '\0';
return (dst);
```

---

## 과제 7: sbs_strcmp

`sbs_strcmp.c` — 두 문자열을 끝까지 비교. 처음 다른 글자의 차이, 같으면 0.

요구사항:
- `unsigned char`로 비교(부호 정확)

힌트:
```c
while (s1[i] && s1[i] == s2[i])
    i++;
return ((unsigned char)s1[i] - (unsigned char)s2[i]);
```

출력 예시:
```
strcmp("abc", "abc") → 0
strcmp("abc", "abd") → 음수
strcmp("abd", "abc") → 양수
```

> 14차시 strncmp(n 제한)와 달리 끝까지 비교.

---

## 과제 8: 채점 + 버퍼 안전성 테스트

```bash
$ bash grade.sh
=== libsbs 12차시 채점 ===
✓ sbs_strlen    (...)
✓ sbs_strlcpy   (...)
✓ sbs_strlcat   (...)
✓ sbs_strnlen   (...)
✓ sbs_strncpy   (...)
✓ sbs_strncat   (...)
✓ sbs_strcmp    (...)
결과: 7 / 7 통과
```

실패 시 `bash grade.sh -v`로 어떤 크기/입력에서 틀렸는지 확인.

직접 실험: 작은 버퍼에 긴 문자열을 복사해 잘리는지, 반환값으로 감지되는지 확인.
```c
char buf[4];
size_t n = sbs_strlcpy(buf, "hello", 4);
/* buf = "hel\0", n = 5 (>= 4 이므로 잘림) */
```

---

## 제출 확인 사항

- [ ] `libsbs.h`에 7개 프로토타입 추가
- [ ] `sbs_strlen.c` - `\0`까지, size_t 반환
- [ ] `sbs_strlcpy.c` - dstsize-1 복사, src 길이 반환, dstsize==0 처리
- [ ] `sbs_strlcat.c` - dst 뒤 이어붙이기, 반환값 규칙
- [ ] `sbs_strnlen.c` - maxlen까지만 측정
- [ ] `sbs_strncpy.c` - n글자 복사 + \0 패딩
- [ ] `sbs_strncat.c` - n글자 이어붙이기 + \0 종결
- [ ] `sbs_strcmp.c` - 끝까지 비교, unsigned char
- [ ] `<string.h>` 미사용
- [ ] `bash grade.sh` → 7 / 7 통과

---

## 더 생각해볼 거리

1. strlcpy 반환값이 "복사한 수"가 아니라 "src 길이"인 이유는? (잘림을 감지하려고)
2. strlcat에서 dst 길이를 dstsize로 제한해 측정하는 이유는? (\0 없는 버퍼 방어)
3. strcpy 대신 strlcpy를 쓰면 어떤 보안 문제를 막을까? (버퍼 오버플로우)
