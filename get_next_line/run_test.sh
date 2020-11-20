#!/bin/bash
if [ $# != 1 ] && [ $# != 2 ]; then
	echo -e "\e[1;91mUsage: run_test.sh [path_to_gnl] {what_test}"
	return 1 2>/dev/null
	exit 1
fi

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

path_to_gnl="$1"
test="$2"

# test!
$DIR/../run_test.sh "$path_to_gnl/get_next_line.c $path_to_gnl/get_next_line_utils.c" "-I $path_to_gnl -DBUFFER_SIZE=32" "$DIR/mandatory"