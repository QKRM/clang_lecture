#!/usr/bin/env bash
# =============================================================
# libsbs 16차시 종합 채점 스크립트 (미니셸)
#   사용법:  bash grade.sh         (요약)
#            bash grade.sh -v      (상세)
#
#   검사 항목:
#     1) sbs_split.c 금지 헤더 검사 + libsbs.a 빌드
#     2) sbs_split / sbs_free_split 단위 테스트 (SPLIT_OK)
#     3) make minishell — 빌드되는가
#     4) minishell 동작: echo / upper / len / 알수없는명령 / exit
#     5) make clean / fclean / re 동작
# =============================================================

CFLAGS="-Wall -Wextra -Werror"
VERBOSE=""
if [ "$1" = "-v" ]; then
	VERBOSE="-v"
fi

NAME="libsbs.a"
FORBIDDEN='string\.h|strings\.h'
pass_count=0
total=0

TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

echo "=== libsbs 16차시 종합 채점 (미니셸) ==="

if [ ! -f Makefile ]; then
	echo "✗ Makefile이 없습니다."
	echo "결과: 0 / 5 통과"
	exit 1
fi

# ---- 1) 금지 헤더 + libsbs.a 빌드 ----
total=$((total + 1))
if [ -f src/sbs_split.c ] && grep -Eq "include[[:space:]]*<($FORBIDDEN)>" src/sbs_split.c; then
	echo "✗ src/sbs_split.c : <string.h>/<strings.h> 사용 금지 (직접 구현)"
	echo "결과: 0 / 5 통과 (금지 헤더)"
	exit 1
fi
make fclean >/dev/null 2>&1
if make >"$TMP/make.log" 2>&1 && [ -f "$NAME" ]; then
	echo "✓ make → libsbs.a 빌드"
	pass_count=$((pass_count + 1))
else
	echo "✗ make 빌드 실패"
	[ -n "$VERBOSE" ] && sed 's/^/    /' "$TMP/make.log"
	echo "결과: 0 / 5 통과 (빌드 실패)"
	exit 1
fi

# ---- 2) split 단위 테스트 ----
total=$((total + 1))
if cc $CFLAGS -I. tests/test_split.c -L. -lsbs -o "$TMP/tsplit" 2>"$TMP/ts.log" \
	&& [ "$("$TMP/tsplit")" = "SPLIT_OK" ]; then
	echo "✓ sbs_split / sbs_free_split 동작 (SPLIT_OK)"
	pass_count=$((pass_count + 1))
else
	echo "✗ split 테스트 실패"
	[ -n "$VERBOSE" ] && { sed 's/^/    /' "$TMP/ts.log"; "$TMP/tsplit" 2>/dev/null | sed 's/^/    /'; }
fi

# ---- 3) minishell 빌드 ----
total=$((total + 1))
if make minishell >"$TMP/ms.log" 2>&1 && [ -x ./minishell ]; then
	echo "✓ make minishell — 빌드"
	pass_count=$((pass_count + 1))
else
	echo "✗ make minishell 빌드 실패"
	[ -n "$VERBOSE" ] && sed 's/^/    /' "$TMP/ms.log"
fi

# ---- 4) minishell 동작 ----
total=$((total + 1))
if [ -x ./minishell ]; then
	out="$(printf 'echo hello world\nupper abc\nlen hello\nnope\nexit\n' | ./minishell 2>/dev/null)"
	miss=""
	echo "$out" | grep -q 'hello world'            || miss="$miss echo"
	echo "$out" | grep -q 'ABC'                     || miss="$miss upper"
	echo "$out" | grep -q 'hello: 5'                || miss="$miss len"
	echo "$out" | grep -q 'command not found'       || miss="$miss unknown"
	echo "$out" | grep -q 'bye'                      || miss="$miss exit"
	if [ -z "$miss" ]; then
		echo "✓ minishell 동작 (echo/upper/len/미존재/exit)"
		pass_count=$((pass_count + 1))
	else
		echo "✗ minishell 동작 미흡 (누락:$miss )"
		[ -n "$VERBOSE" ] && echo "$out" | sed 's/^/    /'
	fi
else
	echo "✗ minishell 실행 파일 없음"
fi

# ---- 5) clean / fclean / re ----
total=$((total + 1))
make clean >/dev/null 2>&1
obj_after_clean="$(ls obj/*.o 2>/dev/null | wc -l)"
make fclean >/dev/null 2>&1
lib_after_fclean=0
[ -f "$NAME" ] && lib_after_fclean=1
make re >"$TMP/re.log" 2>&1
re_ok=0
[ -f "$NAME" ] && re_ok=1
if [ "$obj_after_clean" -eq 0 ] && [ "$lib_after_fclean" -eq 0 ] && [ "$re_ok" -eq 1 ]; then
	echo "✓ clean / fclean / re 동작"
	pass_count=$((pass_count + 1))
else
	echo "✗ clean / fclean / re 문제 (clean후 .o=$obj_after_clean, fclean후 lib=$lib_after_fclean, re후 lib=$re_ok)"
fi

make fclean >/dev/null 2>&1

echo "-------------------------"
echo "결과: $pass_count / $total 통과"
if [ "$pass_count" -eq "$total" ]; then
	echo "🎉 libsbs 미니셸 완성! 과정을 모두 마쳤습니다."
	exit 0
fi
exit 1
