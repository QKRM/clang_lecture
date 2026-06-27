#!/usr/bin/env bash
# =============================================================
# libsbs 11차시 채점 스크립트  (메모리 함수 II)
#   사용법:  bash grade.sh         (요약)
#            bash grade.sh -v      (실패 케이스 상세)
#
#   채점 단계:
#     1) 금지 헤더 검사 — 학생 .c가 <string.h>/<strings.h> 사용 시 0점
#                         (calloc은 <stdlib.h> 허용: malloc/free)
#     2) 컴파일 검사   — gcc -Wall -Wextra -Werror
#     3) 동작 검사     — 표준 함수와 비교 (calloc은 0 초기화 확인)
# =============================================================

CFLAGS="-Wall -Wextra -Werror"
VERBOSE=""
if [ "$1" = "-v" ]; then
	VERBOSE="-v"
fi

# 채점 대상 함수 (모두 malloc으로 새 메모리 생성)
FUNCS="calloc substr strjoin itoa strdup"
# 링크에 필요한 모든 구현 (calloc→memset, substr/strjoin→strlen)
SRC="sbs_calloc.c sbs_substr.c sbs_strjoin.c sbs_itoa.c sbs_strdup.c sbs_memset.c sbs_strlen.c"
FORBIDDEN='string\.h|strings\.h'

TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

pass_count=0
total=0

echo "=== libsbs 11차시 채점 ==="

missing=0
if [ ! -f libsbs.h ]; then
	echo "✗ libsbs.h 파일이 없습니다."
	missing=1
fi
for f in $SRC; do
	if [ ! -f "$f" ]; then
		echo "✗ $f 파일이 없습니다."
		missing=1
	fi
done
if [ "$missing" -eq 1 ]; then
	echo "결과: 0 / 5 통과 (파일 누락)"
	exit 1
fi

# 금지 헤더 검사 (학생 구현 파일만)
for f in $SRC; do
	if grep -Eq "include[[:space:]]*<($FORBIDDEN)>" "$f"; then
		echo "✗ $f : <string.h>/<strings.h> 사용 금지 (직접 구현)"
		echo "결과: 0 / 5 통과 (금지 헤더)"
		exit 1
	fi
done

for name in $FUNCS; do
	total=$((total + 1))
	src="sbs_${name}.c"
	test="tests/test_${name}.c"

	if ! gcc $CFLAGS -c "$src" -I. -o "$TMP/${name}.o" 2> "$TMP/werr"; then
		echo "✗ sbs_${name}   (컴파일 실패: 경고/에러)"
		[ -n "$VERBOSE" ] && sed 's/^/    /' "$TMP/werr"
		continue
	fi

	if ! gcc $CFLAGS -I. "$test" $SRC -o "$TMP/run_${name}" 2> "$TMP/lerr"; then
		echo "✗ sbs_${name}   (테스트 빌드 실패)"
		[ -n "$VERBOSE" ] && sed 's/^/    /' "$TMP/lerr"
		continue
	fi

	out="$("$TMP/run_${name}" $VERBOSE)"
	rc=$?
	score="$(echo "$out" | tail -n1)"
	detail="$(echo "$out" | sed '$d')"

	if [ "$rc" -eq 0 ]; then
		echo "✓ sbs_${name}   ($score)"
		pass_count=$((pass_count + 1))
	else
		echo "✗ sbs_${name}   ($score)"
		[ -n "$VERBOSE" ] && [ -n "$detail" ] && echo "$detail"
	fi
done

echo "-------------------------"
echo "결과: $pass_count / $total 통과"
[ "$pass_count" -eq "$total" ] && exit 0
exit 1
