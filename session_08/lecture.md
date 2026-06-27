# 8차시 강의 노트 - 구조체와 typedef

## 학습 목표

1. 구조체(struct)를 선언하고 멤버에 접근할 수 있다.
2. `.`(점)과 `->`(화살표) 연산자를 구분해 사용할 수 있다.
3. typedef로 타입 별칭을 정의할 수 있다.
4. 구조체 배열과 구조체 포인터를 사용할 수 있다.
5. 구조체를 함수에 전달할 수 있다.

---

## 1부: 구조체란?

### 1.1 서로 다른 데이터를 하나로 묶기

지금까지 변수는 값 하나만 담았습니다. 구조체는 **여러 값을 하나의 묶음**으로 만듭니다. 예: 학생 = 이름 + 나이 + 점수.

```c
struct student {
    char name[20];
    int  age;
    int  score;
};
```

이건 "설계도"입니다. 실제 변수를 만들어야 메모리를 차지합니다.

```c
struct student s1;          // 변수 선언
struct student s2 = {"Kim", 20, 95};  // 선언 + 초기화
```

### 1.2 왜 쓰나?

관련된 데이터를 한 덩어리로 다루면 코드가 명확해집니다. 학생 100명을 `name[100]`, `age[100]`, `score[100]` 세 배열로 관리하는 것보다 `struct student arr[100]` 하나가 깔끔합니다.

---

## 2부: 멤버 접근 — `.` 연산자

### 2.1 점으로 멤버에 접근

구조체 변수의 멤버는 `.`(점)으로 읽고 씁니다.

```c
struct student s1;

s1.age = 20;              // 쓰기
s1.score = 95;
printf("%d\n", s1.age);   // 읽기 → 20
```

문자열 멤버는 배열이므로 대입이 아니라 복사해야 합니다(7차시).

```c
// s1.name = "Kim";   // 에러! 배열은 통째 대입 불가
strcpy(s1.name, "Kim");  // 복사로 채움
```

### 2.2 초기화

```c
struct student s = {"Lee", 21, 88};
// name="Lee", age=21, score=88 순서대로
```

---

## 3부: typedef — 타입에 별칭

### 3.1 struct를 매번 쓰기 번거롭다

`struct student`를 매번 쓰는 대신, `typedef`로 짧은 별칭을 답니다.

```c
typedef struct student {
    char name[20];
    int  age;
    int  score;
} t_student;

// 이제 struct 없이 t_student로 쓴다
t_student s1;
t_student s2 = {"Park", 22, 77};
```

| 표현 | 의미 |
|------|------|
| `struct student s;` | typedef 없이 |
| `t_student s;` | typedef로 짧게 |

> libsbs 코드 규칙에서는 타입 별칭에 `t_` 접두사를 자주 씁니다 (`t_student`, `t_point`). 일관성을 위한 관례입니다.

### 3.2 익명 구조체 + typedef

이름을 생략하고 별칭만 둘 수도 있습니다.

```c
typedef struct {
    int x;
    int y;
} t_point;

t_point p = {3, 4};
```

---

## 4부: 구조체 포인터 — `->` 연산자

### 4.1 포인터로 멤버 접근

구조체 포인터에서는 `.` 대신 `->`(화살표)로 멤버에 접근합니다.

```c
t_student s = {"Kim", 20, 95};
t_student *p = &s;

printf("%d\n", (*p).age);   // 방법 1: 역참조 후 점
printf("%d\n", p->age);     // 방법 2: 화살표 (같은 뜻, 더 간결)
```

`p->age`는 `(*p).age`의 줄임말입니다. 거의 항상 `->`를 씁니다.

| 상황 | 연산자 |
|------|--------|
| 구조체 변수 | `s.age` |
| 구조체 포인터 | `p->age` |

### 4.2 왜 포인터를 쓰나?

구조체가 크면 함수에 통째로 복사하는 것은 비쌉니다. 포인터(주소)를 넘기면 복사 없이 원본에 접근합니다(5~6차시 원리).

```c
void grow_up(t_student *p)
{
    p->age++;       // 원본의 age가 증가
}
```

---

## 5부: 구조체 배열과 함수 전달

### 5.1 구조체 배열

```c
t_student class[3] = {
    {"Kim", 20, 95},
    {"Lee", 21, 88},
    {"Park", 22, 77}
};

for (int i = 0; i < 3; i++)
    printf("%s %d\n", class[i].name, class[i].score);
```

`class[i]`는 구조체 변수이므로 `.`로 접근합니다.

### 5.2 값 전달 vs 포인터 전달

```c
void print_student(t_student s)    // 값 — 복사본 (원본 못 바꿈)
{
    printf("%s\n", s.name);
}

void update_score(t_student *p, int new_score)  // 포인터 — 원본 수정
{
    p->score = new_score;
}
```

읽기만 하면 값(또는 `const` 포인터), 바꾸려면 포인터로 넘깁니다.

---

## 핵심 정리

1. 구조체 = 서로 다른 데이터를 하나로 묶는 설계도
2. 구조체 변수 멤버는 `.`(점)으로 접근
3. `typedef`로 별칭을 달아 `struct` 생략 (`t_student`)
4. 구조체 포인터는 `->`(화살표)로 접근 — `p->age` = `(*p).age`
5. 큰 구조체나 수정이 필요하면 포인터로 전달
6. 문자열 멤버는 대입이 아니라 복사(strcpy)로 채운다

---

## 다음 차시 예고

9차시부터 본격적인 libsbs 구현이 시작됩니다. 첫 주제는 문자 분류 함수(`sbs_isalpha`, `sbs_isdigit`, `sbs_toupper` 등)입니다. 7차시에서 본 "문자는 ASCII 정수"와 범위 판별이 그대로 함수가 됩니다. 지금까지 배운 포인터·문자열·함수가 모두 모입니다.
