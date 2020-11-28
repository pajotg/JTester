#!/bin/bash

if [ $# != 3 ]; then
	echo -e "\e[1;91mUsage: run_test.sh [lib] [gcc args] [tests_folder/file]"
	return 1 2>/dev/null
	exit 1
fi

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

lib="$1"
gcc_args="$2"
tests_folder="$3"
utils_lib=$DIR"/utils/utils.a"
utils_include=$DIR"/utils/include"
flags="-Wall -Wextra -Werror"
LIB_PRELOAD="$DIR/utils/PRELOAD/PRELOAD.so"
LIB_PRELOAD_NOP="$DIR/utils/PRELOAD/NOP/libPRELOAD_NOP.so"

mkdir_result=$(mkdir "$DIR/tmp" 2>/dev/null)
test_file="$DIR/tmp/run_test.out"

#make sure out utils is up to date
make_result=$(cd $DIR/utils; make)
make_result=$(cd $DIR/utils/PRELOAD; make)
make_result=$(cd $DIR/utils/PRELOAD/NOP; make)

#echo lib $lib
#echo gcc args $gcc_args
#echo tests_folder $tests_folder
#echo utils_lib $utils_lib
#echo utils_include $utils_include
#echo flags $flags

if [[ "$DEBUG_TEST" ]]; then
	gcc_args="-g $gcc_args"
fi

OK_COLOR=$(printf "\e[1;32m")
KO_COLOR=$(printf "\e[1;31m")
WARN_COLOR=$(printf "\e[1;38;5;208m")
TEST_COLOR=$(printf "\e[1;33m")
ERR_COLOR=$(printf "\e[1;35m")
DEF_COLOR=$(printf "\e[0m")

device=$(uname -s)
case "${device}" in
	Linux*)
		#echo "Linux detected!"
		;;
	Darwin*)
		# echo "OSX detected!"
		;;
	*)
		echo "unknown device: \"${device}\" stopping tests!"
		exit ;;
esac


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

	compile_out=$(cc $flags -o $test_file -I $utils_include $gcc_args $test_name $lib $utils_lib $LIB_PRELOAD_NOP 2>&1)

	exit_code=$?
	base_name=$(basename $test_name)
	#base_name=${base_name:0:-2}
	base_name=${base_name:0:$((${#base_name} - 2))}
	if ((${#base_name} < 8)); then
		base_name+='	'
	fi
	echo -n "$TEST_COLOR$base_name	$DEF_COLOR"
	if [ $exit_code -ne 0 ]; then
		echo "$KO_COLOR[DID_NOT_COMPILE]$DEF_COLOR"
		echo "$compile_out"
		return
	fi
	i=0

	while [ $i -lt 25 ]; do
		case "${device}" in
			Linux*) ret=$(ulimit -t 5; LD_PRELOAD="$LD_PRELOAD $LIB_PRELOAD" $test_file $i);;
			Darwin*)ret=$(cd $(dirname $LIB_PRELOAD_NOP); ulimit -t 5; DYLD_FORCE_FLAT_NAMESPACE=1 DYLD_INSERT_LIBRARIES="$LIB_PRELOAD" $test_file $i);; #DYLD_PRINT_LIBRARIES=1
			*)
				echo "Update run_test case"
				return;;
		esac
		exit_code=$?
		exit_reason=$(get_exit_reason $exit_code)
		i=$(( $i+1 ))

		# return values:
		# start with s = no more tests
		# end with f = no crash
		# test type:
		#	x or X: can crash/should crash
		# after test type result: - or +
		# then we can have a reason or no reason
		# echo
		# echo -n "$ret"

		# timeout/stop
		if [[ $exit_code -eq 137 ]]; then
			echo -n "$KO_COLOR[TIMEOUT]$DEF_COLOR"
			continue
		elif [[ "$ret" == "s"* ]]; then
			break
		fi

		# handle crashes
		if [[ "$ret" != *"f" ]]; then
			if [[ "$ret" == "X"* ]]; then
				echo -n "$OK_COLOR[$exit_reason]$DEF_COLOR"
			elif [[ "$ret" == "x"* ]]; then
				echo -n "$OK_COLOR[$exit_reason]$DEF_COLOR"
			else
				echo -n "$KO_COLOR[$exit_reason]$DEF_COLOR"
			fi
			continue
		fi

		# handle no crash
		if [[ "$ret" == "X"* ]]; then
			echo -n "$KO_COLOR[NO CRASH]$DEF_COLOR"
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
			#message="${ret:1:-1}"
			message="${ret:1:$((${#ret} - 1 - 1))}"
		fi

		# print out OK/KO with prot and message
		if [[ "$ret" == "+"* ]]; then
			# i dont like to print OK if it has a message or is protected
			if [[ "$prot" ]]; then
				if [[ "$message" ]]; then
					echo -n "$OK_COLOR[PROT: $message]$DEF_COLOR"
				else
					echo -n "$OK_COLOR[PROT]$DEF_COLOR"
				fi
			elif [[ "$message" ]]; then
				echo -n "$OK_COLOR[$message]$DEF_COLOR"
			else
				echo -n "$OK_COLOR[OK]$DEF_COLOR"
			fi
		elif [[ "$ret" == "-"* ]]; then
			# i dont like to print KO if it has a message or is protected
			if [[ "$prot" ]]; then
				if [[ "$message" ]]; then
					echo -n "$KO_COLOR[PROT: $message]$DEF_COLOR"
				else
					echo -n "$KO_COLOR[PROT]$DEF_COLOR"
				fi
			elif [[ "$message" ]]; then
				echo -n "$KO_COLOR[$message]$DEF_COLOR"
			else
				echo -n "$KO_COLOR[KO]$DEF_COLOR"
			fi
		elif [[ "$ret" == "?"* ]]; then
			# i dont like to print WARN if it has a message or is protected
			if [[ "$prot" ]]; then
				if [[ "$message" ]]; then
					echo -n "$WARN_COLOR[PROT: $message]$DEF_COLOR"
				else
					echo -n "$WARN_COLOR[PROT]$DEF_COLOR"
				fi
			elif [[ "$message" ]]; then
				echo -n "$WARN_COLOR[$message]$DEF_COLOR"
			else
				echo -n "$WARN_COLOR[WARN]$DEF_COLOR"
			fi
		else
			echo -n "$ERR_COLOR[$ret]$DEF_COLOR"
		fi
	done
	if [[ !"$DEBUG_TEST" ]]; then
		rm $test_file
	fi
	echo
}

test_mains=$(find $tests_folder -type f -name "*.c" | sort)
for f in $test_mains; do
	run_test $f
done