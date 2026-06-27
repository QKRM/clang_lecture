# 3차시: 조건문과 반복문

## 학습 목표

1. `if / else if / else`로 조건 분기를 구현할 수 있다
2. `switch`의 동작과 `break`(fall-through)를 설명할 수 있다
3. `for`, `while`, `do-while`을 상황에 맞게 선택할 수 있다
4. `break`, `continue`로 반복 흐름을 제어할 수 있다
5. 중첩 반복문으로 2차원 패턴을 출력할 수 있다

---

## 핵심 개념

### 1. 참/거짓의 기준

C에는 기본 boolean 타입이 없다. **0은 거짓, 0이 아닌 모든 값은 참.**

```c
if (1)   // 참
if (0)   // 거짓
if (-5)  // 참 (0이 아니므로)
```

---

### 2. if / else if / else

위에서부터 처음으로 참인 가지 하나만 실행.

```c
if (score >= 90)
    printf("A\n");
else if (score >= 80)
    printf("B\n");
else
    printf("F\n");
```

> 중괄호를 생략하면 바로 다음 한 문장만 묶인다 → 항상 `{}`를 쓰는 습관

---

### 3. switch

```c
switch (day)
{
    case 1:
        printf("월\n");
        break;      // 없으면 다음 case로 흘러내림(fall-through)
    case 2:
        printf("화\n");
        break;
    default:
        printf("기타\n");
}
```

| 규칙 | 내용 |
|------|------|
| `break` 누락 | 다음 case로 fall-through |
| `case` 라벨 | 상수만 가능 |
| 비교 대상 | 정수형(int, char)만 |

---

### 4. 반복문 3종

```c
/* for — 횟수가 정해짐 */
for (int i = 0; i < 5; i++)
    printf("%d ", i);     // 0 1 2 3 4

/* while — 조건 기반 */
int i = 0;
while (i < 5)
{
    printf("%d ", i);
    i++;
}

/* do-while — 최소 1회 실행 */
int n = 10;
do {
    printf("%d ", n);     // 10 (조건 거짓이어도 1회)
} while (n < 5);
```

| 상황 | 추천 |
|------|------|
| 반복 횟수 정해짐 | `for` |
| 조건 기반 (입력/탐색) | `while` |
| 최소 1회 보장 | `do-while` |

> libsbs 문자열/메모리 함수는 길이를 모르므로 `while (s[i])` 형태를 자주 쓴다.

---

### 5. break / continue

```c
for (int i = 0; i < 100; i++)
{
    if (i == 5)
        break;       // 반복 전체 종료 → 0 1 2 3 4
    printf("%d ", i);
}

for (int i = 0; i < 10; i++)
{
    if (i % 2 == 0)
        continue;    // 현재 회차만 건너뜀 → 1 3 5 7 9
    printf("%d ", i);
}
```

| 키워드 | 동작 |
|--------|------|
| `break` | 반복문 전체 종료 |
| `continue` | 현재 회차 건너뛰고 다음으로 |

---

### 6. 중첩 반복문

```c
for (int dan = 2; dan <= 9; dan++)
{
    for (int i = 1; i <= 9; i++)
        printf("%d x %d = %d\n", dan, i, dan * i);
    printf("\n");
}
```

바깥 루프 1회 = 안쪽 루프 전체 실행.

---

## 실습 코드

**fizzbuzz.c 핵심** — 15의 배수를 먼저 검사:
```c
if (i % 15 == 0)      printf("FizzBuzz\n");
else if (i % 3 == 0)  printf("Fizz\n");
else if (i % 5 == 0)  printf("Buzz\n");
else                  printf("%d\n", i);
```

**guess_number.c 핵심** — 무한 루프 + break:
```c
while (1)
{
    scanf("%d", &guess);
    tries++;
    if (guess > answer)      printf("더 작게!\n");
    else if (guess < answer) printf("더 크게!\n");
    else { printf("정답! %d번\n", tries); break; }
}
```

---

## 실행 전 체크리스트

- [ ] `if` 가지 순서가 맞는가? (FizzBuzz는 15 먼저)
- [ ] `switch`의 각 `case`에 `break`를 넣었는가?
- [ ] `while` 루프 안에 종료 조건을 바꾸는 코드(`i++`)가 있는가? (무한 루프 방지)
- [ ] 중괄호 없이 묶인 줄이 의도와 일치하는가?
- [ ] `-Wall -Wextra -Werror` 경고 없이 컴파일되는가?

---

## 다음 차시 예고

- **4차시: 함수와 재귀**
- 함수 프로토타입, 매개변수와 반환값, 값에 의한 전달(pass by value)
- 스택 프레임, 재귀 개념
- 실습: 팩토리얼, 피보나치 (반복문 버전 vs 재귀 버전)

---

## 트러블슈팅

| 증상 | 확인 사항 |
|------|----------|
| FizzBuzz에서 15가 Fizz로만 나옴 | `i % 15 == 0`을 가장 먼저 검사 |
| switch가 여러 case를 다 출력 | 각 case 끝에 `break` 누락 |
| 프로그램이 멈춤(무한 루프) | while 조건을 바꾸는 코드 누락 |
| `if` 다음 줄이 항상 실행됨 | 중괄호 없이 두 문장 → `{}`로 감싸기 |
| 구구단 단 사이 줄바꿈 없음 | 바깥 루프 끝에 `printf("\n")` |
