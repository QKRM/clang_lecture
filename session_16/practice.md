# 16차시 실습 - libsbs 종합 프로젝트 + 코드 리뷰

## 실습 목표

- 9~14차시 26개 함수를 한 폴더로 통합한다.
- 통합 Makefile로 `libsbs.a`를 빌드한다.
- 동료와 코드 리뷰를 주고받는다.
- 최종 통합 테스트를 통과한다.


> 이번 폴더에는 26개 함수 정답 + 통합 Makefile + 통합 테스트가 제공됩니다. 본인이 9~14차시에서 만든 코드로 교체해 빌드해보세요.

---

## 과제 1: 함수 통합

요구사항:
- 9~14차시 각 폴더에서 `sbs_*.c` 26개를 한 폴더로 모은다
- `libsbs.h`에 모든 프로토타입을 차시별로 정리(주석 구분)

체크:
```bash
$ ls sbs_*.c | wc -l
24
```

---

## 과제 2: 통합 Makefile

요구사항:
- `SRCS`에 26개 소스를 모두 나열
- `make` → `libsbs.a` 빌드 (경고 없이)
- `clean / fclean / re` 규칙

확인:
```bash
$ make
$ ar t libsbs.a | wc -l    # 24
$ make re                   # 재빌드
```

---

## 과제 3: 통합 테스트

```bash
$ cc -Wall -Wextra -Werror tests/test_all.c -L. -lsbs -o run
$ ./run
ALL_OK
```

`ALL_OK`가 나오면 26개 함수가 모두 정상 동작합니다. `[FAIL]`이 나오면 해당 함수를 점검하세요.

---

## 과제 4: 코드 리뷰

동료와 짝을 지어 서로의 코드를 리뷰합니다. `CODE_REVIEW.md`(제공) 체크리스트를 사용하세요.

리뷰 절차:
1. 동료의 함수 1~2개를 골라 읽는다
2. 체크리스트 항목을 확인한다 (정확성·메모리·스타일·중복)
3. 코멘트를 작성한다 (질문형·구체적·존중)
4. 받은 피드백으로 코드를 개선한다

리뷰 코멘트 예시:
```
[sbs_strdup.c]
- 좋아요: malloc 실패 시 NULL 검사가 잘 되어 있어요.
- 질문: len + 1로 할당하는 이유를 주석으로 남기면 어떨까요? (\0 자리)
- 제안: sbs_strlen을 재사용하면 길이 측정 루프를 줄일 수 있어요.
```

---

## 과제 5: 최종 채점

```bash
$ bash grade.sh
=== libsbs 16차시 종합 채점 ===
✓ 파일 구성 (libsbs.h + sbs_*.c 26개)
✓ make → libsbs.a 빌드 (26개 함수)
✓ 26개 함수 통합 동작 (ALL_OK)
✓ make re / fclean 동작
결과: 4 / 4 통과
🎉 libsbs 종합 프로젝트 완성!
```

---

## 제출 확인 사항

- [ ] 26개 `sbs_*.c` 한 폴더에 통합
- [ ] `libsbs.h` 전체 프로토타입 정리
- [ ] 통합 Makefile (`make` → libsbs.a, 경고 없음)
- [ ] `tests/test_all.c` 링크 → `ALL_OK`
- [ ] 동료 코드 리뷰 1회 이상 (주고/받기)
- [ ] `bash grade.sh` → 4 / 4 통과

---

## 더 생각해볼 거리

1. 26개 함수 중 다른 함수를 재사용하는 것은? (isalnum→isalpha/isdigit, bzero→memset, calloc→memset, strlcpy/cat/dup→strlen)
2. 라이브러리를 다른 프로젝트에서 쓰려면 무엇이 필요한가? (libsbs.a + libsbs.h)
3. 다음에 추가하고 싶은 함수는? (printf, split, itoa 등 — 확장 과제)
