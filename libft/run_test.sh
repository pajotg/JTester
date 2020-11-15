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
if [ $# == 1 ]; then
	$DIR/../run_test.sh "$path_to_libft/libft.a" "$path_to_libft" "$DIR"
else
	base_name=$(basename "$test")
	if [[ "$base_name" == "$test" ]]; then #if we dont have a path specified assume the test is in this directory
		file=$(find "$DIR" -type f -name "$test")
		if [[ "${file}" ]]; then # if we can find files with that name, test those
			$DIR/../run_test.sh "$path_to_libft/libft.a" "$path_to_libft" "$file"
		else # otherwise asssume $test contains a folder name
			$DIR/../run_test.sh "$path_to_libft/libft.a" "$path_to_libft" "$DIR/$test"
		fi
	else
		$DIR/../run_test.sh "$path_to_libft/libft.a" "$path_to_libft" "$test"
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

# ft_lstadd_back.c
# ft_lstadd_front.c
# ft_lstclear.c
# ft_lstdelone.c
# ft_lstiter.c
# ft_lstlast.c
# ft_lstmap.c
# ft_lstnew.c
# ft_lstsize.c