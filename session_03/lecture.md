# 3차시 강의 노트 - 조건문과 반복문

## 학습 목표

1. `if / else if / else`로 조건 분기를 구현할 수 있다.
2. `switch` 문의 동작과 `break`의 역할을 설명할 수 있다.
3. `for`, `while`, `do-while`을 상황에 맞게 선택해 사용할 수 있다.
4. `break`, `continue`로 반복 흐름을 제어할 수 있다.
5. 중첩 반복문으로 2차원 패턴을 출력할 수 있다.

---

## 1부: 조건문 (Conditional Statements)

### 1.1 if 문

조건이 참(0이 아닌 값)이면 블록을 실행합니다.

```c
int score = 85;

if (score >= 60)
    printf("합격\n");
```

C언어에는 별도의 boolean 타입이 기본으로 없습니다. **0은 거짓, 0이 아닌 모든 값은 참**입니다.

```c
if (1)      printf("항상 실행\n");   // 참
if (0)      printf("절대 실행 안 됨\n"); // 거짓
if (-5)     printf("실행됨\n");      // 0이 아니므로 참
```

### 1.2 if / else

```c
int n = 7;

if (n % 2 == 0)
    printf("짝수\n");
else
    printf("홀수\n");
```

### 1.3 if / else if / else

여러 조건을 순서대로 검사합니다. 위에서부터 처음으로 참이 되는 가지만 실행됩니다.

```c
int score = 85;

if (score >= 90)
    printf("A\n");
else if (score >= 80)
    printf("B\n");        // 여기 실행
else if (score >= 70)
    printf("C\n");
else
    printf("F\n");
```

### 1.4 중괄호 주의

중괄호를 생략하면 **바로 다음 한 문장만** 조건에 묶입니다. 버그의 단골 원인입니다.

```c
// 위험: printf 두 줄 다 묶인 것처럼 보이지만...
if (x > 0)
    printf("양수\n");
    printf("이 줄은 조건과 무관하게 항상 실행\n");  // 함정!

// 안전: 항상 중괄호를 쓰는 습관
if (x > 0)
{
    printf("양수\n");
    printf("두 줄 모두 조건 안\n");
}
```

> libsbs 코드 규칙에서도 블록은 중괄호로 명확히 감싸는 것을 권장합니다.

### 1.5 switch 문

하나의 변수를 여러 상수값과 비교할 때 사용합니다.

```c
int day = 3;

switch (day)
{
    case 1:
        printf("월요일\n");
        break;
    case 2:
        printf("화요일\n");
        break;
    case 3:
        printf("수요일\n");
        break;
    default:
        printf("기타\n");
        break;
}
```

**핵심: `break`가 없으면 다음 case로 그대로 흘러내립니다 (fall-through).**

```c
switch (n)
{
    case 1:
    case 2:
    case 3:
        printf("1~3\n");   // 1, 2, 3 모두 여기로
        break;
    default:
        printf("그 외\n");
}
```

`switch`는 정수형(`int`, `char` 등)만 비교할 수 있고, `case` 라벨은 상수여야 합니다.

---

## 2부: 반복문 (Loops)

### 2.1 while 문

조건이 참인 동안 반복합니다. 반복 횟수가 미리 정해지지 않은 경우에 적합합니다.

```c
int i = 0;

while (i < 5)
{
    printf("%d ", i);   // 0 1 2 3 4
    i++;
}
```

**무한 루프 주의**: 조건을 거짓으로 만드는 코드(`i++`)를 빠뜨리면 영원히 돕니다.

### 2.2 for 문

반복 횟수가 정해진 경우에 적합합니다. 초기화·조건·증감을 한 줄에 모읍니다.

```c
//      초기화;   조건;    증감
for (int i = 0; i < 5; i++)
{
    printf("%d ", i);   // 0 1 2 3 4
}
```

실행 순서: `초기화` → `조건 검사` → `본문` → `증감` → `조건 검사` → ... (조건이 거짓이면 종료)

### 2.3 do-while 문

본문을 **먼저 한 번 실행한 뒤** 조건을 검사합니다. 최소 1회는 반드시 실행됩니다.

```c
int i = 10;

do {
    printf("%d ", i);   // 10 (조건이 거짓이어도 한 번은 출력)
    i++;
} while (i < 5);
```

> 끝에 세미콜론(`;`)이 붙는 것에 주의.

### 2.4 while vs for vs do-while

| 상황 | 추천 |
|------|------|
| 반복 횟수가 정해짐 (0~n) | `for` |
| 조건에 따라 반복 (입력, 탐색) | `while` |
| 최소 1회 실행 보장 (메뉴 출력) | `do-while` |

libsbs의 문자열/메모리 함수는 대부분 `while (s[i])` 형태를 씁니다 — 길이를 미리 모르기 때문입니다.

---

## 3부: 흐름 제어 — break, continue

### 3.1 break

가장 가까운 반복문(또는 switch)을 즉시 빠져나갑니다.

```c
for (int i = 0; i < 100; i++)
{
    if (i == 5)
        break;          // i가 5가 되면 반복 종료
    printf("%d ", i);   // 0 1 2 3 4
}
```

### 3.2 continue

이번 반복의 나머지를 건너뛰고 다음 반복으로 넘어갑니다.

```c
for (int i = 0; i < 10; i++)
{
    if (i % 2 == 0)
        continue;       // 짝수면 아래 건너뜀
    printf("%d ", i);   // 1 3 5 7 9
}
```

| 키워드 | 동작 |
|--------|------|
| `break` | 반복문 전체 종료 |
| `continue` | 현재 회차만 건너뛰고 다음 회차로 |

---

## 4부: 중첩 반복문 (Nested Loops)

반복문 안에 반복문을 넣습니다. 바깥 루프가 1번 돌 때 안쪽 루프가 전부 돕니다.

```c
// 구구단 2~9단
for (int dan = 2; dan <= 9; dan++)
{
    for (int i = 1; i <= 9; i++)
    {
        printf("%d x %d = %d\n", dan, i, dan * i);
    }
    printf("\n");   // 단 사이 줄바꿈
}
```

별 삼각형 패턴:

```c
for (int row = 1; row <= 5; row++)
{
    for (int col = 0; col < row; col++)
        printf("*");
    printf("\n");
}
// *
// **
// ***
// ****
// *****
```

> 중첩이 깊어지면 가독성이 떨어집니다. libsbs 코드 규칙에서는 중첩 깊이를 제한하기도 합니다.

---

## 핵심 정리

1. C에서 **0은 거짓, 나머지는 모두 참**
2. `if / else if / else`는 위에서부터 처음 참인 가지만 실행
3. `switch`는 `break`를 빠뜨리면 fall-through 발생
4. 반복 횟수가 정해지면 `for`, 조건 기반이면 `while`, 최소 1회면 `do-while`
5. `break`는 반복 종료, `continue`는 현재 회차만 건너뜀
6. 항상 중괄호를 쓰는 습관이 버그를 막는다

---

## 다음 차시 예고

4차시에서는 함수(function)와 재귀(recursion)를 학습합니다. 함수 프로토타입, 값에 의한 전달, 스택 프레임을 다루고 팩토리얼·피보나치를 반복문 버전과 재귀 버전으로 각각 구현합니다.
