# 3차시 실습 - 조건문과 반복문

## 실습 목표

- 중첩 반복문으로 구구단을 출력한다.
- 조건문과 나머지 연산자를 조합해 FizzBuzz를 구현한다.
- `while` 반복과 조건 분기로 숫자 맞추기 게임을 만든다.


---

## 과제 1: 구구단 출력

`gugudan.c` 파일을 만들고 2단부터 9단까지 출력하는 프로그램을 작성하세요.

요구사항:
- 바깥 반복문: 단(2~9)
- 안쪽 반복문: 곱하는 수(1~9)
- 각 단 사이에 빈 줄 한 개

출력 예시 (일부):
```
2단
2 x 1 = 2
2 x 2 = 4
...
2 x 9 = 18

3단
3 x 1 = 3
...
```

힌트:
```c
for (int dan = 2; dan <= 9; dan++)
{
    printf("%d단\n", dan);
    for (int i = 1; i <= 9; i++)
        printf("%d x %d = %d\n", dan, i, dan * i);
    printf("\n");
}
```

---

## 과제 2: FizzBuzz

`fizzbuzz.c` 파일을 만들고 1부터 30까지 출력하되, 규칙에 따라 단어로 바꾸는 프로그램을 작성하세요.

규칙:
- 3의 배수 → `Fizz`
- 5의 배수 → `Buzz`
- 3과 5의 공배수(15의 배수) → `FizzBuzz`
- 그 외 → 숫자 그대로

출력 예시:
```
1
2
Fizz
4
Buzz
Fizz
7
8
Fizz
Buzz
11
Fizz
13
14
FizzBuzz
...
```

**주의**: 15의 배수 검사를 먼저 해야 합니다. 순서를 틀리면 15에서 `Fizz`만 출력됩니다.

힌트:
```c
if (i % 15 == 0)
    printf("FizzBuzz\n");
else if (i % 3 == 0)
    printf("Fizz\n");
else if (i % 5 == 0)
    printf("Buzz\n");
else
    printf("%d\n", i);
```

---

## 과제 3: 숫자 맞추기 게임

`guess_number.c` 파일을 만들고 정답을 맞출 때까지 반복 입력받는 프로그램을 작성하세요.

요구사항:
- 정답을 코드에 상수로 정함 (예: `const int answer = 42;`)
- `scanf`로 사용자 입력을 받음
- 입력이 정답보다 크면 "더 작게", 작으면 "더 크게" 출력
- 맞히면 시도 횟수를 출력하고 종료 (`while` + `break` 사용)

출력 예시:
```
숫자를 맞춰보세요 (1~100): 50
더 작게!
숫자를 맞춰보세요 (1~100): 25
더 크게!
숫자를 맞춰보세요 (1~100): 42
정답! 3번 만에 맞혔습니다.
```

힌트:
```c
#include <stdio.h>

int main(void)
{
    const int answer = 42;
    int guess = 0;
    int tries = 0;

    while (1)
    {
        printf("숫자를 맞춰보세요 (1~100): ");
        scanf("%d", &guess);
        tries++;

        if (guess > answer)
            printf("더 작게!\n");
        else if (guess < answer)
            printf("더 크게!\n");
        else
        {
            printf("정답! %d번 만에 맞혔습니다.\n", tries);
            break;
        }
    }
    return (0);
}
```

> `scanf`의 `&guess`에서 `&`(주소 연산자)는 5차시 포인터에서 자세히 다룹니다. 지금은 "입력값을 변수에 저장하는 문법"으로 받아들이세요.

---

## 과제 4: 별 피라미드 (심화, 20분)

`pyramid.c` 파일을 만들고 중첩 반복문으로 아래 패턴을 출력하세요.

```
    *
   ***
  *****
 *******
*********
```

힌트:
- 행(row) 1~5에 대해
- 공백을 `(5 - row)`개 출력
- 별을 `(2 * row - 1)`개 출력
- 줄바꿈

```c
for (int row = 1; row <= 5; row++)
{
    for (int s = 0; s < 5 - row; s++)
        printf(" ");
    for (int star = 0; star < 2 * row - 1; star++)
        printf("*");
    printf("\n");
}
```

---

## 제출 확인 사항

- [ ] `gugudan.c` - 2~9단 중첩 반복문 출력
- [ ] `fizzbuzz.c` - 1~30, 15의 배수 우선 검사
- [ ] `guess_number.c` - while + break, 시도 횟수 출력
- [ ] `pyramid.c` - 별 피라미드 (심화)
- [ ] 모든 파일: `gcc -Wall -Wextra -Werror` 경고 없이 컴파일
