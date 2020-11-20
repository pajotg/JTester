#!/bin/bash
if [ $# != 1 ] && [ $# != 2 ]; then
	echo -e "\e[1;91mUsage: run_test.sh [path_to_printf] {what_test}"
	return 1 2>/dev/null
	exit 1
fi

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

path_to_printf="$1"
test="$2"

make_result=$(make -C $path_to_printf)

# test!
$DIR/../run_test.sh "$DIR/printf_test_utils.c $path_to_printf/libftprintf.a $path_to_printf/libft/libft.a" "-I $DIR" "$DIR/tests"