# 14차시 심화 - 큰 정수 변환 (sbs_atol)

> 필수 2개(strncmp/atoi)를 끝낸 학생을 위한 심화 자료입니다. `atoi`는 `int` 범위(약 ±21억)를 넘는 수는 처리 못 합니다. `atol`은 그보다 큰 `long` 범위까지 다룹니다.

## 심화 학습 목표

1. `int`와 `long`의 표현 범위 차이를 설명할 수 있다.
2. `sbs_atol`을 `sbs_atoi`의 구조를 재사용해 구현할 수 있다.
3. "한 단계 위 타입으로 누적"하는 오버플로 완화 패턴을 이해한다.

---

## 1. int로는 부족한 경우

```c
sbs_atoi("9999999999");   // int 범위(약 21억) 초과 → 정의되지 않은 동작(값 깨짐)
sbs_atol("9999999999");   // long 범위 안 → 정확한 값
```

파일 크기(바이트 단위), 타임스탬프, 큰 ID 값 등은 `int` 하나로 담기엔 클 때가 많습니다.

---

## 2. sbs_atol — 구현

`sbs_atoi`(14차시)와 처리 순서(공백 → 부호 → 숫자)는 완전히 같습니다. 차이는 **누적 변수와 반환 타입**뿐입니다: `int` 대신 `long`을 반환하고, 오버플로를 조금 더 늦추기 위해 내부 누적은 `long`보다 한 단계 위인 `long long`으로 합니다(9차시 `putnbr_fd`에서 `int`→`long`으로 올렸던 것과 같은 아이디어).

```c
#include "libsbs.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

long	sbs_atol(const char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((long)(result * sign));
}
```

핵심 포인트:
- `is_space` 헬퍼는 `sbs_atoi`와 완전히 동일(복붙 재사용)
- 처리 순서(공백→부호→숫자)도 동일 — **바뀐 건 타입뿐**
- `long long result` — `sbs_atoi`가 `int` 반환에 `long` 누적을 썼던 것과 똑같은 "한 단계 위로 누적" 패턴

---

## 3. 심화 정리

1. `sbs_atol`은 `sbs_atoi`와 알고리즘이 100% 동일 — 타입만 한 단계씩 올림
2. `int → long`, `long → long long`: 오버플로 여유를 한 단계 벌어주는 패턴
3. 여전히 `long long`도 무한하지 않으므로 극단적으로 긴 숫자는 표준처럼 정의되지 않은 동작(이 과정에서는 다루지 않음)

---

## 채점

필수 2개와 별도로 심화 1개를 채점합니다(`bash grade.sh`가 BONUS 섹션으로 표시).

```bash
$ bash grade.sh
=== libsbs 14차시 채점 ===
✓ sbs_strncmp   (...)
✓ sbs_atoi      (...)
결과: 2 / 2 통과
--- BONUS (심화) ---
✓ sbs_atol
보너스: 1 / 1 통과
```

---

## 심화 연결 지도

| 심화 주제 | 이어지는 차시 |
|-----------|---------------|
| int/long 범위 | 9차시 putnbr_fd의 INT_MIN 오버플로 처리 |
| 함수 재사용 | 9차시 sbs_isalnum→isalpha+isdigit 패턴 |
| 정수 파싱 | 16차시 종합 프로젝트에서 다시 활용 |
