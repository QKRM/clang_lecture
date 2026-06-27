# 9차시 심화 - fd 출력 함수 (putchar/putstr/putnbr)

> 기본 7개 함수(is*/toupper/tolower)를 끝낸 학생을 위한 심화 자료입니다. 파일 디스크립터(fd)와 `write` 시스템 콜을 처음 만나고, 재귀로 정수를 출력합니다. libsbs 확장 함수(bonus)로 자주 포함됩니다.

## 심화 학습 목표

1. 파일 디스크립터(fd)와 `write` 시스템 콜의 개념을 설명할 수 있다.
2. `sbs_putchar_fd`, `sbs_putstr_fd`를 구현할 수 있다.
3. `sbs_putnbr_fd`를 재귀로 구현하고 **`INT_MIN` 함정**을 처리할 수 있다.

---

## 1. 파일 디스크립터와 write

### 1.1 fd란?

운영체제가 열린 파일·스트림을 가리키는 정수입니다. 표준 스트림 3개는 고정:

| fd | 이름 | 의미 |
|----|------|------|
| 0 | stdin | 표준 입력 |
| 1 | stdout | 표준 출력 (화면) |
| 2 | stderr | 표준 에러 |

### 1.2 write 시스템 콜

`printf`보다 더 낮은 수준의 출력입니다. "어느 fd에, 어디서, 몇 바이트"를 직접 지정합니다.

```c
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
```

```c
write(1, "Hi", 2);   // stdout에 "Hi" 2바이트
```

> `man 2 write`로 명세 확인. 9차시 문자 함수와 달리 `<unistd.h>`가 필요합니다(이 헤더는 표준 문자 함수가 아니므로 허용).

---

## 2. sbs_putchar_fd — 한 글자 출력

`fd`에 문자 `c` 하나를 씁니다.

```c
#include "libsbs.h"
#include <unistd.h>

void	sbs_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
```

핵심: `write`는 **주소**를 받으므로 `&c`를 넘깁니다(5차시 포인터).

---

## 3. sbs_putstr_fd — 문자열 출력

`fd`에 문자열 `s`를 `\0` 전까지 씁니다.

```c
void	sbs_putstr_fd(char *s, int fd)
{
	int	i;

	if (s == NULL)        // NULL 방어
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
```

핵심:
- `NULL` 입력 방어(`return ;`)
- 7차시 문자열 순회 + `write` 결합

---

## 4. sbs_putnbr_fd — 정수 출력 (가장 어려움)

`fd`에 정수 `n`을 사람이 읽는 10진수로 씁니다. 재귀로 한 자리씩.

### 4.1 기본 아이디어

```
123 출력:
  putnbr(12) 먼저 → putnbr(1) 먼저 → '1'
                              '2'
                  '3'
```

상위 자릿수부터 출력하려면 **재귀 호출을 먼저** 하고, 마지막 자리를 나중에 씁니다.

### 4.2 INT_MIN 함정

`int`의 최솟값은 `-2147483648`. 그런데 최댓값은 `+2147483647`입니다. **`-INT_MIN`은 int로 표현 불가**(오버플로)!

```c
int n = -2147483648;
n = -n;   // 위험! +2147483648은 int 범위를 넘음 → 정의되지 않은 동작
```

해법: **`long`으로 받아** 부호를 뒤집습니다.

```c
void	sbs_putnbr_fd(int n, int fd)
{
	long	nb;
	char	c;

	nb = n;                      // long으로 승격 (핵심!)
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;                // long이므로 안전
	}
	if (nb >= 10)
		sbs_putnbr_fd((int)(nb / 10), fd);   // 상위 자리 먼저
	c = (char)(nb % 10) + '0';   // 마지막 자리
	write(fd, &c, 1);
}
```

핵심 포인트:
- `long nb = n;` — `-nb`가 오버플로 안 나게 long으로
- 음수면 `-` 출력 후 양수로
- `nb >= 10`이면 재귀로 상위 자릿수 먼저
- `nb % 10 + '0'`으로 마지막 자리를 문자로(2차시 ASCII)

> `INT_MIN` 테스트를 통과하는지가 이 함수의 핵심입니다. long을 안 쓰면 `-2147483648`에서 깨집니다.

---

## 심화 정리

1. fd = 운영체제가 열린 스트림을 가리키는 정수 (0/1/2 = in/out/err)
2. `write(fd, &버퍼, 길이)` — `printf`보다 낮은 수준 출력
3. `putchar_fd`는 `&c`를, `putstr_fd`는 NULL 방어 + 순회
4. `putnbr_fd`는 재귀로 상위 자리 먼저 출력
5. **`INT_MIN`은 `long`으로 받아** 부호 뒤집기 (오버플로 방지)

---

## 채점

기본 7개와 별도로 심화 3개를 채점합니다(`bash grade.sh`가 BONUS 섹션으로 표시).

```bash
$ bash grade.sh
=== libsbs 9차시 채점 ===
✓ sbs_isalpha   (256/256)
...
--- BONUS (심화) ---
✓ sbs_putchar_fd
✓ sbs_putstr_fd
✓ sbs_putnbr_fd   (INT_MIN 포함)
```

> 심화는 `<unistd.h>`(write)를 허용합니다. 기본 7개 함수는 여전히 `<ctype.h>` 금지.

---

## 심화 연결 지도

| 심화 주제 | 이어지는 차시 |
|-----------|---------------|
| fd / write | 10차시 메모리 함수(저수준 다루기) |
| 재귀 출력 | 4차시 재귀 복습 + 응용 |
| INT_MIN/오버플로 | 14차시 atoi(숫자 파싱 오버플로) |
| NULL 방어 | 5차시 포인터 안전 |
