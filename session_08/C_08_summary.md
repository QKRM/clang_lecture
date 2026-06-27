# 8차시: 구조체와 typedef

## 학습 목표

1. 구조체를 선언하고 멤버에 접근할 수 있다
2. `.`과 `->`를 구분해 사용한다
3. typedef로 별칭을 정의한다
4. 구조체 배열·포인터를 사용한다
5. 구조체를 함수에 전달한다

---

## 핵심 개념

### 1. 구조체 = 데이터 묶음

```c
struct student {
    char name[20];
    int  age;
    int  score;
};

struct student s = {"Kim", 20, 95};
```

> 여러 값을 하나로. 설계도 → 변수로 만들어야 메모리 차지.

---

### 2. 멤버 접근 — `.`

```c
s.age = 20;
printf("%d\n", s.age);

strcpy(s.name, "Kim");   // 문자열은 복사 (대입 불가)
```

---

### 3. typedef — 별칭

```c
typedef struct student {
    char name[20];
    int  age;
    int  score;
} t_student;

t_student s;   // struct 생략
```

> 익명 + typedef도 가능. libsbs 관례: `t_` 접두사.

```c
typedef struct {
    int x;
    int y;
} t_point;
```

---

### 4. 구조체 포인터 — `->`

```c
t_student s = {"Kim", 20, 95};
t_student *p = &s;

p->age;      // (*p).age 의 줄임말
(*p).age;    // 같은 뜻
```

| 대상 | 연산자 |
|------|--------|
| 구조체 변수 | `s.age` |
| 구조체 포인터 | `p->age` |

---

### 5. 함수 전달

```c
void print_student(t_student s)         // 값 (복사, 읽기)
void update(t_student *p, int sc)        // 포인터 (원본 수정)
{
    p->score = sc;
}
```

> 큰 구조체/수정 → 포인터. 읽기만 → 값 또는 const 포인터.

---

## 실행 전 체크리스트

- [ ] 구조체 정의 끝에 세미콜론(`};`)을 붙였는가?
- [ ] 문자열 멤버를 `=`가 아니라 `strcpy`로 채웠는가?
- [ ] 포인터 멤버 접근에 `->`를 썼는가? (변수는 `.`)
- [ ] 원본을 바꾸는 함수는 포인터로 받았는가?
- [ ] `-Wall -Wextra -Werror` 경고 없이 컴파일되는가?

---

## 다음 차시 예고

- **9차시: 문자 분류 함수 구현 (libsbs 시작)**
- `sbs_isalpha`, `sbs_isdigit`, `sbs_isalnum`, `sbs_toupper`, `sbs_tolower`
- 7차시 "문자=ASCII 정수"와 범위 판별이 그대로 함수가 됨
- 지금까지의 포인터·문자열·함수가 모두 모인다

---

## 트러블슈팅

| 증상 | 확인 사항 |
|------|----------|
| 정의 후 에러 | 구조체 끝 `};` 세미콜론 누락 |
| `s.name = "..."` 에러 | 배열은 대입 불가 → `strcpy` |
| 포인터 멤버 접근 에러 | `p.age`가 아니라 `p->age` |
| 함수 후 원본 그대로 | 값 전달(복사). 포인터로 넘길 것 |
| 초기화 값이 밀림 | 멤버 선언 순서대로 `{...}` 채우기 |
