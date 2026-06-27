#!/usr/bin/env bash
# =============================================================
# libsbs 9차시 채점 스크립트
#   사용법:  bash grade.sh        (요약)
#            bash grade.sh -v     (실패 케이스 상세)
#
#   채점 단계:
#     1) 금지 헤더 검사 — 학생 .c가 <ctype.h>로 우회하면 0점
#     2) 컴파일 검사   — gcc -Wall -Wextra -Werror, 경고도 실패
#     3) 동작 검사     — 표준 함수(libc)와 0~255 전 범위 비교
# =============================================================

CFLAGS="-Wall -Wextra -Werror"
VERBOSE=""
if [ "$1" = "-v" ]; then
	VERBOSE="-v"
fi

# 채점 대상: (함수이름) 형태. 각 함수는 sbs_<name>.c / tests/test_<name>.c 와 짝.
FUNCS="isalpha isdigit isalnum isascii isprint toupper tolower"

# 학생이 제출하는 모든 구현 파일 (isalnum이 isalpha/isdigit를 호출하므로 전부 링크)
SRC="sbs_isalpha.c sbs_isdigit.c sbs_isalnum.c sbs_isascii.c \
sbs_isprint.c sbs_toupper.c sbs_tolower.c"

# 금지 패턴: 표준 문자 함수 우회
FORBIDDEN='ctype\.h'

TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

pass_count=0
total=0

echo "=== libsbs 9차시 채점 ==="

# ---- 사전 검사: 필수 파일 존재 ----
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
	echo "결과: 0 / 7 통과 (파일 누락)"
	exit 1
fi

# ---- 금지 헤더 검사 (학생 구현 파일만) ----
for f in $SRC; do
	if grep -Eq "include[[:space:]]*<$FORBIDDEN>" "$f"; then
		echo "✗ $f : <ctype.h> 사용 금지 (직접 구현해야 함)"
		echo "결과: 0 / 7 통과 (금지 헤더)"
		exit 1
	fi
done

# ---- 함수별 채점 ----
for name in $FUNCS; do
	total=$((total + 1))
	src="sbs_${name}.c"
	test="tests/test_${name}.c"

	# 2단계: 학생 파일 단독 컴파일 — 경고/에러 검사
	if ! gcc $CFLAGS -c "$src" -I. -o "$TMP/${name}.o" 2> "$TMP/werr"; then
		echo "✗ sbs_${name}   (컴파일 실패: 경고/에러)"
		if [ -n "$VERBOSE" ]; then
			sed 's/^/    /' "$TMP/werr"
		fi
		continue
	fi

	# 3단계: 테스트 + 모든 구현 링크 → 실행
	if ! gcc $CFLAGS -I. "$test" $SRC -o "$TMP/run_${name}" 2> "$TMP/lerr"; then
		# 테스트 빌드 실패 (대개 프로토타입 불일치)
		echo "✗ sbs_${name}   (테스트 빌드 실패)"
		if [ -n "$VERBOSE" ]; then
			sed 's/^/    /' "$TMP/lerr"
		fi
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
		if [ -n "$VERBOSE" ] && [ -n "$detail" ]; then
			echo "$detail"
		fi
	fi
done

echo "결과: $pass_count / $total 통과"

# =============================================================
# BONUS (심화) — fd 출력 함수. 파일이 있을 때만 채점.
#   putchar_fd / putstr_fd / putnbr_fd
#   <unistd.h>(write) 허용. 점수는 별도 표시(기본 7개와 분리).
# =============================================================
BONUS_FUNCS="putchar_fd putstr_fd putnbr_fd"
BONUS_SRC="sbs_putchar_fd.c sbs_putstr_fd.c sbs_putnbr_fd.c"

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

if [ "$pass_count" -eq "$total" ]; then
	exit 0
fi
exit 1
