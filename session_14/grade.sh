#!/usr/bin/env bash
# =============================================================
# libsbs 14차시 채점 스크립트  (문자열 함수 III)
#   사용법:  bash grade.sh         (요약)
#            bash grade.sh -v      (실패 케이스 상세)
#   - strdup은 <stdlib.h>(malloc/free) 허용. <string.h>는 금지.
# =============================================================

CFLAGS="-Wall -Wextra -Werror"
VERBOSE=""
if [ "$1" = "-v" ]; then
	VERBOSE="-v"
fi

FUNCS="strncmp atoi"
SRC="sbs_strncmp.c sbs_atoi.c"
FORBIDDEN='string\.h|strings\.h'

TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

pass_count=0
total=0

echo "=== libsbs 14차시 채점 ==="

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
	echo "결과: 0 / 2 통과 (파일 누락)"
	exit 1
fi

for f in $SRC; do
	if grep -Eq "include[[:space:]]*<($FORBIDDEN)>" "$f"; then
		echo "✗ $f : <string.h>/<strings.h> 사용 금지 (직접 구현)"
		echo "결과: 0 / 2 통과 (금지 헤더)"
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

echo "결과: $pass_count / $total 통과"

# =============================================================
# BONUS (심화) — 큰 정수 변환. 파일이 있을 때만 채점.
#   atol
# =============================================================
BONUS_FUNCS="atol"
BONUS_SRC="sbs_atol.c"

bonus_present=1
for f in $BONUS_SRC; do
	[ -f "$f" ] || bonus_present=0
done

if [ "$bonus_present" -eq 1 ]; then
	echo "--- BONUS (심화) ---"
	bpass=0
	btotal=0
	for name in $BONUS_FUNCS; do
		btotal=$((btotal + 1))
		src="sbs_${name}.c"
		test="tests/test_${name}.c"

		if ! gcc $CFLAGS -c "$src" -I. -o "$TMP/${name}.o" 2> "$TMP/werr"; then
			echo "✗ sbs_${name}   (컴파일 실패: 경고/에러)"
			[ -n "$VERBOSE" ] && sed 's/^/    /' "$TMP/werr"
			continue
		fi
		if ! gcc $CFLAGS -I. "$test" $BONUS_SRC -o "$TMP/run_${name}" 2> "$TMP/lerr"; then
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
			bpass=$((bpass + 1))
		else
			echo "✗ sbs_${name}   ($score)"
			[ -n "$VERBOSE" ] && [ -n "$detail" ] && echo "$detail"
		fi
	done
	echo "보너스: $bpass / $btotal 통과"
fi

echo "-------------------------"
[ "$pass_count" -eq "$total" ] && exit 0
exit 1
