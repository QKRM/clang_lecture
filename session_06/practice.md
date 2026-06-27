# 6차시 실습 - 배열과 포인터

## 실습 목표

- 배열의 메모리 배치를 주소 출력으로 확인한다.
- 포인터 산술로 배열을 순회한다.
- 버블 정렬을 배열과 포인터로 구현한다.


---

## 과제 1: 배열 주소 확인

`array_address.c` 파일을 만들고 배열이 연속 배치됨을 주소로 확인하세요.

요구사항:
- `int arr[5]`에 10, 20, 30, 40, 50 저장
- 각 원소의 값과 주소(`&arr[i]`)를 출력
- `arr`와 `&arr[0]`이 같은 주소임을 출력

힌트:
```c
for (int i = 0; i < 5; i++)
    printf("arr[%d] = %d, 주소 = %p\n", i, arr[i], (void *)&arr[i]);
printf("arr     = %p\n", (void *)arr);
printf("&arr[0] = %p\n", (void *)&arr[0]);
```

> 주소가 4씩 늘어나는지 확인하세요 (int = 4바이트).

---

## 과제 2: 포인터로 순회

`pointer_walk.c` 파일을 만들고 포인터 산술로 배열을 순회하세요.

요구사항:
- `int arr[5]`에 1~5 저장
- `int *p = arr;`로 포인터 설정
- `*(p + i)` 형태로 모든 원소 출력
- 이어서 `p++`로 포인터를 직접 이동하며 출력

힌트:
```c
int *p = arr;
for (int i = 0; i < 5; i++)
    printf("*(p + %d) = %d\n", i, *(p + i));

p = arr;
while (p < arr + 5)
{
    printf("%d ", *p);
    p++;
}
```

> `*(p + i)`와 `arr[i]`는 완전히 같은 동작입니다.

---

## 과제 3: 버블 정렬

`bubble_sort.c` 파일을 만들고 정수 배열을 오름차순 정렬하세요.

요구사항:
- `void bubble_sort(int *arr, int size)` 구현
- `void print_array(int *arr, int size)` 구현
- 예시 배열 `{5, 2, 9, 1, 7, 3, 8}`을 정렬 전후로 출력

출력 예시:
```
정렬 전: 5 2 9 1 7 3 8
정렬 후: 1 2 3 5 7 8 9
```

힌트:
```c
void bubble_sort(int *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - 1 - i; j++)
            if (arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
}
```

> 정렬 함수가 원본 배열을 직접 바꿉니다(주소 전달). main의 arr이 바뀐 걸 확인하세요.

---

## 과제 4: 합계와 최댓값 (심화, 20분)

`sum_array.c` 파일을 만들고 배열을 받아 합계와 최댓값을 구하는 함수를 작성하세요.

요구사항:
- `int sum_array(int *arr, int size)` — 모든 원소의 합
- `int max_array(int *arr, int size)` — 최댓값
- 예시 배열로 결과 출력

출력 예시 (`{12, 7, 30, 5, 18, 9}`):
```
합계 = 81
최댓값 = 30
```

힌트:
```c
int max_array(int *arr, int size)
{
    int max = arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i] > max)
            max = arr[i];
    return (max);
}
```

---

## 제출 확인 사항

- [ ] `array_address.c` - 배열 연속 배치, arr == &arr[0]
- [ ] `pointer_walk.c` - `*(p+i)`와 `p++` 두 방식 순회
- [ ] `bubble_sort.c` - 오름차순 정렬, 원본 변경 확인
- [ ] `sum_array.c` - 합계 + 최댓값 (심화)
- [ ] 모든 파일: `gcc -Wall -Wextra -Werror` 경고 없이 컴파일
