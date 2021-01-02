#!/bin/bash
if [ $# != 1 ] && [ $# != 2 ]; then
	echo -e "\e[1;91mUsage: run_test.sh [path_to_libft] {what_test}"
	return 1 2>/dev/null
	exit 1
fi

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

path_to_libft="$1"
test="$2"

# make sure the libft we want to test is up to date
make_result=$(cd "$path_to_libft"; make)
make_result=$(cd "$path_to_libft"; make bonus)

# test!
if [ $# == 1 ]; then # No extra args? run all the tests!
	$DIR/../duplicate_include.sh "$path_to_libft"	# Also check duplicate includes
	printf "\e[1;36m--[[        Part 1        ]]--\e[0m\n"
	$DIR/../run_test.sh "$path_to_libft/libft.a" "-I $path_to_libft -I $path_to_libft/include" "$DIR/part1"
	printf "\e[1;36m--[[        Part 2        ]]--\e[0m\n"
	$DIR/../run_test.sh "$path_to_libft/libft.a" "-I $path_to_libft -I $path_to_libft/include" "$DIR/part2"
	printf "\e[1;36m--[[        Bonus         ]]--\e[0m\n"
	$DIR/../run_test.sh "$path_to_libft/libft.a" "-I $path_to_libft -I $path_to_libft/include" "$DIR/bonus"
else # figure out what the extra arg means, does it mean a single test? part1? part2? ft_is*? a external test (not in the test directory)?
	base_name=$(basename "$test")
	if [[ "$base_name" == "$test" ]]; then #if we dont have a path specified assume the test is in this directory
		file=$(find "$DIR" -type f -name "$test")
		if [[ "${file}" == "" ]]; then # if there is no file with that name, try it with a .c
			file=$(find "$DIR" -type f -name "$test.c")
		fi

		if [[ "${file}" ]]; then # if we can find files with that name, test those
			$DIR/../run_test.sh "$path_to_libft/libft.a" "-I $path_to_libft -I $path_to_libft/include" "$file"
		else # otherwise asssume $test contains a folder name
			$DIR/../run_test.sh "$path_to_libft/libft.a" "-I $path_to_libft -I $path_to_libft/include" "$DIR/$test"
		fi
	else #we specified a path, asssume a external test
		$DIR/../run_test.sh "$path_to_libft/libft.a" "-I $path_to_libft -I $path_to_libft/include" "$test"
	fi
fi

# TODO:
# ft_memccpy.c
# ft_memchr.c
# ft_memcmp.c
# ft_memcpy.c
# ft_memmove.c
# ft_strchr.c
# ft_strlcat.c
# ft_strlcpy.c
# ft_strmapi.c
# ft_strncmp.c
# ft_strrchr.c