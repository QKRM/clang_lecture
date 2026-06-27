# 14차시: 문자열 비교와 변환 (strncmp, atoi)

## 학습 목표

1. sbs_strncmp n글자 비교
2. sbs_atoi 부호·공백 처리

> 문자열 복제 `strdup`은 11차시(동적 메모리)에서 다룹니다.

---

## 핵심 개념

### 1. sbs_strncmp

```c
while (i < n)
{
    if (s1[i] != s2[i] || s1[i] == '\0')
        return ((unsigned char)s1[i] - (unsigned char)s2[i]);
    i++;
}
return (0);
```

> n글자까지, \0에서 멈춤(memcmp와 차이). unsigned char로 부호 정확.

---

### 2. sbs_atoi — 처리 순서

```c
while (is_space(str[i])) i++;        // 1. 공백
if (str[i]=='+'||str[i]=='-') {...}  // 2. 부호
while (숫자) result = result*10 + (str[i]-'0');  // 3. 누적
return ((int)(result * sign));
```

| 입력 | 결과 |
|------|------|
| "  -42" | -42 |
| "12ab" | 12 |
| "abc" | 0 |
| "+-5" | 0 |

> '문자'-'0'로 숫자 변환. result는 long으로 완화.

---

## 실행 전 체크리스트

- [ ] strncmp가 \0에서 멈추는가?
- [ ] strncmp를 unsigned char로 비교했는가?
- [ ] atoi가 공백·부호·혼합을 처리하는가?
- [ ] `bash grade.sh` → 2/2?

---

## 다음 차시 예고

- **15차시: Makefile + ar**
- 모든 sbs_*.c를 libsbs.a로 묶기, 빌드 자동화

---

## 트러블슈팅

| 증상 | 확인 사항 |
|------|----------|
| strncmp 부호 반대 | unsigned char 캐스팅 |
| strncmp 길이 무시 | i < n 조건 + \0 종료 |
| atoi 부호 두 개 처리 | 부호는 한 개만 |
| atoi 공백 무시 안 됨 | is_space로 선행 공백 |
