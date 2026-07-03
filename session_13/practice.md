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

---

## 도전 과제 (필수 4개를 마친 사람만)

시간이 남으면 아래 순서대로 도전하세요. 정답 예시는 이 페이지 맨 아래 "정답 코드"에서 확인할 수 있습니다.

### 도전 1: 미니 프로젝트 — 단어 검색기 (word_finder.c)

방금 만든 `sbs_strnstr`을 반복 호출해 문자열 안에서 특정 단어가 **등장하는 모든 위치**를 찾아 출력하는 프로그램을 작성하세요.

요구사항:
- `char *text`, `char *word` 두 문자열을 코드 안에 준비(하드코딩 가능)
- `sbs_strnstr`로 찾은 위치부터 `sbs_strlen(text) - (찾은 위치 - text)`를 남은 길이로 다음 검색 시작
- 겹치지 않게: 찾으면 `찾은 위치 + strlen(word)`부터 다시 검색
- 출력 예: `"is"를 3번 찾음: 인덱스 2, 5, 21`
- 못 찾으면 "찾지 못함" 출력

### 도전 2: 미니 프로젝트 — 파일 경로 분리기 (file_ext.c)

`"/home/user/report.final.txt"` 같은 경로 문자열에서 **파일명**과 **확장자**를 분리해 출력하세요.

요구사항:
- `sbs_strrchr(path, '/')`로 마지막 `/` 찾기 → 그 다음이 파일명
- `sbs_strrchr(filename, '.')`로 마지막 `.` 찾기 → 그 다음이 확장자(`.`이 없으면 "확장자 없음")
- 경로에 `/`가 없는 경우(`"report.txt"`)도 처리
- 출력 예: `파일명: report.final.txt, 확장자: txt`

### 도전 3: 심화 함수 — sbs_strcasestr

대소문자를 무시하고 부분 문자열을 찾는 `sbs_strcasestr`을 구현하세요. [advanced.md](advanced.md)를 참고하세요. 힌트: `sbs_strnstr`과 구조는 같고, 비교할 때 두 글자를 소문자로 맞춰 비교합니다(12차시 `sbs_strcasecmp`의 `to_lower` 헬퍼와 같은 방식).

### 도전 4: 짝 코드 리뷰

옆 사람과 `sbs_strchr.c`/`sbs_strrchr.c`/`sbs_strnstr.c`를 서로 바꿔서 `session_16/CODE_REVIEW.md` 체크리스트로 리뷰하세요.

- 엣지 케이스(빈 문자열, `\0` 검색, `len=0`)를 놓치지 않았는지 질문형으로 코멘트
- 좋은 점 최소 1개 언급
- 리뷰 받은 내용으로 자기 코드를 한 번 고쳐보기
