# 10차시 실습 - 메모리 함수 I

## 실습 목표

- `void *`를 `unsigned char *`로 캐스팅해 바이트 단위로 다룬다.
- `sbs_memset`, `sbs_bzero`, `sbs_memcpy`, `sbs_memccpy`를 구현한다.
- 심화: `sbs_memchr`(탐색), `sbs_memcmp`(비교)까지 구현한다.
- `bash grade.sh`로 표준 함수와 비교해 자동 채점한다.

---

## 준비: libsbs.h에 추가

9차시 `libsbs.h`에 4개 프로토타입을 **추가**합니다 (기존 7개는 그대로). 길이 타입 `size_t`를 위해 `# include <stddef.h>`도 추가.

```c
# include <stddef.h>
/* ... 9차시 문자 함수 7개 ... */

void	*sbs_memset(void *b, int c, size_t len);
void	sbs_bzero(void *s, size_t n);
void	*sbs_memcpy(void *dst, const void *src, size_t n);
void	*sbs_memccpy(void *dst, const void *src, int c, size_t n);
void	*sbs_memchr(const void *s, int c, size_t n);
int		sbs_memcmp(const void *s1, const void *s2, size_t n);
```

> 이번 차시 폴더에는 메모리 함수 6개만 채점합니다. 9차시 문자 함수는 가져오지 않아도 됩니다(헤더 선언은 있어도 무방).

---

## 과제 1: sbs_memset

`sbs_memset.c` — `b`부터 `len`바이트를 값 `c`로 채우고 `b` 반환.

---

## 과제 2: sbs_bzero

`sbs_bzero.c` — `s`부터 `n`바이트를 0으로. **반환값 없음(void)**.


---

## 과제 3: sbs_memcpy

`sbs_memcpy.c` — `src`에서 `dst`로 `n`바이트 복사, `dst` 반환.

요구사항:
- `dst`는 `unsigned char *`, `src`는 `const unsigned char *`로 캐스팅
- 한 바이트씩 복사


---

## 과제 4: sbs_memccpy

`sbs_memccpy.c` — `src`를 `dst`로 복사하되 문자 `c`를 만나면 **그 문자까지 복사 후 멈춤**.

반환값 규칙 (가장 헷갈리는 부분):
- `c`를 찾으면 → `dst`에서 **그 문자 다음 위치** 포인터
- 못 찾으면 → `NULL`


---

## 과제 5: sbs_memchr

`sbs_memchr.c` — `s`부터 `n`바이트 안에서 값 `c`(바이트)를 **앞에서부터** 찾는다.

반환값 규칙:
- 찾으면 → 그 바이트를 가리키는 포인터 (`memccpy`와 달리 **다음 위치 아님**)
- `n`바이트 안에 없으면 → `NULL`

요구사항:
- `s`는 `const void *` → `const unsigned char *`로 캐스팅 (읽기만)
- 반환 타입은 `void *`. `const` 포인터를 `void *`로 돌려주려면 캐스팅 필요.

---

## 과제 6: sbs_memcmp

`sbs_memcmp.c` — `s1`과 `s2`의 앞 `n`바이트를 비교.

반환값 규칙 (부호가 핵심):
- 다른 첫 바이트에서 `s1` 바이트 `<` `s2` 바이트 → **음수**
- `>` → **양수**
- `n`바이트 모두 같음 → `0`

요구사항:
- **반드시 `unsigned char`로 비교**. `char`로 하면 0x80 이상 바이트가 음수가 돼 부호가 뒤집힌다.
- 차이값은 `(int)a[i] - (int)b[i]`로 계산.


---

## 과제 7: 채점 실행

```bash
$ bash grade.sh
=== libsbs 10차시 채점 ===
✓ sbs_memset    (20/20)
✓ sbs_bzero     (4/4)
✓ sbs_memcpy    (5/5)
✓ sbs_memccpy   (16/16)
✓ sbs_memchr    (25/25)
✓ sbs_memcmp    (25/25)
결과: 6 / 6 통과
```

실패 시: `bash grade.sh -v`로 어떤 길이/값에서 틀렸는지 확인.

> zip으로 받았으면 `bash grade.sh`로 실행(권한 없어도 됨). `./grade.sh`를 쓰려면 `chmod +x grade.sh`.

---

## 제출 확인 사항

- [ ] `libsbs.h`에 `<stddef.h>` + 4개 프로토타입 추가
- [ ] `sbs_memset.c` - 값으로 채우고 b 반환
- [ ] `sbs_bzero.c` - 0으로 채움 (memset 재사용)
- [ ] `sbs_memcpy.c` - n바이트 복사, const src
- [ ] `sbs_memccpy.c` - c 찾으면 다음 위치, 못 찾으면 NULL
- [ ] `sbs_memchr.c` - c 찾으면 그 위치, 못 찾으면 NULL
- [ ] `sbs_memcmp.c` - unsigned 비교, 부호로 대소, 같으면 0
- [ ] `<string.h>`, `<strings.h>` 미사용
- [ ] `bash grade.sh` → 6 / 6 통과

---

## 더 생각해볼 거리

1. `unsigned char`가 아니라 `char`로 캐스팅하면 어떤 문제가 생길까?
2. `memcpy`로 겹치는 영역을 복사하면 왜 위험할까?
3. `memccpy`에서 `n`이 0이면?
