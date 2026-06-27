# 13차시 강의 노트 - 문자열 함수 II (strchr, strrchr, strnstr)

## 학습 목표

1. `sbs_strchr`로 문자를 순방향 검색하고 `\0` 처리를 이해한다.
2. `sbs_strrchr`로 문자를 역방향 검색할 수 있다.
3. `sbs_strnstr`로 부분 문자열을 길이 제한 안에서 검색할 수 있다.
4. 검색 알고리즘의 엣지 케이스를 처리할 수 있다.

---

## 1부: sbs_strchr — 순방향 검색

`s`에서 문자 `c`를 **앞에서부터** 찾아 그 위치 포인터를 반환. 못 찾으면 `NULL`.

```c
char *sbs_strchr(const char *s, int c)
{
    size_t i = 0;
    while (s[i])
    {
        if (s[i] == (char)c)
            return ((char *)(s + i));
        i++;
    }
    if ((char)c == '\0')           // \0도 검색 대상!
        return ((char *)(s + i));
    return (NULL);
}
```

핵심 포인트:
- `c`를 `(char)`로 캐스팅해 비교
- **`\0` 검색**: `c`가 `\0`이면 문자열 끝의 `\0` 위치를 반환(표준 동작)
- 반환 타입은 `char *`지만 입력은 `const char *` → `(char *)` 캐스팅

> `memchr`(11차시)와 달리 길이가 아니라 `\0`까지 봅니다.

---

## 2부: sbs_strrchr — 역방향 검색

`s`에서 `c`를 **뒤에서부터** 찾습니다. 즉 **마지막으로 나타나는** 위치를 반환.

```c
char *sbs_strrchr(const char *s, int c)
{
    size_t i = 0;
    while (s[i])                   // 먼저 끝까지 이동
        i++;
    if ((char)c == '\0')           // \0이면 끝 위치
        return ((char *)(s + i));
    while (i > 0)                  // 뒤에서부터
    {
        i--;
        if (s[i] == (char)c)
            return ((char *)(s + i));
    }
    return (NULL);
}
```

핵심 포인트:
- 먼저 `\0`까지 이동(끝 인덱스 확보)
- `\0` 검색이면 끝 위치 반환
- 뒤에서부터 내려오며 첫 일치 = 마지막 등장

| 함수 | 방향 | 결과 |
|------|------|------|
| `strchr` | 앞 → 뒤 | 첫 번째 등장 |
| `strrchr` | 뒤 → 앞 | 마지막 등장 |

---

## 3부: sbs_strnstr — 부분 문자열 검색

`big`에서 `little`(부분 문자열)을 **`len`바이트 범위 안에서** 찾습니다.

```c
char *sbs_strnstr(const char *big, const char *little, size_t len)
{
    size_t i;
    size_t j;

    if (little[0] == '\0')          // 빈 needle이면 big 반환
        return ((char *)big);
    i = 0;
    while (big[i] && i < len)
    {
        j = 0;
        while (big[i + j] && i + j < len && big[i + j] == little[j])
            j++;
        if (little[j] == '\0')      // little 끝까지 일치 = 찾음
            return ((char *)(big + i));
        i++;
    }
    return (NULL);
}
```

핵심 포인트:
- **빈 little**: 즉시 `big` 반환(표준 동작)
- 이중 루프: 바깥은 시작 위치 `i`, 안쪽은 일치 검사 `j`
- `i + j < len` 으로 범위를 넘지 않음(strnstr의 n)
- `little[j] == '\0'`이면 little 전체가 일치 = 발견

> `man 3 strnstr` 참고. 엣지 케이스(빈 needle, len이 짧을 때, needle이 끝에 걸칠 때)를 꼭 테스트하세요.

---

## 4부: 채점

`strchr`/`strrchr`는 표준과 비교, `strnstr`은 BSD 함수라 테스트 안의 정답 동작과 비교합니다.

```bash
$ bash grade.sh
✓ sbs_strchr    (...)
✓ sbs_strrchr   (...)
✓ sbs_strnstr   (...)
결과: 3 / 3 통과
```

---

## 핵심 정리

1. `strchr`는 순방향(첫 등장), `\0`도 검색 대상
2. `strrchr`는 역방향(마지막 등장), 먼저 끝까지 이동 후 내려옴
3. 두 함수 모두 `(char)c`로 비교, `(char *)` 캐스팅 반환
4. `strnstr`는 `len` 범위 안에서 부분 문자열 검색
5. 빈 `little`이면 `big`을 그대로 반환
6. 이중 루프 + `i + j < len`으로 범위 안전

---

## 다음 차시 예고

14차시에서는 문자열 함수 III(`sbs_strncmp`, `sbs_atoi`, `sbs_strdup`)를 구현합니다. 문자열 비교, 문자열→정수 변환(부호·공백·오버플로 처리), 동적 메모리로 문자열 복제를 다룹니다.
