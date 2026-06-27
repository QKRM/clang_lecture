# C언어 입문 강의 — libsbs 구현 과정

Hello World부터 표준 C 라이브러리(libsbs) 직접 구현까지, 16차시 전 과정 강의 사이트입니다.

## 강의 사이트 (GitHub Pages)

저장소 루트의 `index.html`이 강의 목록 허브입니다. GitHub Pages로 배포하면 바로 열립니다.

- **배포 주소**: `https://qkrm.github.io/clang_lecture/`
- 각 강의 페이지 = 강의노트 + 실습 문제 + 정답 코드(토글) 한 페이지

## 구성

| 단계 | 차시 | 내용 |
|------|------|------|
| C 기초 | 1~8 | 환경 세팅 · 자료형 · 제어문 · 함수/재귀 · 포인터 · 배열 · 문자열 · 구조체 |
| libsbs 구현 | 9~16 | 헤더/문자함수 · 메모리함수 · 동적메모리 · 문자열함수 · Makefile · 종합 통합 |

9~16차시는 `bash grade.sh`로 표준 함수와 비교하는 **자동 채점 스크립트**를 포함합니다.

## 폴더 구조

```
.
├── index.html          # 강의 목록 허브 (사이트 진입점)
├── site.css / site.js  # 허브 스타일·동작
├── lesson.css          # 강의 페이지 공유 스타일
├── build_lessons.js    # 강의 페이지 생성기 (Node)
├── catchup/            # 8차시까지 따라잡기 단일 페이지
└── session_01 ~ 16/    # 차시별 자료 (lecture.md, practice.md, lesson.html, 정답 .c, grade.sh, tests/)
```

## 강의 페이지 다시 생성

`lecture.md` / `practice.md` / 정답 `.c`를 수정한 뒤:

```bash
node build_lessons.js
```

## GitHub Pages 배포 방법

1. 이 저장소를 푸시
2. GitHub → Settings → Pages
3. Source: **Deploy from a branch**, Branch: **main / (root)** 선택 → Save
4. 1~2분 뒤 `https://qkrm.github.io/clang_lecture/` 접속
