#!/bin/bash
if [ $# != 1 ] && [ $# != 2 ]; then
	echo -e "\e[1;91mUsage: run_test.sh [path_to_gnl] {what_test}"
	return 1 2>/dev/null
	exit 1
fi

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

path_to_gnl="$1"
test="$2"

prev_mandatory_out=""
prev_bonus_out=""

# test!
# this do_test function basically does 1 test first, and then compares all the other tests to the first one, if they differ, print out the difference, otherwise, print that they are the same
do_tests()
{
	BUFFER_SIZE=$1
	mandatory_out=$($DIR/../run_test.sh "$DIR/gnl_utils.c $path_to_gnl/get_next_line.c $path_to_gnl/get_next_line_utils.c" "-I $DIR -I $path_to_gnl -DBUFFER_SIZE=$BUFFER_SIZE" "$DIR/mandatory")
	bonus_out=$($DIR/../run_test.sh "$DIR/gnl_utils.c $path_to_gnl/get_next_line_bonus.c $path_to_gnl/get_next_line_utils_bonus.c" "-I $DIR -I $path_to_gnl -DBUFFER_SIZE=$BUFFER_SIZE" "$DIR/bonus")
	if [[ "$prev_mandatory_out" ]]; then
		if [[ "$prev_mandatory_out" != "$mandatory_out" || "$prev_bonus_out" != "$bonus_out" ]]; then
			printf "\e[1;36m--	BUFFER_SIZE=$BUFFER_SIZE	differes from initial test!\e[0m\n"
		else
			printf "\e[1;36m--	BUFFER_SIZE=$BUFFER_SIZE	is same as initial test!\e[0m\n"
		fi
		if [[ "$prev_mandatory_out" != "$mandatory_out" ]]; then
			printf "$mandatory_out\n"
		fi
		if [[ "$prev_bonus_out" != "$bonus_out" ]]; then
			printf "$bonus_out\n"
		fi
	else
		printf "\e[1;36m--	Initial test with BUFFER_SIZE=$BUFFER_SIZE\e[0m\n"
		printf "$mandatory_out\n"
		printf "$bonus_out\n"
		prev_mandatory_out="$mandatory_out";
		prev_bonus_out="$bonus_out";
	fi
}

do_tests 32
do_tests 128
do_tests 8
do_tests 2
do_tests 1024
do_tests 16384
printf "\e[1;36m--	Tests completed!\e[0m\n"