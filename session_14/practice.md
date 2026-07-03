# 14차시 실습 - 문자열 비교와 변환

## 실습 목표

- `sbs_strncmp`로 n글자 비교를 구현한다.
- `sbs_atoi`로 부호·공백·혼합 입력을 처리해 정수로 변환한다.

**진행 순서**: 과제 1~3은 **필수**(전원 완료), 맨 아래 "도전 과제"는 필수를 끝낸 사람만 진행합니다.

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

::: hint 막히면 힌트 보기 (sbs_strncmp)
```c
while (i < n)
{
    if (s1[i] != s2[i] || s1[i] == '\0')
        return ((unsigned char)s1[i] - (unsigned char)s2[i]);
    i++;
}
return (0);
```
:::

> memcmp와 달리 `\0`에서 멈춥니다. 한쪽이 짧으면 거기서 결판.

---

## 과제 2: sbs_atoi

`sbs_atoi.c` — 문자열을 정수로. 공백 → 부호 → 숫자 순서.

요구사항:
- 선행 공백 건너뛰기(` `, `\t`, `\n`, `\v`, `\f`, `\r`)
- `+`/`-` 부호 한 개 처리
- 숫자가 아닌 문자를 만나면 중단
- 숫자 없으면 0

::: hint 막히면 힌트 보기 (sbs_atoi)
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
:::

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

---

## 도전 과제 (필수 3개를 마친 사람만)

시간이 남으면 아래 순서대로 도전하세요. 정답 예시는 이 페이지 맨 아래 "정답 코드"에서 확인할 수 있습니다.

> 스켈레톤 코드는 **TODO를 채우기 전에는 컴파일이 안 될 수 있습니다** (`-Werror`가 미사용 변수 경고를 에러로 처리). TODO를 다 채운 뒤 컴파일하세요.

### 도전 1: 미니 프로젝트 — 버전 비교기 (version_compare.c)

`"1.2.3"`, `"1.10.0"` 같은 버전 문자열 두 개를 받아 어느 쪽이 더 높은 버전인지 출력하세요.

요구사항:
- 단순히 `sbs_strncmp`로 전체 비교하면 안 됨! (`"1.2"` vs `"1.10"`을 문자 그대로 비교하면 `'2' > '1'`이라 `1.2`가 더 크다고 잘못 나옴)
- `sbs_atoi`로 `.`로 구분된 각 부분을 숫자로 변환한 뒤 비교(메이저.마이너.패치 순서로)
- 출력 예: `1.2.3 < 1.10.0`

스켈레톤 (`version_compare.c`로 저장 후 TODO를 채우세요):
```c
#include "libsbs.h"
#include <stdio.h>

/* s의 idx 위치부터 다음 '.' 전까지를 숫자로 변환하고, idx를 다음 부분으로 이동 */
static int	next_part(const char *s, int *idx)
{
	int	start;
	int	value;

	start = *idx;
	/* TODO 1: *idx를 '.' 또는 '\0'까지 전진 */
	value = sbs_atoi(s + start);
	/* TODO 2: 지금 위치가 '.'이면 한 칸 더 전진(다음 부분의 시작) */
	return (value);
}

static int	compare_version(const char *a, const char *b)
{
	int	ia;
	int	ib;

	ia = 0;
	ib = 0;
	while (a[ia] || b[ib])
	{
		/* TODO 3: next_part로 양쪽에서 숫자 하나씩 꺼내 비교.
		           다르면 그 차이를 반환 */
	}
	return (0);
}

int	main(void)
{
	char	*v1 = "1.2.3";
	char	*v2 = "1.10.0";
	int		cmp;

	cmp = compare_version(v1, v2);
	/* TODO 4: cmp 부호에 따라 "<", ">", "==" 출력 */
	return (0);
}
```

컴파일·실행:
```bash
cc -Wall -Wextra -Werror -I. version_compare.c sbs_atoi.c -o vcmp && ./vcmp
```

### 도전 2: 미니 프로젝트 — 커맨드라인 계산기 (calc_cli.c)

`argc`/`argv`로 `숫자 연산자 숫자` 형태의 인자 3개를 받아 계산하는 프로그램을 작성하세요(예: `./calc 3 + 5`).

요구사항:
- `argv[1]`, `argv[3]`을 `sbs_atoi`로 정수 변환
- `argv[2]`가 `"+"`, `"-"`, `"*"`, `"/"` 중 무엇인지 `sbs_strncmp`로 판별(`argv[2][1]`이 `\0`인지도 확인해 한 글자짜리 연산자만 허용)
- `argc != 4`면 사용법 출력 후 종료
- `0`으로 나누기 방지

스켈레톤 (`calc_cli.c`로 저장 후 TODO를 채우세요):
```c
#include "libsbs.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	int	a;
	int	b;
	int	result;

	result = 0;
	/* TODO 1: argc != 4 이거나 argv[2]가 한 글자가 아니면 사용법 출력 후 return 1 */
	a = sbs_atoi(argv[1]);
	b = sbs_atoi(argv[3]);
	/* TODO 2: sbs_strncmp로 argv[2]가 +,-,*,/ 중 무엇인지 판별해 계산 */
	/* TODO 3: 나눗셈일 때 b == 0이면 에러 출력 후 return 1 */
	printf("%d %s %d = %d\n", a, argv[2], b, result);
	return (0);
}
```

컴파일·실행:
```bash
cc -Wall -Wextra -Werror -I. calc_cli.c sbs_atoi.c sbs_strncmp.c -o calc && ./calc 3 + 5
```

### 도전 3: 심화 함수 — sbs_atol

`int` 범위를 넘는 큰 정수도 다루는 `sbs_atol`(문자열 → `long`)을 구현하세요. [advanced.md](advanced.md)를 참고하세요. 힌트: `sbs_atoi`와 로직은 같고, `result`와 반환 타입만 `long`으로 바꿉니다.

스켈레톤 (`sbs_atol.c`로 저장 후 TODO를 채우세요):
```c
#include "libsbs.h"

static int	is_space(char c)
{
	/* TODO: sbs_atoi의 is_space와 동일 */
	return (c == ' ');
}

long	sbs_atol(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	/* TODO 1: 공백 건너뛰기 */
	/* TODO 2: 부호 한 개 처리 */
	/* TODO 3: 숫자 누적 (sbs_atoi와 동일, 타입만 long long) */
	return ((long)(result * sign));
}
```

`sbs_atol.c` 파일을 만들면 `bash grade.sh`가 자동으로 BONUS 섹션에서 채점합니다.
