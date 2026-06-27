# 7차시 실습 - 문자열과 포인터

## 실습 목표

- 포인터로 문자열을 순회하며 길이·복사·검색을 구현한다.
- 문자가 ASCII 정수임을 이용해 대소문자를 변환한다.
- 문자열을 뒤집고 글자를 세는 함수를 작성한다.


> 이번 차시는 실습 분량이 평소의 2배입니다. 기본 과제(1~6)를 먼저 끝내고, 시간이 남으면 심화(7~8)로 갑니다.

---

## 과제 1: 문자열 길이

`str_length.c` 파일을 만들고 문자열 길이를 직접 세는 함수를 작성하세요. (`strlen` 사용 금지)

요구사항:
- `int str_length(char *s)` — `\0`까지 글자 수를 셈
- `main`에서 여러 문자열로 테스트

출력 예시:
```
"hello" → 5
"" → 0
"42 seoul" → 8
```

힌트:
```c
int str_length(char *s)
{
    int len = 0;
    while (s[len])
        len++;
    return (len);
}
```

> 12차시 `sbs_strlen`의 원형입니다. `while (s[i])`로 `\0`까지 셉니다.

---

## 과제 2: 문자열 출력 (포인터 순회)

`str_print.c` 파일을 만들고 포인터를 직접 이동시키며 한 글자씩 출력하세요. (`printf("%s")` 금지, `%c`만)

요구사항:
- `void str_print(char *s)` — `*p`로 한 글자씩, `p++`로 이동
- 끝에 줄바꿈

힌트:
```c
void str_print(char *s)
{
    char *p = s;
    while (*p)
    {
        printf("%c", *p);
        p++;
    }
    printf("\n");
}
```

---

## 과제 3: 대문자 변환

`to_upper.c` 파일을 만들고 문자열의 소문자를 모두 대문자로 바꾸세요.

요구사항:
- `void to_upper(char *s)` — 소문자만 `-32`, 나머지는 그대로
- 원본 배열을 직접 수정 (배열로 선언할 것)

출력 예시:
```
"Hello, 42!" → "HELLO, 42!"
```

힌트:
```c
void to_upper(char *s)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] = s[i] - 32;
        i++;
    }
}
```

> `char *s = "..."`가 아니라 `char s[] = "..."`로 만드세요. 리터럴은 수정 불가.

---

## 과제 4: 문자열 복사

`str_copy.c` 파일을 만들고 한 문자열을 다른 배열로 복사하세요. (`strcpy` 금지)

요구사항:
- `void str_copy(char *dst, char *src)` — `src`를 `dst`로 `\0`까지 복사
- `\0`도 복사할 것
- `main`에서 충분히 큰 `dst` 배열 준비

출력 예시:
```
복사 결과: hello world
```

힌트:
```c
void str_copy(char *dst, char *src)
{
    int i = 0;
    while (src[i])
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';   // 끝 표시 잊지 말 것
}
```

> `\0`을 복사하지 않으면 쓰레기가 붙습니다. 12차시 `sbs_strlcpy`의 기초.

---

## 과제 5: 문자 개수 세기

`count_char.c` 파일을 만들고 문자열에서 특정 문자가 몇 번 나오는지 세세요.

요구사항:
- `int count_char(char *s, char target)` — `target`과 같은 글자 수 반환
- 여러 문자로 테스트

출력 예시:
```
"banana"에서 'a' → 3
"banana"에서 'n' → 2
"banana"에서 'z' → 0
```

힌트:
```c
int count_char(char *s, char target)
{
    int count = 0;
    int i = 0;
    while (s[i])
    {
        if (s[i] == target)
            count++;
        i++;
    }
    return (count);
}
```

---

## 과제 6: 문자열 뒤집기

`str_reverse.c` 파일을 만들고 문자열을 제자리에서 뒤집으세요.

요구사항:
- `void str_reverse(char *s)` — 양끝에서 가운데로 swap
- 추가 배열 없이 제자리(in-place) 뒤집기
- 배열로 선언

출력 예시:
```
"hello" → "olleh"
"42seoul" → "luoes24"
```

힌트:
```c
void str_reverse(char *s)
{
    int left = 0;
    int right = 0;
    while (s[right])
        right++;
    right--;
    while (left < right)
    {
        char tmp = s[left];
        s[left] = s[right];
        s[right] = tmp;
        left++;
        right--;
    }
}
```

> 5차시 swap을 문자열에 응용. `right`는 마지막 글자 인덱스(len-1)에서 시작.

---

## 과제 7: 모음 개수 세기 (심화, 20분)

`count_vowels.c` 파일을 만들고 문자열의 모음(a,e,i,o,u 대소문자 모두)을 세세요.

요구사항:
- `int count_vowels(char *s)` — 모음 개수 반환
- 대문자·소문자 모음 모두 인정
- 보조 함수 `int is_vowel(char c)`를 만들어 사용

출력 예시:
```
"Hello World" → 3
"AEIOU" → 5
"xyz" → 0
```

힌트:
```c
int is_vowel(char c)
{
    if (c >= 'A' && c <= 'Z')
        c = c + 32;   // 소문자로 통일
    return (c == 'a' || c == 'e' || c == 'i'
        || c == 'o' || c == 'u');
}
```

> 대소문자를 통일한 뒤 비교하면 조건이 간단해집니다.

---

## 과제 8: 회문 판별 (심화, 25분)

`palindrome.c` 파일을 만들고 문자열이 회문(앞뒤로 같음)인지 판별하세요.

요구사항:
- `int is_palindrome(char *s)` — 회문이면 1, 아니면 0
- 양끝에서 좁혀가며 비교 (뒤집지 말고 직접 비교)
- 여러 문자열로 테스트

출력 예시:
```
"level" → 회문
"hello" → 회문 아님
"42024" → 회문
```

힌트:
```c
int is_palindrome(char *s)
{
    int left = 0;
    int right = 0;
    while (s[right])
        right++;
    right--;
    while (left < right)
    {
        if (s[left] != s[right])
            return (0);
        left++;
        right--;
    }
    return (1);
}
```

생각해보기: 뒤집어서 비교하는 방법도 있지만, 양끝 비교가 왜 더 효율적일까? (절반만 비교하면 됨)

---

## 제출 확인 사항

기본 (6과제):
- [ ] `str_length.c` - `\0`까지 길이 세기
- [ ] `str_print.c` - 포인터 순회로 출력
- [ ] `to_upper.c` - 소문자 → 대문자 (±32)
- [ ] `str_copy.c` - `\0` 포함 복사
- [ ] `count_char.c` - 특정 문자 세기
- [ ] `str_reverse.c` - 제자리 뒤집기

심화 (2과제):
- [ ] `count_vowels.c` - 모음 세기 (보조 함수)
- [ ] `palindrome.c` - 회문 판별

- [ ] 모든 파일: `gcc -Wall -Wextra -Werror` 경고 없이 컴파일
- [ ] 수정하는 문자열은 모두 `char arr[]`로 선언했는가?
