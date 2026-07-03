# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

16차시 C언어 입문 강의 사이트 (libsbs 표준 라이브러리 직접 구현). GitHub Pages 정적 사이트로 배포 (`https://qkrm.github.io/clang_lecture/`). 대상: Codespaces 환경에서 학습하는 학생.

## Commands

- Regenerate all lesson HTML pages after editing `lecture.md` / `practice.md` / any answer `.c` file in a `session_NN/`:
  ```
  node build_lessons.js
  ```
- Build & test libsbs functions inside a session directory (9~16차시만 해당, `Makefile`/`grade.sh` 존재):
  ```
  bash grade.sh        # 요약 결과
  bash grade.sh -v     # 실패 시 상세 로그(make/link 출력) 포함
  ```
  session_09~14는 개별 함수 채점(각 함수당 컴파일+링크+실행 비교), session_15~16은 `make`로 `libsbs.a` 빌드 후 `tests/test_all.c`(session_16) 또는 `tests/test_link.c`(session_15)를 링크해 통합 동작(`ALL_OK`) 확인.
- 개별 함수 하나만 수동으로 컴파일해 확인하려면 (`-Wall -Wextra -Werror` 필수, 강의 표준):
  ```
  cc -Wall -Wextra -Werror -I. tests/test_<이름>.c sbs_<이름>.c -o /tmp/t && /tmp/t
  ```

## Architecture

### 두 종류의 콘텐츠가 한 파이프라인을 거친다

1. **소스 콘텐츠** (사람이 직접 수정): `session_NN/lecture.md`(강의노트), `session_NN/practice.md`(실습문제), `session_NN/*.c`(정답 코드), `libsbs.h`, `Makefile`.
2. **생성된 콘텐츠** (직접 수정 금지, 항상 `node build_lessons.js`로 재생성): `session_NN/lesson.html`.

`build_lessons.js`는 자체 미니 마크다운 → HTML 변환기(`mdToHtml`)를 갖고 있다(외부 markdown 라이브러리 미사용). 코드 펜스, 표, 목록, blockquote, 헤딩만 지원하는 제한된 서브셋이므로 `lecture.md`/`practice.md`를 쓸 때 이 서브셋 밖의 마크다운 문법(중첩 리스트, 각주 등)은 렌더링되지 않는다는 점 주의.

`answerCards()`가 세션 폴더의 `.c`/`Makefile`/`libsbs.h`를 스캔해 "정답 보기" 토글 카드로 자동 삽입한다 — lecture.md/practice.md에 정답 코드를 직접 붙여넣지 않는다.

### 세션 번호 → 커리큘럼 단계

- **1~8차시**: C 기초 (환경설정 → 자료형 → 제어문 → 함수/재귀 → 포인터 → 배열 → 문자열 → 구조체). `.c` 파일만 존재, `grade.sh`/`Makefile`/`tests/` 없음.
- **9~16차시**: libsbs 구현 (표준 C 라이브러리를 `sbs_` 접두사로 직접 구현). 각 폴더에 `libsbs.h`, `grade.sh`, `tests/test_*.c` 존재. **각 차시는 이전 차시에서 구현한 함수를 폴더별로 복제해 누적**한다 (예: `sbs_memset.c`가 10, 11, 16차시에 각각 따로 존재) — 한 파일을 고치면 다른 세션 폴더의 동일 파일은 자동으로 바뀌지 않으니, 특정 함수의 버그를 고칠 때 어느 세션에서 요청됐는지 확인하고 필요시 여러 폴더에 동일하게 반영해야 한다.
- **session_16**은 9~14차시 32개 함수를 `libsbs.a` 정적 라이브러리로 통합하는 최종 프로젝트 (`Makefile`의 `SRCS` 목록이 통합 대상 32개 함수의 정본).
- `curriculum.md`가 전체 16차시의 학습목표/구현함수 목록의 정본(source of truth) — 새 함수 추가 시 여기도 갱신.

### libsbs 코드 컨벤션 (기존 `.c` 파일에서 관찰됨, `session_16/CODE_REVIEW.md`에 명시)

- 함수명 `sbs_` 접두사 + snake_case, 표준 함수와 동일 시그니처(`man 3 함수명` 기준).
- `return (값)` 형태로 괄호 사용, 변수는 함수 상단 선언, 탭 들여쓰기.
- 컴파일 경고 0개 필수 (`-Wall -Wextra -Werror`).
- 부호 비교는 `unsigned char`로 캐스팅 (memcmp/strncmp류).
- 가능하면 이미 구현한 자기 함수를 재사용 (`sbs_isalnum`→`sbs_isalpha`+`sbs_isdigit`, `sbs_bzero`→`sbs_memset`, `sbs_calloc`→`sbs_memset`, `sbs_strlcpy/strlcat/strdup`→`sbs_strlen` 등).

### 사이트 허브

`index.html` + `site.css`/`site.js`가 루트의 강의 목록 페이지(진입점). `lesson.css`는 모든 `session_NN/lesson.html`이 공유하는 스타일. `catchup/`은 1~8차시를 압축 정리한 별도 단일 페이지(독립적인 HTML/CSS/JS).
