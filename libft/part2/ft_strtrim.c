#include "libft.h"
#include "test_utils.h"
#include <stdio.h>
#include <string.h>

void do_test(char* input, char* set, char* expected, char* message, char* msize_message)
{
	tu_eq_str_msize(message, msize_message, ft_strtrim(input, set), expected, true, false);
}

int main(int argc, char *argv[])
{
	TEST_START
		do_test("Hello World", " ", "Hello World", "Basic input", "Basic input msize, what?");
	TEST
		do_test("  Hello World   ", " ", "Hello World", "Basic input", "Basic input msize, what?");
	TEST
		do_test("Hello World", "", "Hello World", "Empty set", "Empty set msize, what?");
	TEST
		do_test("----------------------------------------------------------Hello World----------------------------------------------------------", "-", "Hello World", "a bunch of - at the start", "your malloc does not use minimum memory");
	TEST
		do_test("Hello World", "Hello World", "", "trim(x,x) != \"\"", "trim(x,x) msize, what?");
	TEST
		tu_test_can_crash();
		char* result = ft_strtrim("Hello World", NULL);
		if (result != NULL)
			tu_eq_str_msize("trim(x,NULL) != x", "trim(x,NULL) msize, what?", result, "Hello World", true, false);
		else
			tu_warning_message("Calling strtrim with a NULL set returns NULL instead of input");
	TEST
		tu_test_can_crash();
		char* result = ft_strtrim(NULL, "");
		if (result != NULL)
			tu_eq_str_msize("strtrim(NULL, \"\") != \"\"", "strtrim(NULL, \"\") msize, what?", result, "", true, false);
	TEST
		tu_malloc_null_in(0);
		tu_eq_str("Somehow you returned a string while your malloc returned null, or are you cheating by using calloc?, what?", ft_strtrim("Did you protect your malloc?", "Did malloc?"), NULL, true, false);
	TEST_END
	return (0);
}