# 2차시 실습 - 변수, 자료형, 연산자

## 실습 목표

- 각 자료형의 실제 크기를 sizeof로 직접 확인한다.
- 연산자를 활용한 계산기 프로그램을 작성한다.
- 형 변환이 필요한 상황을 직접 경험한다.


---

## 과제 1: sizeof 실험

`sizeof_test.c` 파일을 만들고, 아래 모든 자료형의 크기를 출력하는 프로그램을 작성하세요.

```c
#include <stdio.h>

int main(void)
{
    // 각 자료형의 크기를 출력하세요
    // 힌트: printf("char 크기: %zu 바이트\n", sizeof(char));
    
    // char, unsigned char
    // short, unsigned short
    // int, unsigned int
    // long, unsigned long
    // float
    // double
    // long double
    
    return (0);
}
```

실행 후 표를 채워보세요:

| 자료형 | 예상 크기 | 실제 크기 |
|--------|-----------|-----------|
| char | 1 | |
| short | 2 | |
| int | 4 | |
| long | ? | |
| float | 4 | |
| double | 8 | |

---

## 과제 2: 사칙연산 계산기

`calculator.c` 파일을 만들고 두 정수에 대한 사칙연산 결과를 출력하는 프로그램을 작성하세요.

요구사항:
- 두 개의 `int` 변수를 선언하고 원하는 값으로 초기화
- 덧셈, 뺄셈, 곱셈, 나눗셈, 나머지를 모두 출력
- **정수 나눗셈과 실수 나눗셈을 둘 다 출력** (형 변환 사용)

출력 예시 (`a = 17`, `b = 5` 기준):
```
=== 계산기 ===
a = 17, b = 5
덧셈:   17 + 5 = 22
뺄셈:   17 - 5 = 12
곱셈:   17 * 5 = 85
나눗셈(정수): 17 / 5 = 3
나눗셈(실수): 17 / 5 = 3.400000
나머지: 17 % 5 = 2
```

---

## 과제 3: 온도 변환기

`temperature.c` 파일을 만들고 섭씨를 화씨로, 화씨를 섭씨로 변환하는 프로그램을 작성하세요.

공식:
- 섭씨 → 화씨: `F = C * 9.0 / 5.0 + 32`
- 화씨 → 섭씨: `C = (F - 32) * 5.0 / 9.0`

요구사항:
- 섭씨 0도, 100도를 화씨로 변환
- 화씨 32도, 212도를 섭씨로 변환
- 소수점 2자리까지 출력 (`%.2f`)

출력 예시:
```
섭씨 0.00°C = 화씨 32.00°F
섭씨 100.00°C = 화씨 212.00°F
화씨 32.00°F = 섭씨 0.00°C
화씨 212.00°F = 섭씨 100.00°C
```

---

## 과제 4: 연산자 우선순위 실험 (심화, 20분)

`priority.c` 파일을 만들고 아래 식의 결과를 먼저 손으로 계산한 뒤, 프로그램으로 확인하세요.

```c
#include <stdio.h>

int main(void)
{
    int a = 2, b = 3, c = 4;
    int result;

    // 각 식의 결과를 예상하고 출력하세요
    result = a + b * c;
    printf("a + b * c = %d\n", result);

    result = (a + b) * c;
    printf("(a + b) * c = %d\n", result);

    result = a * b + c * 2;
    printf("a * b + c * 2 = %d\n", result);

    result = a + b > c;
    printf("a + b > c = %d\n", result);

    result = a == 2 && b == 3;
    printf("a == 2 && b == 3 = %d\n", result);

    result = a > 1 || b > 10;
    printf("a > 1 || b > 10 = %d\n", result);

    return (0);
}
```

손으로 계산한 예상값:
1. `a + b * c` = ___
2. `(a + b) * c` = ___
3. `a * b + c * 2` = ___
4. `a + b > c` = ___
5. `a == 2 && b == 3` = ___
6. `a > 1 || b > 10` = ___

---

## 제출 확인 사항

- [ ] `sizeof_test.c` - 모든 자료형 크기 출력
- [ ] `calculator.c` - 사칙연산 + 정수/실수 나눗셈 구분 출력
- [ ] `temperature.c` - 온도 변환 (형 변환 사용)
- [ ] `priority.c` - 연산자 우선순위 실험 (심화)
- [ ] 모든 파일: `-Wall -Wextra -Werror` 경고 없이 컴파일
