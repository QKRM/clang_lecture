# 11차시: 동적 메모리와 malloc

## 학습 목표

1. 스택 vs 힙, malloc이 필요한 이유
2. malloc/free 사용법
3. sbs_calloc 구현
4. malloc으로 문자열 만들기 (substr/strjoin/itoa/strdup)

> 10차시에서 memchr·memcmp를 미리 다뤘으므로, 11차시는 **동적 메모리(malloc)** 에 집중.

---

## 핵심 개념

### 1. 스택 vs 힙

| 구분 | 스택 | 힙 |
|------|------|-----|
| 크기 | 컴파일 시점 고정 | 실행 중 자유 |
| 수명 | 함수 끝나면 소멸 | free 할 때까지 |
| 관리 | 자동 | malloc/free 직접 |

> 실행 중 크기가 정해지거나, 함수가 새 데이터를 만들어 돌려줄 때 malloc.

---

### 2. malloc / free

```c
int *p = malloc(sizeof(int) * 10);
if (p == NULL) return (NULL);   // ① 실패 검사
/* ... 사용 ... */
free(p);                        // ② 반환 (안 하면 누수)
```

문자열은 `malloc(len + 1)` — \0 자리 +1.

흔한 실수: use-after-free, double-free, 주소 잃어버려 누수.

---

### 3. 표준 동적 함수

| 함수 | 역할 |
|------|------|
| malloc(size) | 할당 (초기화 X) |
| calloc(n, size) | 할당 + 0 초기화 |
| realloc(p, size) | 크기 재조정 |
| free(p) | 해제 |

---

### 4. sbs_calloc

```c
total = count * size;
if (count != 0 && total / count != size) return (NULL);  // 오버플로
ptr = malloc(total);
if (ptr == NULL) return (NULL);
sbs_memset(ptr, 0, total);   // 0 초기화
return (ptr);
```

---

### 5. sbs_substr — 부분 문자열

```c
slen = sbs_strlen(s);
if (start >= slen) len = 0;
else if (len > slen - start) len = slen - start;
sub = malloc(len + 1);
/* s[start+i] 복사 + \0 */
```

> start 초과 → "", len 초과 → 끝까지.

---

### 6. sbs_strjoin — 문자열 합치기

```c
res = malloc(l1 + l2 + 1);    // 두 길이 합 + \0
/* s1 복사 후 이어서 s2 복사 + \0 */
```

> 원본은 안 건드리고 **새 메모리**에 결과. malloc 문자열 만들기의 대표 예.

---

### 7. sbs_itoa — 숫자→문자열

```c
if (nb < 0) { sign = 1; nb = -nb; }   // INT_MIN 위해 long
while (tmp >= 10) { tmp /= 10; len++; }   // 자릿수 세기
str = malloc(len + sign + 1);
/* 뒤에서부터 자릿수 채우고, 음수면 str[0]='-' */
```

> 먼저 자릿수를 세어 정확한 크기 할당. INT_MIN은 long으로(14차시 atoi와 같은 함정).

---

### 8. sbs_strdup — 문자열 복제

```c
size_t len = sbs_strlen(s);
char  *dup = malloc(len + 1);
if (dup == NULL) return (NULL);
/* s를 dup로 복사 + \0 */
return (dup);
```

> 한 문자열을 그대로 새 메모리에 복사. 원본과 독립 주소, 호출자가 free.

---

## 실행 전 체크리스트

- [ ] 모든 malloc에 NULL 검사?
- [ ] 문자열은 malloc(len + 1)로 \0 자리 확보?
- [ ] calloc에 오버플로 방어 + 0 초기화?
- [ ] substr/strjoin/strdup이 원본과 독립된 새 메모리?
- [ ] itoa가 INT_MIN을 처리?
- [ ] `bash grade.sh` → 5/5? valgrind 누수 0?

---

## 다음 차시 예고

- **12차시: 문자열 함수 I** (strlen, strlcpy, strlcat)
- 고정 버퍼 안전 처리 (오늘의 동적 strjoin과 대조)

---

## 트러블슈팅

| 증상 | 확인 사항 |
|------|----------|
| 크래시 (use-after-free) | free한 메모리를 다시 쓰지 않기 |
| double free | free는 한 번만 |
| 메모리 누수 | malloc 후 반드시 free (호출자 책임) |
| 문자열 끝 깨짐 | malloc(len + 1), 마지막 \0 |
| itoa가 INT_MIN에서 깨짐 | long으로 받아 부호 처리 |
| substr 빈문자열 안 나옴 | start >= slen이면 len=0 |
