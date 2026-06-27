# 10차시: 메모리 함수 I (memset, bzero, memcpy, memccpy)

## 학습 목표

1. `void *`의 개념과 캐스팅을 설명한다
2. `unsigned char *`로 바이트 단위 처리
3. `sbs_memset`, `sbs_bzero` 구현
4. `sbs_memcpy`, `sbs_memccpy` 구현 + 반환값 규칙

---

## 핵심 개념

### 1. void 포인터

```c
void *sbs_memset(void *b, int c, size_t len);
```

> 어떤 타입이든 가리킴. 역참조하려면 구체 타입으로 캐스팅. 길이는 `size_t`(`<stddef.h>`).

---

### 2. 바이트 단위 = unsigned char

```c
unsigned char *p = (unsigned char *)b;
p[i] = (unsigned char)c;
```

> char는 부호가 있어 음수 문제. unsigned char(0~255)로 캐스팅.

---

### 3. sbs_memset / sbs_bzero

```c
void *sbs_memset(void *b, int c, size_t len)
{
    unsigned char *p = (unsigned char *)b;
    size_t i = 0;
    while (i < len) { p[i] = (unsigned char)c; i++; }
    return (b);
}

void sbs_bzero(void *s, size_t n)
{
    sbs_memset(s, 0, n);   // 재사용, 반환값 없음
}
```

---

### 4. sbs_memcpy

```c
void *sbs_memcpy(void *dst, const void *src, size_t n)
{
    unsigned char       *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    size_t i = 0;
    while (i < n) { d[i] = s[i]; i++; }
    return (dst);
}
```

> src는 `const`(읽기 전용). 겹치는 영역은 미보장(→ 11차시 memmove).

---

### 5. sbs_memccpy — 반환값이 핵심

```c
while (i < n)
{
    d[i] = s[i];
    if (s[i] == (unsigned char)c)
        return (d + i + 1);   // 찾음: 다음 위치
    i++;
}
return (NULL);                // 못 찾음
```

| 상황 | 반환 |
|------|------|
| c 찾음 | dst에서 c 다음 위치 |
| 못 찾음 | NULL |

---

## 실행 전 체크리스트

- [ ] `libsbs.h`에 `<stddef.h>` + 프로토타입 추가했는가?
- [ ] `unsigned char *`로 캐스팅했는가? (char 아님)
- [ ] src를 `const`로 받았는가?
- [ ] memccpy가 찾으면 다음 위치, 못 찾으면 NULL인가?
- [ ] `<string.h>` 미사용? `bash grade.sh` → 4/4?

---

## 다음 차시 예고

- **11차시: 메모리 함수 II** (`sbs_memmove`, `sbs_memchr`, `sbs_memcmp`, `sbs_calloc`)
- 겹치는 메모리 안전 복사(memmove), malloc/free, 동적 할당(calloc)

---

## 트러블슈팅

| 증상 | 확인 사항 |
|------|----------|
| 음수 바이트 깨짐 | `char` 아니라 `unsigned char` 캐스팅 |
| memcpy 경고 (const) | src를 `const unsigned char *`로 |
| memccpy 반환 틀림 | 찾으면 `d + i + 1`, 못 찾으면 NULL |
| `size_t` 관련 에러 | `# include <stddef.h>` 추가 |
| 채점 0/4 | 파일명·헤더 추가 확인 |
