#!/usr/bin/env bash
# =============================================================
# libsbs 13차시 채점 스크립트  (문자열 함수 II)
#   사용법:  bash grade.sh         (요약)
#            bash grade.sh -v      (실패 케이스 상세)
# =============================================================

CFLAGS="-Wall -Wextra -Werror"
VERBOSE=""
if [ "$1" = "-v" ]; then
	VERBOSE="-v"
fi

FUNCS="strchr strrchr strnstr"
SRC="sbs_strchr.c sbs_strrchr.c sbs_strnstr.c"
FORBIDDEN='string\.h|strings\.h'

TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

pass_count=0
total=0

echo "=== libsbs 13차시 채점 ==="

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
	echo "결과: 0 / 3 통과 (파일 누락)"
	exit 1
fi

for f in $SRC; do
	if grep -Eq "include[[:space:]]*<($FORBIDDEN)>" "$f"; then
		echo "✗ $f : <string.h>/<strings.h> 사용 금지 (직접 구현)"
		echo "결과: 0 / 3 통과 (금지 헤더)"
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
# BONUS (심화) — 대소문자 무시 검색. 파일이 있을 때만 채점.
#   strcasestr
# =============================================================
BONUS_FUNCS="strcasestr"
BONUS_SRC="sbs_strcasestr.c"

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
