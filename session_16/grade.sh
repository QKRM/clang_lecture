#!/usr/bin/env bash
# =============================================================
# libsbs 16차시 종합 채점 스크립트
#   사용법:  bash grade.sh         (요약)
#            bash grade.sh -v      (상세)
#
#   검사 항목:
#     1) 32개 sbs_*.c 파일 + libsbs.h 존재
#     2) make 로 libsbs.a 빌드 (-Wall -Wextra -Werror)
#     3) libsbs.a를 링크해 32개 함수 통합 동작 (ALL_OK)
#     4) make re / fclean 동작
# =============================================================

CFLAGS="-Wall -Wextra -Werror"
VERBOSE=""
if [ "$1" = "-v" ]; then
	VERBOSE="-v"
fi

NAME="libsbs.a"
EXPECTED=32
pass_count=0
total=0

TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

echo "=== libsbs 16차시 종합 채점 ==="

# ---- 1) 파일 존재 ----
total=$((total + 1))
missing=0
[ -f libsbs.h ] || { echo "  libsbs.h 없음"; missing=1; }
count="$(ls sbs_*.c 2>/dev/null | wc -l)"
if [ "$count" -lt "$EXPECTED" ]; then
	echo "  sbs_*.c 파일이 $count개 (32개 필요)"
	missing=1
fi
if [ "$missing" -eq 0 ]; then
	echo "✓ 파일 구성 (libsbs.h + sbs_*.c $count개)"
	pass_count=$((pass_count + 1))
else
	echo "✗ 파일 구성 미흡"
fi

# ---- 2) make 빌드 ----
total=$((total + 1))
make fclean >/dev/null 2>&1
if [ ! -f Makefile ]; then
	echo "✗ Makefile 없음"
	echo "결과: $pass_count / 4 통과"
	exit 1
fi
if make >"$TMP/make.log" 2>&1 && [ -f "$NAME" ]; then
	echo "✓ make → libsbs.a 빌드 (32개 함수)"
	pass_count=$((pass_count + 1))
else
	echo "✗ make 빌드 실패"
	[ -n "$VERBOSE" ] && sed 's/^/    /' "$TMP/make.log"
	echo "결과: $pass_count / 4 통과 (빌드 실패)"
	exit 1
fi

# ---- 3) 통합 동작 ----
total=$((total + 1))
if cc $CFLAGS -I. tests/test_all.c -L. -lsbs -o "$TMP/run" 2>"$TMP/link.log"; then
	out="$("$TMP/run")"
	if [ "$out" = "ALL_OK" ]; then
		echo "✓ 32개 함수 통합 동작 (ALL_OK)"
		pass_count=$((pass_count + 1))
	else
		echo "✗ 통합 동작 실패"
		[ -n "$VERBOSE" ] && "$TMP/run" | sed 's/^/    /'
	fi
else
	echo "✗ 통합 테스트 링크 실패"
	[ -n "$VERBOSE" ] && sed 's/^/    /' "$TMP/link.log"
fi

# ---- 4) re / fclean ----
total=$((total + 1))
make re >"$TMP/re.log" 2>&1
re_ok=0
[ -f "$NAME" ] && re_ok=1
make fclean >/dev/null 2>&1
fclean_ok=0
[ ! -f "$NAME" ] && fclean_ok=1
if [ "$re_ok" -eq 1 ] && [ "$fclean_ok" -eq 1 ]; then
	echo "✓ make re / fclean 동작"
	pass_count=$((pass_count + 1))
else
	echo "✗ re / fclean 문제 (re=$re_ok fclean=$fclean_ok)"
fi

make fclean >/dev/null 2>&1

echo "-------------------------"
echo "결과: $pass_count / $total 통과"
if [ "$pass_count" -eq "$total" ]; then
	echo "🎉 libsbs 종합 프로젝트 완성!"
	exit 0
fi
exit 1
