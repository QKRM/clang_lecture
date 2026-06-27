# 1차시 강의 노트 - GitHub Codespaces 환경 세팅 + C언어 첫걸음

## 학습 목표

1. GitHub Codespaces를 설정하고 C언어 개발 환경을 구축할 수 있다.
2. gcc로 C 프로그램을 컴파일하고 실행할 수 있다.
3. C 소스 파일의 기본 구조를 설명할 수 있다.

---

## 1부: GitHub Codespaces 환경 세팅

### 1.1 GitHub Codespaces란?

GitHub Codespaces는 브라우저에서 바로 실행되는 클라우드 개발 환경입니다. 본인 PC에 아무것도 설치하지 않아도 VS Code와 동일한 환경에서 코딩할 수 있습니다.

- **장점**: 어디서든 동일한 환경, 설치 불필요, 즉시 시작 가능
- **우리 강의에서 사용하는 이유**: C언어 컴파일러(gcc)가 기본으로 설치된 Linux 환경을 즉시 사용 가능

### 1.2 Codespaces 생성 단계

**Step 1 - GitHub 계정 준비**
1. https://github.com 에 접속한다.
2. 계정이 없다면 Sign up을 클릭해 계정을 만든다.
3. 이미 있다면 Sign in으로 로그인한다.

**Step 2 - 새 Repository 생성**
1. 우측 상단의 `+` 버튼 클릭 → `New repository`
2. Repository name: `libsbs` (나중에 우리 프로젝트 이름이 됩니다)
3. `Public` 또는 `Private` 선택 (어떤 것이든 무방)
4. `Add a README file` 체크
5. `Create repository` 클릭

**Step 3 - Codespace 생성**
1. Repository 페이지에서 초록색 `<> Code` 버튼 클릭
2. `Codespaces` 탭 클릭
3. `Create codespace on main` 클릭
4. 약 1~2분 대기 (VS Code 환경이 브라우저에서 열립니다)

**Step 4 - 환경 확인**
Codespace가 열리면 하단의 터미널에서 다음을 실행해 gcc가 있는지 확인합니다.

```bash
gcc --version
```

출력 예시:
```
gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0
```

gcc가 있으면 환경 세팅 완료입니다.

### 1.3 터미널 기본 명령어

C언어 개발에 필수적인 터미널 명령어를 먼저 익힙니다.

```bash
pwd          # 현재 디렉토리 경로 확인 (Print Working Directory)
ls           # 현재 디렉토리의 파일 목록 출력
ls -la       # 숨김 파일 포함, 상세 정보 출력
mkdir 폴더명  # 폴더(디렉토리) 생성
cd 폴더명     # 폴더 이동
cd ..        # 상위 폴더로 이동
touch 파일명  # 빈 파일 생성
rm 파일명     # 파일 삭제
clear        # 터미널 화면 지우기
```

**실습**: 터미널에서 다음 순서대로 실행해보기
```bash
mkdir test_folder
cd test_folder
touch hello.c
ls
cd ..
```

---

## 2부: C언어 기초

### 2.1 C언어란?

C언어는 1972년 Dennis Ritchie가 만든 범용 프로그래밍 언어입니다.

- **특징**: 하드웨어에 가까운 저수준 제어 가능, 매우 빠른 실행 속도
- **사용처**: 운영체제(Linux, Windows), 임베디드, 컴파일러 개발
- **이 강의에서**: C언어를 통해 메모리와 포인터의 개념을 기초부터 이해

### 2.2 첫 번째 C 프로그램

터미널에서 아래와 같이 입력합니다.

```bash
touch hello.c
```

VS Code에서 `hello.c` 파일을 열고 다음 코드를 입력합니다.

```c
#include <stdio.h>

int main(void)
{
    printf("Hello, World!\n");
    return (0);
}
```

### 2.3 코드 한 줄씩 분석

**`#include <stdio.h>`**
- `#include`는 전처리기 지시문입니다. 다른 파일의 내용을 이 파일에 포함시킵니다.
- `<stdio.h>`는 Standard Input/Output 헤더 파일입니다.
- `printf` 함수를 사용하려면 이 헤더를 포함해야 합니다.

**`int main(void)`**
- `int`: main 함수가 정수(int)를 반환한다는 뜻
- `main`: C 프로그램의 진입점(entry point). 프로그램은 항상 main에서 시작
- `void`: 매개변수가 없다는 뜻

**`printf("Hello, World!\n");`**
- `printf`: 화면에 출력하는 함수 (stdio.h에 정의됨)
- `"Hello, World!\n"`: 출력할 문자열. `\n`은 줄바꿈(개행) 문자
- 문장 끝에 반드시 `;`(세미콜론)이 붙어야 합니다.

**`return (0);`**
- main 함수가 0을 반환합니다.
- 0은 프로그램이 정상 종료되었음을 의미합니다.
- 운영체제가 이 값을 받아 성공/실패를 판단합니다.

**중괄호 `{ }`**
- 코드 블록의 시작과 끝을 나타냅니다.
- 이 강의에서는 권장 코드 스타일에 따라 여는 중괄호 `{`는 새 줄에 씁니다.

### 2.4 컴파일과 실행

C언어는 컴파일 과정이 필요합니다. 소스 코드(.c) → 기계어(.out 또는 실행 파일)

```
소스 코드(.c) → [전처리] → [컴파일] → [어셈블] → [링킹] → 실행 파일
```

터미널에서 다음 명령어를 실행합니다.

```bash
gcc hello.c -o hello
```

- `gcc`: GNU C Compiler (컴파일러 프로그램)
- `hello.c`: 컴파일할 소스 파일
- `-o hello`: 출력 파일 이름을 `hello`로 지정 (`-o` 옵션)

실행:
```bash
./hello
```

출력:
```
Hello, World!
```

### 2.5 컴파일 옵션 (중요)

이 강의에서는 항상 아래 옵션을 붙여 컴파일합니다.

```bash
gcc -Wall -Wextra -Werror hello.c -o hello
```

| 옵션 | 의미 |
|------|------|
| `-Wall` | 대부분의 경고(warning)를 표시 |
| `-Wextra` | 추가적인 경고를 표시 |
| `-Werror` | 경고를 에러로 처리 (경고가 있으면 컴파일 실패) |

이 옵션들을 사용하는 이유: libsbs 과정의 요구사항이며, 더 안전하고 명확한 코드 작성 습관을 기르기 위함입니다.

### 2.6 printf 서식 지정자

```c
#include <stdio.h>

int main(void)
{
    int age = 25;
    float height = 175.5;
    char initial = 'K';

    printf("나이: %d\n", age);
    printf("키: %.1f\n", height);
    printf("이니셜: %c\n", initial);
    printf("문자열: %s\n", "Hello");
    return (0);
}
```

| 서식 지정자 | 의미 |
|------------|------|
| `%d` | 정수(int) |
| `%f` | 실수(float, double) |
| `%c` | 문자(char) |
| `%s` | 문자열(char 배열) |
| `%p` | 포인터 주소 |

### 2.7 이스케이프 문자

| 이스케이프 | 의미 |
|------------|------|
| `\n` | 줄바꿈 |
| `\t` | 탭 |
| `\\` | 백슬래시 자체 |
| `\"` | 큰따옴표 |
| `\0` | null 문자 (문자열 끝) |

### 2.8 주석

```c
// 한 줄 주석

/*
   여러 줄
   주석
*/
```

코드의 의도를 설명할 때 사용합니다. 컴파일러는 주석을 무시합니다.

---

## 핵심 정리

1. GitHub Codespaces로 설치 없이 C 개발 환경을 구성할 수 있다.
2. C 프로그램은 항상 `main` 함수에서 시작한다.
3. `gcc 파일명.c -o 실행파일명` 으로 컴파일한다.
4. `-Wall -Wextra -Werror` 옵션을 항상 붙이는 습관을 기른다.
5. `printf`로 다양한 형태의 출력을 할 수 있다.

---

## 다음 차시 예고

2차시에서는 C언어의 변수, 자료형, 연산자를 학습합니다. int, char, float 등 각 타입의 크기와 범위, 그리고 형 변환 개념을 다룹니다.
