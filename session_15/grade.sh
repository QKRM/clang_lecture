#!/usr/bin/env bash
# =============================================================
# libsbs 15차시 채점 스크립트  (Makefile + ar)
#   사용법:  bash grade.sh         (요약)
#            bash grade.sh -v      (상세)
#
#   검사 항목:
#     1) make 로 libsbs.a 생성되는가
#     2) ar 아카이브에 오브젝트가 들어있는가
#     3) libsbs.a를 링크해 함수가 동작하는가
#     4) clean / fclean / re 규칙이 동작하는가
# =============================================================

CFLAGS="-Wall -Wextra -Werror"
VERBOSE=""
if [ "$1" = "-v" ]; then
	VERBOSE="-v"
fi

NAME="libsbs.a"
pass_count=0
total=0

TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

echo "=== libsbs 15차시 채점 (Makefile) ==="

# ---- 필수 파일 ----
if [ ! -f Makefile ]; then
	echo "✗ Makefile이 없습니다."
	echo "결과: 0 / 4 통과"
	exit 1
fi

# 깨끗한 상태에서 시작
make fclean >/dev/null 2>&1

# ---- 1) make로 libsbs.a 생성 ----
total=$((total + 1))
if make >"$TMP/make.log" 2>&1 && [ -f "$NAME" ]; then
	echo "✓ make → libsbs.a 생성"
	pass_count=$((pass_count + 1))
else
	echo "✗ make 실패 또는 libsbs.a 미생성"
	[ -n "$VERBOSE" ] && sed 's/^/    /' "$TMP/make.log"
	echo "결과: 0 / 4 통과 (빌드 실패)"
	exit 1
fi

# ---- 2) 아카이브 내용 확인 ----
total=$((total + 1))
if ar t "$NAME" 2>/dev/null | grep -q '\.o$'; then
	echo "✓ ar 아카이브에 오브젝트 포함"
	pass_count=$((pass_count + 1))
else
	echo "✗ libsbs.a에 .o가 없습니다"
	[ -n "$VERBOSE" ] && ar t "$NAME" | sed 's/^/    /'
fi

# ---- 3) 링크 테스트 ----
total=$((total + 1))
if cc $CFLAGS -I. tests/test_link.c -L. -lsbs -o "$TMP/run" 2>"$TMP/link.log" \
	&& [ "$("$TMP/run")" = "LINK_OK" ]; then
	echo "✓ libsbs.a 링크 + 동작 확인"
	pass_count=$((pass_count + 1))
else
	echo "✗ 링크/동작 실패"
	[ -n "$VERBOSE" ] && sed 's/^/    /' "$TMP/link.log"
fi

# ---- 4) clean / fclean / re ----
total=$((total + 1))
make clean >/dev/null 2>&1
obj_after_clean="$(ls *.o 2>/dev/null | wc -l)"
make fclean >/dev/null 2>&1
lib_after_fclean=0
[ -f "$NAME" ] && lib_after_fclean=1
make re >"$TMP/re.log" 2>&1
re_ok=0
[ -f "$NAME" ] && re_ok=1
if [ "$obj_after_clean" -eq 0 ] && [ "$lib_after_fclean" -eq 0 ] && [ "$re_ok" -eq 1 ]; then
	echo "✓ clean / fclean / re 규칙 동작"
	pass_count=$((pass_count + 1))
else
	echo "✗ clean / fclean / re 규칙 문제"
	[ -n "$VERBOSE" ] && echo "    clean 후 .o=$obj_after_clean, fclean 후 lib=$lib_after_fclean, re 후 lib=$re_ok"
fi

# 정리
make fclean >/dev/null 2>&1

echo "-------------------------"
echo "결과: $pass_count / $total 통과"
[ "$pass_count" -eq "$total" ] && exit 0
exit 1
