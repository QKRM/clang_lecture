# 13차시 실습 - 문자열 함수 II

## 실습 목표

- `sbs_strchr`, `sbs_strrchr`로 순/역방향 문자 검색을 구현한다.
- `sbs_strnstr`로 부분 문자열을 길이 제한 안에서 검색한다.
- 엣지 케이스(빈 needle, \0 검색, 범위 경계)를 처리한다.


> **금지**: `<string.h>`, `<strings.h>`. 직접 구현해야 합니다.

---

## 준비: libsbs.h에 추가

```c
char	*sbs_strchr(const char *s, int c);
char	*sbs_strrchr(const char *s, int c);
char	*sbs_strnstr(const char *big, const char *little, size_t len);
```

---

## 과제 1: sbs_strchr

`sbs_strchr.c` — `s`에서 `c`를 앞에서부터 찾아 위치 반환, 못 찾으면 NULL.

요구사항:
- `(char)c`로 비교
- **`\0` 검색 처리**: `c`가 `\0`이면 문자열 끝 위치 반환
- 반환은 `(char *)` 캐스팅

힌트:
```c
while (s[i])
{
    if (s[i] == (char)c)
        return ((char *)(s + i));
    i++;
}
if ((char)c == '\0')
    return ((char *)(s + i));
return (NULL);
```

> `strchr(s, '\0')`은 문자열 끝의 \0 위치를 반환합니다(표준 동작). 빠뜨리기 쉬움.

---

## 과제 2: sbs_strrchr

`sbs_strrchr.c` — `c`를 뒤에서부터 찾아 **마지막 등장** 위치 반환.

요구사항:
- 먼저 `\0`까지 이동
- `\0` 검색이면 끝 위치 반환
- 뒤에서부터 내려오며 첫 일치 반환

힌트:
```c
while (s[i]) i++;          // 끝으로
if ((char)c == '\0')
    return ((char *)(s + i));
while (i > 0)
{
    i--;
    if (s[i] == (char)c)
        return ((char *)(s + i));
}
return (NULL);
```

---

## 과제 3: sbs_strnstr

`sbs_strnstr.c` — `big`에서 `little`을 `len`바이트 범위 안에서 검색.

요구사항:
- 빈 `little`이면 `big` 반환
- 이중 루프(바깥 시작위치 i, 안쪽 비교 j)
- `i + j < len`으로 범위 초과 방지
- `little[j] == '\0'`이면 발견

힌트:
```c
if (little[0] == '\0')
    return ((char *)big);
while (big[i] && i < len)
{
    j = 0;
    while (big[i + j] && i + j < len && big[i + j] == little[j])
        j++;
    if (little[j] == '\0')
        return ((char *)(big + i));
    i++;
}
return (NULL);
```

> 엣지 케이스: needle이 끝에 걸쳐 len을 넘으면 못 찾은 것. 빈 needle은 즉시 big.

---

## 과제 4: 채점 + 엣지 케이스

```bash
$ bash grade.sh
=== libsbs 13차시 채점 ===
✓ sbs_strchr    (...)
✓ sbs_strrchr   (...)
✓ sbs_strnstr   (...)
결과: 3 / 3 통과
```

직접 확인할 엣지 케이스:
- `strchr(s, '\0')` → 끝의 \0 위치
- `strrchr("hello", 'l')` → 마지막 l (index 3)
- `strnstr("abc", "", 3)` → "abc" (빈 needle)
- `strnstr("abc", "abcd", 10)` → NULL (needle이 더 김)

---

## 제출 확인 사항

- [ ] `libsbs.h`에 3개 프로토타입 추가
- [ ] `sbs_strchr.c` - 순방향, \0 검색 처리
- [ ] `sbs_strrchr.c` - 역방향, 마지막 등장
- [ ] `sbs_strnstr.c` - len 범위, 빈 needle 처리
- [ ] `<string.h>` 미사용
- [ ] `bash grade.sh` → 3 / 3 통과

---

## 더 생각해볼 거리

1. `strchr`가 `\0`을 찾을 수 있어야 하는 이유는? (문자열 끝 위치를 얻으려고)
2. `strrchr`를 앞에서부터 돌면서도 구현할 수 있을까? (마지막 일치를 변수에 기억)
3. `strnstr`의 `n`이 `strstr`과 다른 점은? (검색 범위를 len으로 제한)
