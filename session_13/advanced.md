# 13차시 심화 - 대소문자 무시 검색 (sbs_strcasestr)

> 필수 3개(strchr/strrchr/strnstr)를 끝낸 학생을 위한 심화 자료입니다. `strnstr`과 구조는 똑같고, 비교 방식만 대소문자를 무시하도록 바꿉니다. 표준 C에는 없는 GNU 확장 함수(`strcasestr`)를 `sbs_` 버전으로 만들어 봅니다.

## 심화 학습 목표

1. 대소문자를 무시하는 문자열 비교가 왜 필요한지 설명할 수 있다.
2. `sbs_strcasestr`을 `sbs_strnstr`의 구조를 재사용해 구현할 수 있다.
3. `to_lower` 헬퍼로 **비교하는 순간에만** 대소문자를 맞추는 방식을 이해한다(원본은 그대로 둠).

---

## 1. 왜 대소문자 무시 검색이 필요한가

사용자가 검색창에 `"HELLO"`를 입력해도 본문의 `"Hello"`, `"hello"`를 찾아야 하는 경우가 많습니다(파일 검색, 이메일 필터, 로그 검색 등). `strnstr`은 대소문자를 구분하므로 이럴 때 못 씁니다.

```c
sbs_strnstr("Hello World", "world", 11);      // NULL (대소문자 다름)
sbs_strcasestr("Hello World", "world", 11);   // "World" 위치 반환
```

---

## 2. sbs_strcasestr — 구현

`big`에서 `little`을 대소문자 구분 없이 `len` 범위 안에서 찾습니다. `sbs_strnstr`과 뼈대는 같고, 비교 한 줄만 `to_lower`를 거칩니다.

```c
#include "libsbs.h"

/* 9차시 sbs_tolower와 같은 원리. 13차시엔 그 파일이 없으므로 여기서 직접 변환(12차시 strcasecmp 컨벤션과 동일). */
static int	to_lower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

char	*sbs_strcasestr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] && i + j < len
			&& to_lower((unsigned char)big[i + j])
				== to_lower((unsigned char)little[j]))
			j++;
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
```

핵심 포인트:
- `sbs_strnstr`(13차시)과 이중 루프 구조가 동일 — **재사용/복붙 후 비교 줄만 수정**
- `(unsigned char)`로 캐스팅 후 소문자로 변환(부호 문제 방지, 12차시 컨벤션)
- `little`이 이미 소문자든 대문자든 상관없이 동작(양쪽 다 소문자로 맞춰 비교하므로)

---

## 3. 심화 정리

1. 대소문자 무시 검색 = 비교 순간에만 양쪽을 소문자로 맞춤
2. 알고리즘 구조는 `strnstr`과 완전히 같음 — 새로 짜지 말고 재사용
3. 12차시 `sbs_strcasecmp`와 같은 `to_lower` 헬퍼 재사용 예시

---

## 채점

필수 3개와 별도로 심화 1개를 채점합니다(`bash grade.sh`가 BONUS 섹션으로 표시).

```bash
$ bash grade.sh
=== libsbs 13차시 채점 ===
✓ sbs_strchr    (...)
✓ sbs_strrchr   (...)
✓ sbs_strnstr   (...)
결과: 3 / 3 통과
--- BONUS (심화) ---
✓ sbs_strcasestr
보너스: 1 / 1 통과
```

---

## 심화 연결 지도

| 심화 주제 | 이어지는 차시 |
|-----------|---------------|
| 대소문자 무시 비교 | 12차시 strcasecmp/strncasecmp |
| 함수 재사용 | 9차시 sbs_isalnum→isalpha+isdigit 패턴 |
| 부분 문자열 검색 | 14차시 문자열 비교(strncmp)로 이어짐 |
