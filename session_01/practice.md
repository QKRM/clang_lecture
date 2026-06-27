# 1차시 실습 - 환경 세팅 + Hello World 변형

## 실습 목표

- GitHub Codespaces를 직접 생성하고 개발 환경을 세팅한다.
- gcc 컴파일 명령어를 익힌다.
- printf를 활용한 다양한 출력 형태를 실습한다.


---

## Step 1: Codespaces 환경 직접 세팅

아래 순서를 따라 직접 환경을 구성하세요.

### 1-1. GitHub Repository 생성

1. https://github.com 접속 및 로그인
2. 우측 상단 `+` → `New repository`
3. Repository name: `libsbs`
4. `Add a README file` 체크
5. `Create repository` 클릭

### 1-2. Codespace 열기

1. Repository 페이지 → `<> Code` 버튼
2. `Codespaces` 탭 → `Create codespace on main`
3. 브라우저에서 VS Code 환경이 열릴 때까지 대기

### 1-3. 환경 확인 체크리스트

터미널에서 아래 명령어를 실행하고 결과를 확인하세요.

```bash
# gcc 버전 확인
gcc --version

# 현재 위치 확인
pwd

# 파일 목록 확인
ls -la
```

체크리스트:
- [ ] Codespace가 정상적으로 열렸다.
- [ ] `gcc --version` 명령어가 버전 정보를 출력했다.
- [ ] 터미널에서 명령어를 입력할 수 있다.

---

## Step 2: Hello World 컴파일 및 실행

### 2-1. 파일 생성 및 코드 작성

터미널에서:
```bash
touch hello.c
```

VS Code에서 `hello.c`를 열고 아래 코드를 입력하세요 (직접 타이핑, 복사 붙여넣기 금지):

```c
#include <stdio.h>

int main(void)
{
    printf("Hello, World!\n");
    return (0);
}
```

### 2-2. 컴파일 및 실행

```bash
gcc -Wall -Wextra -Werror hello.c -o hello
./hello
```

예상 출력:
```
Hello, World!
```

---

## Step 3: printf 활용 실습

### 과제 3-1: 자기소개 출력 프로그램

`intro.c` 파일을 만들고, 아래 형식으로 자기소개를 출력하는 프로그램을 작성하세요.

출력 예시 (본인 정보로 교체):
```
=== 자기소개 ===
이름: 홍길동
나이: 25
좋아하는 프로그래밍 언어: C
목표: libsbs 완성
================
```

요구사항:
- 변수를 활용해서 이름, 나이를 저장하고 출력할 것
- `%s`, `%d` 서식 지정자를 사용할 것
- 컴파일 옵션: `-Wall -Wextra -Werror`

### 과제 3-2: 이스케이프 문자 실험

`escape.c` 파일을 만들고 아래 코드를 작성해 각 이스케이프 문자의 동작을 확인하세요.

```c
#include <stdio.h>

int main(void)
{
    printf("줄바꿈 테스트:\n첫 번째 줄\n두 번째 줄\n");
    printf("탭 테스트:\t[탭 뒤]\n");
    printf("따옴표 테스트: \"Hello\"\n");
    printf("백슬래시 테스트: \\\n");
    return (0);
}
```

각 출력 결과를 직접 설명해보세요:
1. `\n`의 효과:
2. `\t`의 효과:
3. `\"`의 효과:
4. `\\`의 효과:

### 과제 3-3: 도형 출력 (심화)

`shapes.c` 파일을 만들고 printf만으로 아래 도형을 출력하세요.

```
*****
*   *
*   *
*   *
*****
```

힌트: `*`와 공백을 적절히 조합해서 출력합니다.

---

## 제출 확인 사항

- [ ] `hello.c` - 컴파일 및 실행 성공
- [ ] `intro.c` - 자기소개 출력 (변수 사용)
- [ ] `escape.c` - 이스케이프 문자 동작 확인
- [ ] `shapes.c` - 도형 출력 (선택)
- [ ] 모든 파일이 `-Wall -Wextra -Werror` 옵션으로 경고 없이 컴파일됨

---

## 자주 나오는 오류와 해결법

| 오류 메시지 | 원인 | 해결 방법 |
|------------|------|-----------|
| `error: 'printf' undeclared` | `#include <stdio.h>` 누락 | 첫 줄에 include 추가 |
| `error: expected ';'` | 세미콜론 누락 | 각 문장 끝에 `;` 추가 |
| `bash: ./hello: No such file or directory` | 컴파일 안 됨 | 먼저 gcc 컴파일 실행 |
| `warning: unused variable` | 선언했지만 사용 안 한 변수 | 변수를 사용하거나 삭제 |
