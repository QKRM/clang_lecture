# 8차시 실습 - 구조체와 typedef

## 실습 목표

- 구조체를 선언하고 `.`/`->`로 멤버에 접근한다.
- typedef로 별칭을 만들어 사용한다.
- 구조체 배열과 포인터로 데이터를 관리한다.


> 이번 차시는 실습 분량이 평소의 2배입니다. 기본 과제(1~6)를 먼저 끝내고, 시간이 남으면 심화(7~8)로 갑니다.

---

## 과제 1: 점(Point) 구조체

`point.c` 파일을 만들고 2D 좌표 구조체를 정의해 사용하세요.

요구사항:
- `typedef struct { int x; int y; } t_point;`
- `main`에서 `t_point p = {3, 4};`를 만들고 멤버 출력

출력 예시:
```
p = (3, 4)
```

힌트:
```c
typedef struct {
    int x;
    int y;
} t_point;

t_point p = {3, 4};
printf("p = (%d, %d)\n", p.x, p.y);
```

---

## 과제 2: 학생 구조체

`student.c` 파일을 만들고 학생 정보 구조체를 정의하세요.

요구사항:
- `t_student` (이름 `char name[20]`, 나이 `int age`, 점수 `int score`)
- `main`에서 한 명을 초기화하고 출력
- 이름은 `strcpy`로 채워볼 것

출력 예시:
```
이름: Kim, 나이: 20, 점수: 95
```

힌트:
```c
#include <string.h>

typedef struct {
    char name[20];
    int  age;
    int  score;
} t_student;

t_student s = {"Kim", 20, 95};
printf("이름: %s, 나이: %d, 점수: %d\n", s.name, s.age, s.score);
```

---

## 과제 3: 구조체 포인터 (-> 연산자)

`student_ptr.c` 파일을 만들고 포인터로 멤버에 접근하세요.

요구사항:
- `t_student s`를 만들고 `t_student *p = &s;`
- `p->name`, `p->age`, `p->score`로 출력
- `(*p).age`와 `p->age`가 같음을 주석으로 표시
- `p->age++;`로 나이를 올려 원본 `s`가 바뀌는지 확인

출력 예시:
```
p->age = 20
나이 +1 후 s.age = 21
```

힌트:
```c
t_student *p = &s;
printf("%d\n", p->age);   // (*p).age 와 같음
p->age++;                  // 원본 s.age가 증가
```

---

## 과제 4: 구조체를 함수에 전달

`student_func.c` 파일을 만들고 구조체를 값/포인터로 함수에 넘기세요.

요구사항:
- `void print_student(t_student s)` — 값으로 받아 출력 (읽기)
- `void set_score(t_student *p, int score)` — 포인터로 받아 점수 수정
- `main`에서 호출 후 점수가 바뀌었는지 확인

출력 예시:
```
변경 전: Kim 90
변경 후: Kim 100
```

힌트:
```c
void set_score(t_student *p, int score)
{
    p->score = score;   // 원본 수정
}
```

> 읽기만 하면 값 전달, 바꾸려면 포인터 전달. 5~6차시 원리가 구조체에도 그대로.

---

## 과제 5: 구조체 배열

`class_list.c` 파일을 만들고 여러 학생을 배열로 관리하세요.

요구사항:
- `t_student class[3]`을 3명으로 초기화
- 반복문으로 전체 명단 출력

출력 예시:
```
[0] Kim  20  95
[1] Lee  21  88
[2] Park 22  77
```

힌트:
```c
t_student class[3] = {
    {"Kim", 20, 95},
    {"Lee", 21, 88},
    {"Park", 22, 77}
};
for (int i = 0; i < 3; i++)
    printf("[%d] %s %d %d\n", i, class[i].name, class[i].age, class[i].score);
```

---

## 과제 6: 사각형 넓이

`rectangle.c` 파일을 만들고 사각형 구조체로 넓이와 둘레를 구하세요.

요구사항:
- `t_rect` (`int width; int height;`)
- `int area(t_rect r)` — 넓이
- `int perimeter(t_rect r)` — 둘레
- `main`에서 사각형 하나로 두 함수 호출

출력 예시:
```
사각형 5x3 → 넓이=15, 둘레=16
```

힌트:
```c
int area(t_rect r)
{
    return (r.width * r.height);
}
int perimeter(t_rect r)
{
    return (2 * (r.width + r.height));
}
```

---

## 과제 7: 최고 점수 학생 찾기 (심화, 20분)

`top_student.c` 파일을 만들고 학생 배열에서 점수가 가장 높은 학생을 찾으세요.

요구사항:
- `t_student *find_top(t_student *arr, int size)` — 최고 점수 학생의 **주소** 반환
- `main`에서 배열을 만들고 결과 학생 출력
- 반환된 포인터로 `->`를 써서 출력

출력 예시:
```
최고 점수: Kim (95점)
```

힌트:
```c
t_student *find_top(t_student *arr, int size)
{
    t_student *top = &arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i].score > top->score)
            top = &arr[i];
    return (top);
}
```

> 6차시 max_array를 구조체 버전으로. 값이 아니라 **주소**를 비교·반환하는 점에 주목.

---

## 과제 8: 두 점 사이 거리² (심화, 20분)

`distance.c` 파일을 만들고 두 점 구조체 사이의 거리 제곱을 구하세요.

요구사항:
- `t_point` 두 개를 함수에 전달
- `int dist_squared(t_point a, t_point b)` — `(x2-x1)² + (y2-y1)²` 반환
- (제곱근은 안 함 — 정수로 거리² 만)

출력 예시:
```
(0,0) ~ (3,4) 거리² = 25
(1,1) ~ (4,5) 거리² = 25
```

힌트:
```c
int dist_squared(t_point a, t_point b)
{
    int dx = b.x - a.x;
    int dy = b.y - a.y;
    return (dx * dx + dy * dy);
}
```

생각해보기: 구조체를 값으로 넘기면 멤버가 모두 복사됩니다. 점은 작아서 괜찮지만, 멤버가 많은 큰 구조체라면 포인터가 유리합니다.

---

## 제출 확인 사항

기본 (6과제):
- [ ] `point.c` - 점 구조체 + typedef
- [ ] `student.c` - 학생 구조체, strcpy로 이름
- [ ] `student_ptr.c` - `->` 연산자, 원본 수정
- [ ] `student_func.c` - 값/포인터 전달
- [ ] `class_list.c` - 구조체 배열 순회
- [ ] `rectangle.c` - 넓이/둘레 함수

심화 (2과제):
- [ ] `top_student.c` - 최고 점수 학생 주소 반환
- [ ] `distance.c` - 두 점 거리²

- [ ] 모든 파일: `gcc -Wall -Wextra -Werror` 경고 없이 컴파일
- [ ] 구조체 정의 끝에 `};` 세미콜론을 붙였는가?
