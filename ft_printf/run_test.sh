#!/bin/bash
if [ $# != 1 ] && [ $# != 2 ]; then
	echo -e "\e[1;91mUsage: run_test.sh [path_to_printf] {libname}"
	return 1 2>/dev/null
	exit 1
fi

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

path_to_printf="$1"
lib_name="$2"
if [[ "$lib_name" == "" ]]; then
	lib_name="libftprintf"
fi

make_result=$(make -C $path_to_printf)
make_result=$(make bonus -C $path_to_printf)

# test!
$DIR/../duplicate_include.sh "$path_to_printf"	# Also check duplicate includes

$DIR/../run_test.sh "$DIR/printf_test_utils.c $path_to_printf/$lib_name.a" "-I $DIR" "$DIR/tests"