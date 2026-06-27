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

## 과제 4: 채점 + 버퍼 안전성 테스트

```bash
$ bash grade.sh
=== libsbs 12차시 채점 ===
✓ sbs_strlen    (...)
✓ sbs_strlcpy   (...)
✓ sbs_strlcat   (...)
결과: 3 / 3 통과
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

- [ ] `libsbs.h`에 3개 프로토타입 추가
- [ ] `sbs_strlen.c` - `\0`까지, size_t 반환
- [ ] `sbs_strlcpy.c` - dstsize-1 복사, src 길이 반환, dstsize==0 처리
- [ ] `sbs_strlcat.c` - dst 뒤 이어붙이기, 반환값 규칙
- [ ] `<string.h>` 미사용
- [ ] `bash grade.sh` → 3 / 3 통과

---

## 더 생각해볼 거리

1. strlcpy 반환값이 "복사한 수"가 아니라 "src 길이"인 이유는? (잘림을 감지하려고)
2. strlcat에서 dst 길이를 dstsize로 제한해 측정하는 이유는? (\0 없는 버퍼 방어)
3. strcpy 대신 strlcpy를 쓰면 어떤 보안 문제를 막을까? (버퍼 오버플로우)
