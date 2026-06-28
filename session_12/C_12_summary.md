# 12차시: 문자열 함수 I (strlen, strlcpy, strlcat)

## 학습 목표

1. sbs_strlen 구현 + null terminator
2. 버퍼 오버플로우 위험 이해
3. sbs_strlcpy 구현 (반환값 = src 길이)
4. sbs_strlcat 구현 (반환값 규칙)

---

## 핵심 개념

### 1. sbs_strlen

```c
size_t sbs_strlen(const char *s)
{
    size_t len = 0;
    while (s[len]) len++;
    return (len);
}
```

> `\0`까지 세고 size_t 반환. 다른 함수가 재사용.

---

### 2. 버퍼 오버플로우

```c
char dst[4];
strcpy(dst, "hello");   // 6바이트를 4바이트에! 오버플로우
```

> strcpy는 dst 크기를 모름. strlcpy/strlcat은 dstsize로 안전.

---

### 3. sbs_strlcpy

```c
size_t srclen = sbs_strlen(src);
if (dstsize == 0) return (srclen);
while (src[i] && i < dstsize - 1)
    dst[i] = src[i], i++;
dst[i] = '\0';
return (srclen);   // src 전체 길이!
```

> 최대 dstsize-1 복사 + \0. 반환 = src 길이(>= dstsize면 잘림).

---

### 4. sbs_strlcat

```c
if (dstsize == 0) return (srclen);
dstlen = 0;
while (dstlen < dstsize && dst[dstlen]) dstlen++;
if (dstlen == dstsize) return (dstsize + srclen);  // \0 없음
while (src[i] && dstlen + i < dstsize - 1)
    dst[dstlen + i] = src[i], i++;
dst[dstlen + i] = '\0';
return (dstlen + srclen);
```

> dst 길이는 dstsize 안에서만 측정. 반환 = 만들려던 전체 길이.

---

### 5. n글자 계열 + 비교

```c
/* strnlen — maxlen까지만 */
while (len < maxlen && s[len]) len++;

/* strncpy — n글자 복사 후 남으면 \0 패딩 */
while (i<n && src[i]) dst[i]=src[i], i++;
while (i<n)          dst[i]='\0', i++;

/* strncat — n글자 붙이고 항상 \0 */
while (i<n && src[i]) dst[dstlen+i]=src[i], i++;
dst[dstlen+i]='\0';

/* strcmp — 끝까지 비교 */
while (s1[i] && s1[i]==s2[i]) i++;
return ((unsigned char)s1[i] - (unsigned char)s2[i]);
```

| 함수 | 핵심 |
|------|------|
| strnlen | maxlen 초과 안 함 |
| strncpy | 짧으면 \0 패딩, 길면 종결 미보장 |
| strncat | 항상 \0 종결 |
| strcmp | 끝까지, unsigned char, 부호 의미 |

---

### 6. 대소문자 무시 비교

```c
static int to_lower(int c)
{
    if (c >= 'A' && c <= 'Z') return (c + 32);
    return (c);
}

/* strcasecmp — 끝까지, 소문자 기준 */
while (s1[i] || s2[i]) {
    if (to_lower((unsigned char)s1[i]) != to_lower((unsigned char)s2[i]))
        return (to_lower((unsigned char)s1[i]) - to_lower((unsigned char)s2[i]));
    i++;
}
return (0);

/* strncasecmp — 위와 같되 while (i < n && (s1[i] || s2[i])) */
```

| 함수 | 핵심 |
|------|------|
| strcasecmp | 소문자로 바꿔 끝까지 비교 |
| strncasecmp | 소문자 + n글자 제한 |

---

## 실행 전 체크리스트

- [ ] strlen이 size_t를 반환하는가?
- [ ] strlcpy가 dstsize==0을 처리하는가?
- [ ] strlcpy 반환값이 src 길이인가?
- [ ] strlcat이 dst 길이를 dstsize로 제한 측정하는가?
- [ ] strncpy가 남는 칸을 \0으로 패딩하는가?
- [ ] strncat이 항상 \0로 끝맺는가?
- [ ] strcmp를 unsigned char로 비교하는가?
- [ ] strcasecmp/strncasecmp가 소문자 기준으로 비교하는가?
- [ ] `bash grade.sh` → 9/9?

---

## 다음 차시 예고

- **13차시: 문자열 함수 II** (sbs_strchr, sbs_strrchr, sbs_strnstr)
- 순방향/역방향 문자 검색, 부분 문자열 검색

---

## 트러블슈팅

| 증상 | 확인 사항 |
|------|----------|
| strlcpy 반환 틀림 | 복사 수가 아니라 src 길이 |
| 버퍼 넘침 | i < dstsize - 1 조건 |
| \0 누락 | 복사 후 dst[i]='\0' |
| strlcat 반환 틀림 | dstlen + srclen, \0 없으면 dstsize+srclen |
| dstsize==0 크래시 | 예외 처리 추가 |
