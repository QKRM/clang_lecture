# 4차시 실습 - 함수와 재귀

## 실습 목표

- 함수를 선언·정의·호출하는 전체 흐름을 직접 작성한다.
- 같은 문제(팩토리얼, 피보나치)를 반복문과 재귀로 각각 구현해 비교한다.
- 값에 의한 전달을 코드로 확인한다.


---

## 과제 1: 함수 기본 — 사칙연산

`functions.c` 파일을 만들고 네 개의 함수를 작성하세요.

요구사항:
- `int add(int a, int b)` / `int sub(int a, int b)` / `int mul(int a, int b)` / `int divide(int a, int b)`
- 모두 프로토타입을 `main` 위에 선언, 정의는 `main` 아래
- `main`에서 각 함수를 호출해 결과 출력

출력 예시 (a=12, b=4):
```
add: 16
sub: 8
mul: 48
divide: 3
```

힌트:
```c
#include <stdio.h>

int add(int a, int b);   // 프로토타입
/* ... 나머지 프로토타입 ... */

int main(void)
{
    int a = 12, b = 4;
    printf("add: %d\n", add(a, b));
    /* ... */
    return (0);
}

int add(int a, int b)    // 정의
{
    return (a + b);
}
```

---

## 과제 2: 팩토리얼 — 반복 vs 재귀

`factorial.c` 파일을 만들고 두 가지 버전을 모두 구현하세요.

요구사항:
- `int fact_loop(int n)` — for 또는 while 반복
- `int fact_rec(int n)` — 재귀
- `main`에서 1~5에 대해 두 함수 결과가 같은지 출력

출력 예시:
```
n=1  loop=1   rec=1
n=2  loop=2   rec=2
n=3  loop=6   rec=6
n=4  loop=24  rec=24
n=5  loop=120 rec=120
```

힌트:
```c
int fact_loop(int n)
{
    int result = 1;
    for (int i = 2; i <= n; i++)
        result *= i;
    return (result);
}

int fact_rec(int n)
{
    if (n <= 1)
        return (1);
    return (n * fact_rec(n - 1));
}
```

---

## 과제 3: 피보나치 — 반복 vs 재귀

`fibonacci.c` 파일을 만들고 피보나치 수열을 두 방식으로 구현하세요.

수열 정의: `fib(0)=0`, `fib(1)=1`, `fib(n)=fib(n-1)+fib(n-2)`

요구사항:
- `int fib_loop(int n)` — 반복
- `int fib_rec(int n)` — 재귀
- `main`에서 0~10 출력

출력 예시:
```
fib(0) = 0
fib(1) = 1
fib(2) = 1
fib(3) = 2
fib(4) = 3
fib(5) = 5
...
fib(10) = 55
```

힌트 (재귀):
```c
int fib_rec(int n)
{
    if (n < 2)
        return (n);
    return (fib_rec(n - 1) + fib_rec(n - 2));
}
```

> 생각해보기: 재귀 버전 `fib_rec(40)`은 왜 느릴까? (같은 값을 몇 번이나 다시 계산하는지 추적)

---

## 과제 4: 값 전달 확인 (심화, 25분)

`pass_by_value.c` 파일을 만들고 값에 의한 전달을 직접 확인하세요.

요구사항:
- `void try_change(int x)` — 매개변수 x를 999로 바꿈
- `main`에서 변수 a=5를 넘기고, 호출 전후로 a를 출력
- a가 변하지 **않음**을 확인

출력 예시:
```
호출 전: a = 5
함수 안: x = 999
호출 후: a = 5   ← 변하지 않음!
```

생각해보기: 원본을 진짜로 바꾸려면 무엇이 필요할까? (답은 5차시 포인터)

```c
void try_change(int x)
{
    x = 999;
    printf("함수 안: x = %d\n", x);
}
```

---

## 제출 확인 사항

- [ ] `functions.c` - 4개 함수, 프로토타입 분리
- [ ] `factorial.c` - 반복 + 재귀, 결과 일치 확인
- [ ] `fibonacci.c` - 반복 + 재귀, 0~10 출력
- [ ] `pass_by_value.c` - 값 전달 확인 (심화)
- [ ] 모든 파일: `gcc -Wall -Wextra -Werror` 경고 없이 컴파일
