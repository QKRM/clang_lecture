# 16차시 강의 노트 - libsbs 종합 프로젝트 + 코드 리뷰

## 학습 목표

1. 9~14차시에서 만든 30개 함수를 하나의 `libsbs`로 통합한다.
2. 전체를 빌드하는 통합 Makefile을 완성한다.
3. 헤더 파일(`libsbs.h`)에 모든 프로토타입을 정리한다.
4. 동료 코드 리뷰로 코드 품질을 점검하고 개선한다.

---

## 1부: 통합 — 30개 함수 모으기

### 1.1 전체 함수 목록

| 분류 | 함수 | 차시 |
|------|------|------|
| 문자 분류/변환 | isalpha, isdigit, isalnum, isascii, isprint, toupper, tolower | 9 |
| 메모리 I | memset, bzero, memcpy, memccpy | 10 |
| 메모리 II | memmove, memchr, memcmp, calloc | 11 |
| 문자열 I | strlen, strlcpy, strlcat | 12 |
| 문자열 II | strchr, strrchr, strnstr | 13 |
| 문자열 III | strncmp, atoi, strdup | 14 |

총 **30개**. 각 차시 폴더의 `sbs_*.c`를 한 폴더로 모읍니다.

### 1.2 libsbs.h 정리

모든 프로토타입을 하나의 헤더에 차시별로 정리합니다(주석으로 구분).

```c
#ifndef LIBSBS_H
# define LIBSBS_H
# include <stddef.h>

/* 9차시 — 문자 분류/변환 */
int     sbs_isalpha(int c);
/* ... */

/* 14차시 — 문자열 함수 III */
char    *sbs_strdup(const char *s);

#endif
```

---

## 2부: 통합 Makefile

모든 소스를 `SRCS`에 나열하고 하나의 `libsbs.a`로 빌드합니다(15차시 문법).

```makefile
NAME    = libsbs.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
AR      = ar
ARFLAGS = rcs

SRCS    = sbs_isalpha.c sbs_isdigit.c ... \
          sbs_strncmp.c sbs_atoi.c sbs_strdup.c
OBJS    = $(SRCS:.c=.o)

all: $(NAME)
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)
%.o: %.c libsbs.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re
```

```bash
$ make          # 30개 컴파일 → libsbs.a
$ ar t libsbs.a # 30개 오브젝트 확인
```

---

## 3부: 코드 리뷰 방법론

### 3.1 코드 리뷰란?

동료가 내 코드를 읽고 개선점을 제안하는 과정입니다. 버그를 미리 잡고, 더 읽기 쉬운 코드를 만듭니다. 실무에서 PR(Pull Request)마다 합니다.

### 3.2 리뷰 체크리스트

**정확성**
- [ ] 엣지 케이스 처리?(빈 문자열, NULL, 0 길이, 경계값)
- [ ] 반환값이 표준 명세와 일치?
- [ ] `\0` 종결, 버퍼 범위 확인?

**메모리 안전**
- [ ] `malloc` 후 NULL 검사?
- [ ] 할당한 메모리를 free(또는 호출자에게 책임 명시)?
- [ ] 버퍼 오버플로우 없음?(범위 확인)

**스타일/일관성**
- [ ] 들여쓰기 일관(탭), 변수는 함수 상단 선언?
- [ ] 함수 이름 `sbs_` 접두사, snake_case?
- [ ] 컴파일 경고 없음(`-Wall -Wextra -Werror`)?

**중복/재사용**
- [ ] 같은 로직 반복 대신 작은 함수 재사용?(예: isalnum이 isalpha 호출)
- [ ] 매직 넘버 대신 의미 있는 표현?

### 3.3 리뷰 코멘트 예절

- 코드를 비판하되 사람을 비판하지 않는다
- "이 부분은 왜 이렇게 했나요?" 처럼 질문형
- 좋은 점도 언급한다
- 구체적으로: "여기 NULL 검사가 빠진 것 같아요" (X "버그 있음")

---

## 4부: 최종 빌드 + 통합 테스트

채점 스크립트가 전체를 검증합니다:

```bash
$ bash grade.sh
=== libsbs 16차시 종합 채점 ===
✓ 파일 구성 (libsbs.h + sbs_*.c 30개)
✓ make → libsbs.a 빌드 (30개 함수)
✓ 30개 함수 통합 동작 (ALL_OK)
✓ make re / fclean 동작
결과: 4 / 4 통과
🎉 libsbs 종합 프로젝트 완성!
```

1. 30개 파일 + 헤더가 모두 있는가
2. `make`로 경고 없이 `libsbs.a`가 빌드되는가
3. 링크해서 30개 함수가 모두 동작하는가
4. `re`/`fclean`이 동작하는가

---

## 핵심 정리

1. 30개 함수를 한 폴더로 모으고 `libsbs.h`에 프로토타입 정리
2. 통합 Makefile의 `SRCS`에 모든 소스 나열 → `libsbs.a`
3. 코드 리뷰: 정확성 · 메모리 안전 · 스타일 · 중복 점검
4. 질문형·구체적·존중하는 리뷰 코멘트
5. 통합 테스트로 30개 함수가 함께 동작함을 확인
6. `make / clean / fclean / re`로 빌드 자동화

---

## 과정을 마치며

9차시부터 한 함수씩, 표준 라이브러리를 직접 구현했습니다. 포인터·메모리·문자열·동적 할당을 손으로 다루며 C의 본질에 닿았습니다. 이제 여러분은:

- 표준 함수의 동작 원리를 안다
- 메모리를 바이트 단위로 다룬다
- 빌드 시스템을 직접 만든다
- 동료의 코드를 읽고 개선한다

이것이 libsbs 과정의 목표였습니다. 수고하셨습니다.
