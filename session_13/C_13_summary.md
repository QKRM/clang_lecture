# 13차시: 문자열 함수 II (strchr, strrchr, strnstr)

## 학습 목표

1. sbs_strchr 순방향 검색 + \0 처리
2. sbs_strrchr 역방향 검색(마지막 등장)
3. sbs_strnstr 부분 문자열 검색(len 제한)

---

## 핵심 개념

### 1. sbs_strchr — 순방향

```c
while (s[i])
{
    if (s[i] == (char)c)
        return ((char *)(s + i));
    i++;
}
if ((char)c == '\0')
    return ((char *)(s + i));   // \0도 검색!
return (NULL);
```

> 첫 등장 위치. c가 \0이면 끝 위치 반환.

---

### 2. sbs_strrchr — 역방향

```c
while (s[i]) i++;               // 끝으로
if ((char)c == '\0')
    return ((char *)(s + i));
while (i > 0)
{
    i--;
    if (s[i] == (char)c)
        return ((char *)(s + i));
}
return (NULL);
```

| 함수 | 방향 | 결과 |
|------|------|------|
| strchr | 앞→뒤 | 첫 등장 |
| strrchr | 뒤→앞 | 마지막 등장 |

---

### 3. sbs_strnstr — 부분 문자열

```c
if (little[0] == '\0')
    return ((char *)big);       // 빈 needle
while (big[i] && i < len)
{
    j = 0;
    while (big[i+j] && i+j < len && big[i+j] == little[j])
        j++;
    if (little[j] == '\0')
        return ((char *)(big + i));   // 발견
    i++;
}
return (NULL);
```

> 이중 루프 + i+j < len(범위 제한). 빈 needle은 즉시 big.

---

## 실행 전 체크리스트

- [ ] strchr가 \0 검색을 처리하는가?
- [ ] strrchr가 마지막 등장을 반환하는가?
- [ ] strnstr가 빈 needle에 big을 반환하는가?
- [ ] strnstr가 i+j < len으로 범위를 지키는가?
- [ ] `bash grade.sh` → 3/3?

---

## 다음 차시 예고

- **14차시: 문자열 함수 III** (sbs_strncmp, sbs_atoi, sbs_strdup)
- 비교, 문자열→정수(부호·공백·오버플로), 동적 복제

---

## 트러블슈팅

| 증상 | 확인 사항 |
|------|----------|
| strchr가 \0 못 찾음 | 루프 후 \0 검색 분기 추가 |
| strrchr가 첫 등장 반환 | 뒤에서부터 순회 |
| strnstr 범위 초과 | i+j < len 조건 |
| 빈 needle에 NULL | little[0]=='\0'면 big |
| const 캐스팅 경고 | (char *)(s + i) |
