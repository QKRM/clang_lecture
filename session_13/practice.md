# 13차시 실습 - 문자열 함수 II

## 실습 목표

- `sbs_strchr`, `sbs_strrchr`로 순/역방향 문자 검색을 구현한다.
- `sbs_strnstr`로 부분 문자열을 길이 제한 안에서 검색한다.
- 엣지 케이스(빈 needle, \0 검색, 범위 경계)를 처리한다.

**진행 순서**: 과제 1~4는 **필수**(전원 완료), 맨 아래 "도전 과제"는 필수를 끝낸 사람만 진행합니다.

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

::: hint 막히면 힌트 보기 (sbs_strchr 완성 코드)
```c
#include "libsbs.h"

char	*sbs_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	return (NULL);
}
```
:::

> `strchr(s, '\0')`은 문자열 끝의 \0 위치를 반환합니다(표준 동작). 빠뜨리기 쉬움.

---

## 과제 2: sbs_strrchr

`sbs_strrchr.c` — `c`를 뒤에서부터 찾아 **마지막 등장** 위치 반환.

요구사항:
- 먼저 `\0`까지 이동
- `\0` 검색이면 끝 위치 반환
- 뒤에서부터 내려오며 첫 일치 반환

::: hint 막히면 힌트 보기 (sbs_strrchr 완성 코드)
```c
#include "libsbs.h"

char	*sbs_strrchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])               // 먼저 끝까지 이동
		i++;
	if ((char)c == '\0')
		return ((char *)(s + i));
	while (i > 0)              // 뒤에서부터
	{
		i--;
		if (s[i] == (char)c)
			return ((char *)(s + i));
	}
	return (NULL);
}
```
:::

---

## 과제 3: sbs_strnstr

`sbs_strnstr.c` — `big`에서 `little`을 `len`바이트 범위 안에서 검색.

요구사항:
- 빈 `little`이면 `big` 반환
- 이중 루프(바깥 시작위치 i, 안쪽 비교 j)
- `i + j < len`으로 범위 초과 방지
- `little[j] == '\0'`이면 발견

::: hint 막히면 힌트 보기 (sbs_strnstr 완성 코드)
```c
#include "libsbs.h"

char	*sbs_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
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
}
```
:::

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

실패하면 `bash grade.sh -v`로 어떤 케이스에서 틀렸는지 확인하세요.

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
- [ ] (선택) 도전 과제 — `word_finder.c` / `file_ext.c` / `file_search.c` / `sbs_strcasestr.c`(BONUS 채점)

---

## 더 생각해볼 거리

1. `strchr`가 `\0`을 찾을 수 있어야 하는 이유는? (문자열 끝 위치를 얻으려고)
2. `strrchr`를 앞에서부터 돌면서도 구현할 수 있을까? (마지막 일치를 변수에 기억)
3. `strnstr`의 `n`이 `strstr`과 다른 점은? (검색 범위를 len으로 제한)
4. `printf("%s", sbs_strchr("abc", 'z'))`를 실행하면 무슨 일이? (NULL 역참조 → 크래시. 강의노트 3.7부)

---

## 도전 과제 (필수 4개를 마친 사람만)

시간이 남으면 아래 순서대로 도전하세요. 정답 예시는 이 페이지 맨 아래 "정답 코드"에서 확인할 수 있습니다.

> 스켈레톤 코드는 **TODO를 채우기 전에는 컴파일이 안 될 수 있습니다** (`-Werror`가 미사용 변수 경고를 에러로 처리). TODO를 다 채운 뒤 컴파일하세요.

### 도전 1: 미니 프로젝트 — 단어 검색기 (word_finder.c)

방금 만든 `sbs_strnstr`을 반복 호출해 문자열 안에서 특정 단어가 **등장하는 모든 위치**를 찾아 출력하는 프로그램을 작성하세요.

요구사항:
- `char *text`, `char *word` 두 문자열을 코드 안에 준비(하드코딩 가능)
- 처음엔 `text` 전체에서 검색 → 찾으면 **찾은 위치 + 단어 길이**부터 이어서 다시 검색(겹침 방지) → 못 찾을 때까지 반복
- 각 호출의 `len` 인자에는 남은 부분의 길이를 넘김
- 문자열 길이 함수: 이 폴더에는 `sbs_strlen`이 없으므로 **간단한 길이 헬퍼 함수를 직접 작성**하세요(12차시에서 만든 것과 동일한 5줄짜리)
- 못 찾으면 "찾지 못함" 출력

출력 예 (`text = "this is a test, this is only a test"`, `word = "is"`):
```
인덱스 2에서 발견
인덱스 5에서 발견
인덱스 18에서 발견
인덱스 21에서 발견
"is"를 4번 찾음
```

스켈레톤 (`word_finder.c`로 저장 후 TODO를 채우세요):
```c
#include "libsbs.h"
#include <stdio.h>

static size_t	str_len(const char *s)
{
	size_t	i;

	i = 0;
	/* TODO: \0까지 세기 (12차시 sbs_strlen과 동일) */
	return (i);
}

int	main(void)
{
	char	*text = "this is a test, this is only a test";
	char	*word = "is";
	size_t	pos;
	char	*found;
	int		count;

	pos = 0;
	count = 0;
	while (pos < str_len(text))
	{
		/* TODO 1: text + pos 부터 남은 길이만큼 sbs_strnstr로 검색 */
		found = NULL;
		if (!found)
			break ;
		/* TODO 2: 찾은 인덱스(found - text) 출력, count 증가 */
		/* TODO 3: pos를 찾은 인덱스 + 단어 길이로 이동 (겹침 방지) */
	}
	/* TODO 4: count가 0이면 "찾지 못함", 아니면 "N번 찾음" 출력 */
	return (0);
}
```

컴파일·실행:
```bash
cc -Wall -Wextra -Werror -I. word_finder.c sbs_strnstr.c -o word_finder && ./word_finder
```

### 도전 2: 미니 프로젝트 — 파일 경로 분리기 (file_ext.c)

`"/home/user/report.final.txt"` 같은 경로 문자열에서 **파일명**과 **확장자**를 분리해 출력하세요.

요구사항:
- `sbs_strrchr(path, '/')`로 마지막 `/` 찾기 → 그 다음이 파일명
- `sbs_strrchr(filename, '.')`로 마지막 `.` 찾기 → 그 다음이 확장자(`.`이 없으면 "확장자 없음")
- 경로에 `/`가 없는 경우(`"report.txt"`)도 처리
- 출력 예: `파일명: report.final.txt, 확장자: txt`

스켈레톤 (`file_ext.c`로 저장 후 TODO를 채우세요):
```c
#include "libsbs.h"
#include <stdio.h>

int	main(void)
{
	char	*path = "/home/user/report.final.txt";
	char	*slash;
	char	*dot;
	char	*filename;

	/* TODO 1: sbs_strrchr로 마지막 '/' 찾기 */
	slash = NULL;
	/* TODO 2: slash가 있으면 파일명은 slash + 1, 없으면 path 전체 */
	filename = path;
	/* TODO 3: filename에서 sbs_strrchr로 마지막 '.' 찾기 */
	dot = NULL;
	/* TODO 4: dot 있으면 "파일명: ..., 확장자: ..." / 없으면 "확장자 없음" 출력 */
	return (0);
}
```

컴파일·실행:
```bash
cc -Wall -Wextra -Werror -I. file_ext.c sbs_strrchr.c -o file_ext && ./file_ext
```

### 도전 3: 미니 프로젝트 — 파일에서 내용 찾기 (file_search.c)

강의노트 0.5부에서 배운 `open`/`read`/`close`로 **실제 파일**을 읽어, 그 안에서 단어를 검색하세요. 도전 1(단어 검색기)의 파일 버전입니다.

먼저 검색 대상 파일을 만드세요 (폴더에 `sample.txt`로 저장):
```
C is fun. Searching text is a core skill.
A search function finds a needle in a haystack.
This file is the haystack for your search program.
```

요구사항:
- `open("sample.txt", O_RDONLY)`으로 열기, 실패(`fd < 0`) 시 에러 출력 후 종료
- `read`로 버퍼에 읽고 **`buf[n] = '\0'`으로 직접 문자열화** (0.5부 핵심 포인트)
- 도전 1과 같은 방식으로 `sbs_strnstr` 반복 호출 → 모든 등장 인덱스 출력
- `<fcntl.h>`, `<unistd.h>` 사용 가능 (`<string.h>`는 여전히 금지)

스켈레톤 (`file_search.c`로 저장 후 TODO를 채우세요):
```c
#include "libsbs.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 4096

int	main(void)
{
	char	buf[BUF_SIZE];
	char	*word = "is";
	ssize_t	n;
	int		fd;

	/* TODO 1: sample.txt를 O_RDONLY로 열고, 실패하면 에러 출력 후 return 1 */
	fd = -1;
	/* TODO 2: read로 최대 BUF_SIZE - 1 바이트 읽고 close */
	n = 0;
	/* TODO 3: buf[n] = '\0' 으로 문자열화 */
	/* TODO 4: 도전 1(word_finder)과 같은 반복 검색 루프 */
	return (0);
}
```

컴파일·실행:
```bash
cc -Wall -Wextra -Werror -I. file_search.c sbs_strnstr.c -o file_search && ./file_search
```

출력 예 (위 sample.txt 기준):
```
인덱스 2에서 발견
인덱스 25에서 발견
인덱스 92에서 발견
인덱스 100에서 발견
"is"를 4번 찾음
```

> 더 해보기: `word`를 `"haystack"`으로 바꾸면? 파일이 없을 때(`sample.txt` 삭제 후 실행) 에러 처리가 잘 되는지도 확인하세요.

### 도전 4: 심화 함수 — sbs_strcasestr

대소문자를 무시하고 부분 문자열을 찾는 `sbs_strcasestr`을 구현하세요. [advanced.md](advanced.md)를 참고하세요. 힌트: `sbs_strnstr`과 구조는 같고, 비교할 때 두 글자를 소문자로 맞춰 비교합니다(12차시 `sbs_strcasecmp`의 `to_lower` 헬퍼와 같은 방식).

스켈레톤 (`sbs_strcasestr.c`로 저장 후 TODO를 채우세요):
```c
#include "libsbs.h"

static int	to_lower(int c)
{
	/* TODO: 'A'~'Z'면 +32, 아니면 그대로 (12차시 strcasecmp와 동일) */
	return (c);
}

char	*sbs_strcasestr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	/* TODO 1: 빈 little이면 big 반환 */
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		/* TODO 2: sbs_strnstr의 안쪽 루프와 같되,
		           비교만 to_lower(...) == to_lower(...)로 */
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
```

`sbs_strcasestr.c` 파일을 만들면 `bash grade.sh`가 자동으로 BONUS 섹션에서 채점합니다.
