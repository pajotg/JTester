#!/bin/bash

if [[ $# -gt 2 || $# -eq 0 ]]; then
	echo -e "\e[1;91mUsage: duplicate_include.sh [include] {tests_folder/file}\e[0m"
	return 1 2>/dev/null
	exit 1
fi

include_folder="$1"
if [[ $# -gt 1 ]]; then
	tests_folder="$2"
else
	tests_folder="$1"
fi

# sets the includes value
get_includes_raw() {
	test_file="$1"
	includes=$(cat "$test_file" | egrep "#\s*include" | tr -d "#" | tr " " "\n" | egrep -v "include" | egrep ".")
	#echo -e "\n\nRaw includes from: $test_file: $includes\n\n"
}

containsElement() {
	local e match="$1"
	shift
	for e; do [[ "$e" == "$match" ]] && return 0; done
	return 1
}

get_includes() {
	local file_name="$1"
	#echo "Getting includes of: $file_name"

	local local_includes=()	# the includes this file contains
	local copy_includes=()	# copy of the first raw call

	local get_includes_ret=0

	get_includes_raw "$file_name"
	for header in $includes; do
		#echo "	Raw header: $header"

		containsElement "$header" "${local_includes[@]}"
		if [[ $? == 0 ]]; then
			echo "litteral duplicate header found in $file_name: $header, what?"
			get_includes_ret=1
		else
			local_includes+=("$header")
			copy_includes+=("$header")
		fi
	done

	local dir_name=$(dirname $file_name)
	for header in ${copy_includes[@]}; do
		if [[ "$header" == "\""* ]]; then
			# this is a user defined header file
			header="${header:1:$((${#header} - 1 - 1))}"	# remove the quotes
			#echo "	Expanding  header: $header"

			if [[ "$header" == "."* ]]; then
				get_includes "$dir_name/$header"
			elif [[ "$header" == *"/"* ]]; then
				# i dont know what to do with this, sometimes this is a system file, like "malloc/malloc.h", or maybe you are putting c files with your header directory using a relative path? (why would you do that?)
				echo "Could not find header: $header in $file_name!"
				includes=() # Assume this header contains nothing
			else
				found=$(find $include_folder -type f -name "$header" | sort)
				if [[ "${found}" ]]; then
					get_includes "$found"
				else
					echo "Could not find header: $header in $file_name!"
					includes=() # Assume this header contains nothing
				fi
			fi

			#local_includes+=( "${$includes[@]}" )
			for copy in ${includes[@]}; do
				containsElement "$copy" "${local_includes[@]}"
				if [[ $? == 0 ]]; then
					echo "Duplicate header found in $file_name: $copy"
					get_includes_ret=1
				else
					local_includes+=("$copy")
				fi
			done
		fi
	done

	#includes=( "${local_includes[@]}" )	# the includes this file contains
	includes=()
	for copy in ${local_includes[@]}; do
		includes+=( "$copy" )
	done

	return $get_includes_ret
}

ret=0

test_c=$(find $tests_folder -type f -name "*.c" | sort)
for f in $test_c; do
	#echo "Checking file: $f"
	get_includes $f
	if [[ $? -ne 0 ]]; then
		ret=1
	fi
done

test_h=$(find $include_folder -type f -name "*.h" | sort)
for f in $test_h; do
	#echo "Checking header: $f"
	get_includes $f
	if [[ $? -ne 0 ]]; then
		ret=1
	fi
done

exit $ret