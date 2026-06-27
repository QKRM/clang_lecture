# 14차시 실습 - 문자열 비교와 변환

## 실습 목표

- `sbs_strncmp`로 n글자 비교를 구현한다.
- `sbs_atoi`로 부호·공백·혼합 입력을 처리해 정수로 변환한다.


> **금지**: `<string.h>`, `<strings.h>`. 직접 구현해야 합니다.

---

## 준비: libsbs.h에 추가

```c
int		sbs_strncmp(const char *s1, const char *s2, size_t n);
int		sbs_atoi(const char *str);
```

---

## 과제 1: sbs_strncmp

`sbs_strncmp.c` — 최대 n글자 비교, 처음 다른 글자 차이, 같으면 0.

요구사항:
- `\0`을 만나면 종료(문자열 끝)
- `unsigned char`로 차이 계산
- 부호가 정확해야 함

힌트:
```c
while (i < n)
{
    if (s1[i] != s2[i] || s1[i] == '\0')
        return ((unsigned char)s1[i] - (unsigned char)s2[i]);
    i++;
}
return (0);
```

> memcmp와 달리 `\0`에서 멈춥니다. 한쪽이 짧으면 거기서 결판.

---

## 과제 2: sbs_atoi

`sbs_atoi.c` — 문자열을 정수로. 공백 → 부호 → 숫자 순서.

요구사항:
- 선행 공백 건너뛰기(` `, `\t`, `\n`, `\v`, `\f`, `\r`)
- `+`/`-` 부호 한 개 처리
- 숫자가 아닌 문자를 만나면 중단
- 숫자 없으면 0

힌트:
```c
while (is_space(str[i])) i++;
if (str[i] == '+' || str[i] == '-')
{
    if (str[i] == '-') sign = -1;
    i++;
}
while (str[i] >= '0' && str[i] <= '9')
{
    result = result * 10 + (str[i] - '0');
    i++;
}
return ((int)(result * sign));
```

엣지 케이스 (꼭 테스트):
```
"42"→42  "-42"→-42  "  +7"→7  "12ab"→12
"abc"→0  ""→0  "+-5"→0  "\t-99x"→-99
```

> `is_space` 보조 함수를 만들면 깔끔합니다. `result`를 `long`으로 두면 큰 수에 조금 안전.

---

## 과제 3: 채점 + 엣지 케이스

```bash
$ bash grade.sh
=== libsbs 14차시 채점 ===
✓ sbs_strncmp   (...)
✓ sbs_atoi      (...)
결과: 2 / 2 통과
```

실패 시 `bash grade.sh -v`로 어떤 입력에서 틀렸는지 확인.

메모리 누수 점검(권장):
```bash
$ valgrind --leak-check=full ./a.out
```

---

## 제출 확인 사항

- [ ] `libsbs.h`에 2개 프로토타입 추가
- [ ] `sbs_strncmp.c` - n글자 비교, \0 종료, 부호 정확
- [ ] `sbs_atoi.c` - 공백·부호·숫자 처리, 엣지 케이스
- [ ] `<string.h>` 미사용
- [ ] `bash grade.sh` → 2 / 2 통과

---

## 더 생각해볼 거리

1. strncmp가 `\0`에서 멈추는 이유는? (문자열은 \0이 끝)
2. atoi가 오버플로(범위 초과 숫자)를 만나면? (표준은 정의되지 않음 — 여기선 long으로 완화)
3. strncmp를 `char`로 비교하면 왜 부호가 뒤집힐까? (0x80 이상 바이트가 음수)
