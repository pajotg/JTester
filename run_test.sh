#!/bin/bash

if [ $# != 3 ]; then
	echo -e "\e[1;91mUsage: run_test.sh [lib] [include] [tests_folder/file]"
	return 1 2>/dev/null
	exit 1
fi

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

lib=$1
include=$2
tests_folder=$3
utils_lib=$DIR"/utils/utils.a"
utils_include=$DIR"/utils/include"
flags="-Wall -Wextra -Werror"
LD_PRELOAD_LIB="$DIR/utils/LD_PRELOAD/LD_PRELOAD.so"
LD_PRELOAD_NOP_LIB="$DIR/utils/LD_PRELOAD/NOP/LD_PRELOAD_NOP.so"

test_file="$DIR/tmp/run_test"

#make sure out utils is up to date
make_result=$(cd $DIR/utils; make)
make_result=$(cd $DIR/utils/LD_PRELOAD; make)
make_result=$(cd $DIR/utils/LD_PRELOAD/NOP; make)

#echo lib $lib
#echo include $include
#echo tests_folder $tests_folder
#echo utils_lib $utils_lib
#echo utils_include $utils_include
#echo flags $flags

OK_COLOR="\e[1;32m"
KO_COLOR="\e[1;31m"
WARN_COLOR="\e[1;38;5;208m"
TEST_COLOR="\e[1;33m"
ERR_COLOR="\e[1;35m"
DEF_COLOR="\e[0m"

get_exit_reason()
{
	if [[ $1 -eq 0 ]]; then
		echo -n "EXIT"
	elif [[ $1 -eq 137 ]]; then
		echo -n "KILL"
	elif [[ $1 -eq 139 ]]; then
		echo -n "SEG"
	elif [[ $1 -eq 130 ]]; then
		echo -n "Controll C"
	else
		echo -n "Exit code $1"
	fi
}

run_test ()
{
	test_name=$1
	compile_out=$(cc $flags -o $test_file -I $utils_include -I $include $test_name $lib $utils_lib $LD_PRELOAD_NOP_LIB 2>&1)
	exit_code=$?
	base_name=$(basename $test_name)
	base_name=${base_name:0:-2}
	if ((${#base_name} < 8)); then
		base_name+='	'
	fi
	echo -ne "$TEST_COLOR$base_name	$DEF_COLOR"
	if [ $exit_code -ne 0 ]; then
		echo -e "$KO_COLOR[DID_NOT_COMPILE]$DEF_COLOR"
		echo "$compile_out"
		return
	fi
	i=0

	while [ $i -lt 25 ]; do
		ret=$(ulimit -t 5; LD_PRELOAD="$LD_PRELOAD $LD_PRELOAD_LIB" $test_file $i)
		exit_code=$?
		exit_reason=$(get_exit_reason $exit_code)
		i=$(( $i+1 ))

		# return values:
		# start with s = no more tests
		# end with f = no crash
		# test type:
		#	x or X: can crash/should crash
		# after test type result: - or +, in case of - we have -Reason or just -
		#echo
		#echo -n $ret

		# timeout/stop
		if [[ $exit_code -eq 137 ]]; then
			echo -ne "$KO_COLOR[TIMEOUT]$DEF_COLOR"
			continue
		elif [[ "$ret" == "s"* ]]; then
			break
		fi

		# handle crashes
		if [[ "$ret" != *"f" ]]; then
			if [[ "$ret" == "X"* ]]; then
				echo -ne "$OK_COLOR[$exit_reason]$DEF_COLOR"
			elif [[ "$ret" == "x"* ]]; then
				echo -ne "$OK_COLOR[$exit_reason]$DEF_COLOR"
			else
				echo -ne "$KO_COLOR[$exit_reason]$DEF_COLOR"
			fi
			continue
		fi

		# handle no crash
		if [[ "$ret" == "X"* ]]; then
			echo -ne "$KO_COLOR[NO CRASH]$DEF_COLOR"
			continue
		fi

		# skip x
		prot=""
		if [[ "$ret" == "x"* ]]; then
			prot="true"
			ret=${ret:1}
		fi

		# read message
		message="";
		len=${#ret}
		if [[ $len -gt 3 ]]; then
			message="${ret:1:-1}"
		fi

		# print out OK/KO with prot and message
		if [[ "$ret" == "+"* ]]; then
			# i dont like to print OK if it has a message or is protected
			if [[ "$prot" ]]; then
				if [[ "$message" ]]; then
					echo -ne "$OK_COLOR[PROT: $message]$DEF_COLOR"
				else
					echo -ne "$OK_COLOR[PROT]$DEF_COLOR"
				fi
			elif [[ "$message" ]]; then
				echo -ne "$OK_COLOR[$message]$DEF_COLOR"
			else
				echo -ne "$OK_COLOR[OK]$DEF_COLOR"
			fi
		elif [[ "$ret" == "-"* ]]; then
			# i dont like to print KO if it has a message or is protected
			if [[ "$prot" ]]; then
				if [[ "$message" ]]; then
					echo -ne "$KO_COLOR[PROT: $message]$DEF_COLOR"
				else
					echo -ne "$KO_COLOR[PROT]$DEF_COLOR"
				fi
			elif [[ "$message" ]]; then
				echo -ne "$KO_COLOR[$message]$DEF_COLOR"
			else
				echo -ne "$KO_COLOR[KO]$DEF_COLOR"
			fi
		elif [[ "$ret" == "?"* ]]; then
			# i dont like to print WARN if it has a message or is protected
			if [[ "$prot" ]]; then
				if [[ "$message" ]]; then
					echo -ne "$WARN_COLOR[PROT: $message]$DEF_COLOR"
				else
					echo -ne "$WARN_COLOR[PROT]$DEF_COLOR"
				fi
			elif [[ "$message" ]]; then
				echo -ne "$WARN_COLOR[$message]$DEF_COLOR"
			else
				echo -ne "$WARN_COLOR[WARN]$DEF_COLOR"
			fi
		else
			echo -ne "$ERR_COLOR[$ret]$DEF_COLOR"
		fi
	done
	rm $test_file
	echo
}

test_mains=$(find $tests_folder -type f -name "*.c" | sort)
for f in $test_mains; do
	run_test $f
done