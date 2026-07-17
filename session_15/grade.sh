#!/usr/bin/env bash
# =============================================================
# libsbs 15차시 채점 스크립트  (Makefile + ar + libsbs 활용 프로그램)
#   사용법:  bash grade.sh         (요약)
#            bash grade.sh -v      (상세)
#
#   검사 항목:
#     1) make 로 libsbs.a 생성되는가
#     2) ar 아카이브에 오브젝트가 들어있는가
#     3) libsbs.a를 링크해 함수가 동작하는가
#     4) clean / fclean / re 규칙이 동작하는가
#     5) make wordinfo — libsbs를 쓰는 프로그램이 빌드/동작하는가
#     6) make minishell — 셸 껍데기가 빌드/동작하는가 (프롬프트·입력·exit)
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
	echo "결과: 0 / 6 통과"
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
	echo "결과: 0 / 6 통과 (빌드 실패)"
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

# ---- 5) wordinfo (libsbs 활용 프로그램) ----
total=$((total + 1))
if make wordinfo >"$TMP/wordinfo.log" 2>&1 && [ -x ./wordinfo ]; then
	out="$(./wordinfo hello 2>/dev/null)"
	# 길이 5 + 대문자 HELLO 가 출력에 있어야 한다
	if echo "$out" | grep -q '5' && echo "$out" | grep -q 'HELLO'; then
		echo "✓ make wordinfo — libsbs 활용 프로그램 동작"
		pass_count=$((pass_count + 1))
	else
		echo "✗ wordinfo 출력이 예상과 다름"
		[ -n "$VERBOSE" ] && echo "$out" | sed 's/^/    /'
	fi
else
	echo "✗ make wordinfo 빌드 실패"
	[ -n "$VERBOSE" ] && sed 's/^/    /' "$TMP/wordinfo.log"
fi

# ---- 6) minishell (셸 껍데기) ----
total=$((total + 1))
if make minishell >"$TMP/minishell.log" 2>&1 && [ -x ./minishell ]; then
	# "hello" 입력 → 되돌려 출력, "exit" 입력 → 종료 후 bye
	out="$(printf 'hello\nexit\n' | ./minishell 2>/dev/null)"
	if echo "$out" | grep -q 'minishell\$' \
		&& echo "$out" | grep -q 'hello' \
		&& echo "$out" | grep -q 'bye'; then
		echo "✓ make minishell — 프롬프트/입력/exit 동작"
		pass_count=$((pass_count + 1))
	else
		echo "✗ minishell 동작이 예상과 다름 (프롬프트·입력 반향·bye 확인)"
		[ -n "$VERBOSE" ] && echo "$out" | sed 's/^/    /'
	fi
else
	echo "✗ make minishell 빌드 실패"
	[ -n "$VERBOSE" ] && sed 's/^/    /' "$TMP/minishell.log"
fi

# 정리
make fclean >/dev/null 2>&1

echo "-------------------------"
echo "결과: $pass_count / $total 통과"
[ "$pass_count" -eq "$total" ] && exit 0
exit 1
