# 16차시: libsbs 종합 프로젝트 + 코드 리뷰

## 학습 목표

1. 30개 함수를 libsbs로 통합
2. 통합 Makefile 완성
3. libsbs.h 정리
4. 동료 코드 리뷰

---

## 핵심 개념

### 1. 30개 함수 통합

| 분류 | 개수 | 차시 |
|------|------|------|
| 문자 분류/변환 | 7 | 9 |
| 메모리 함수 | 6 | 10 |
| 동적 메모리(malloc) | 5 | 11 |
| 문자열 함수 | 12 | 12~14 |

> 한 폴더로 모으고 libsbs.h에 프로토타입 정리(차시별 주석).

---

### 2. 통합 Makefile

```makefile
SRCS = sbs_isalpha.c ... sbs_strdup.c   # 30개
OBJS = $(SRCS:.c=.o)
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
```

```bash
make            # libsbs.a
ar t libsbs.a   # 30개 확인
```

---

### 3. 코드 리뷰 체크리스트

- **정확성**: 엣지 케이스, 반환값, \0, 버퍼 범위
- **메모리**: NULL 검사, free, 오버플로, const
- **스타일**: 들여쓰기, snake_case, 경고 0
- **재사용**: 작은 함수 조합(isalnum→isalpha+isdigit 등)

---

### 4. 리뷰 코멘트 원칙

1. 코드를 리뷰(사람 X)
2. 질문형
3. 좋은 점도
4. 구체적
5. 제안형

---

### 5. 함수 재사용 관계

```
isalnum  → isalpha + isdigit
bzero    → memset
calloc   → memset
strlcpy  → strlen
strlcat  → strlen
strdup   → strlen
```

---

## 실행 전 체크리스트

- [ ] sbs_*.c 30개 통합?
- [ ] libsbs.h 전체 프로토타입?
- [ ] make → libsbs.a 경고 없이?
- [ ] test_all → ALL_OK?
- [ ] 코드 리뷰 1회 이상?
- [ ] `bash grade.sh` → 4/4?

---

## 과정 완료

9~16차시: 헤더 → 문자 함수 → 메모리 함수 → 문자열 함수 → Makefile → 통합.
표준 라이브러리를 직접 구현하며 C의 본질(포인터·메모리·빌드)에 닿았다.

**libsbs 과정 수료. 수고하셨습니다.**

---

## 트러블슈팅

| 증상 | 확인 사항 |
|------|----------|
| ar t가 30개 미만 | SRCS에 빠진 파일 |
| 통합 테스트 FAIL | 해당 함수 -v로 점검 |
| make 경고 | 개별 차시에서 -Werror 통과했는지 |
| 링크 실패 | -L. -lsbs, libsbs.a 존재 |
| 함수 충돌 | 중복 정의(같은 함수 2번) |
