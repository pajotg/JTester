#include "libft.h"
#include "test_utils.h"
#include <stdio.h>
#include <string.h>

void do_test(char* prefix, char* suffix, char* expected, char* message, char* msize_message)
{
	tu_eq_str_msize(message, msize_message, ft_strjoin(prefix, suffix), expected, true, false);
}

int main(int argc, char *argv[])
{
	TEST_START
		do_test("Hello", " World", "Hello World", "Basic input", "Basic input malloc size, what? got: %i expected: %i");
	TEST
		do_test("Hello", "", "Hello", "Empty suffix", "Empty suffix malloc size, what? got: %i expected: %i");
	TEST
		do_test("", "World", "World", "Empty prefix", "Empty prefix malloc size, what? got: %i expected: %i");
	TEST
		tu_test_can_crash();
		char* str = ft_strjoin("Hello", NULL);
		if (str != NULL)
			tu_eq_str_msize("NULL suffix", "NULL suffix malloc size, what? got: %i expected: %i", str, "Hello", true, false);
		else
			tu_warning_message("Calling strjoin with null suffix returns NULL instead of the prefix");
	TEST
		tu_test_can_crash();
		char* str = ft_strjoin(NULL, " World");
		if (str != NULL)
			tu_eq_str_msize("NULL prefix", "NULL prefix malloc size, what? got: %i expected: %i", str, " World", true, false);
		else
			tu_warning_message("Calling strjoin with null prefix returns NULL instead of the suffix");
	TEST
		tu_test_can_crash();
		char* str = ft_strjoin(NULL, NULL);
		if (str != NULL)
			tu_eq_str_msize("NULL NULL", "NULL NULL malloc size, what? got: %i expected: %i", str, "", true, false);
	TEST
		tu_malloc_null_in(0);
		tu_eq_str("Somehow you returned a string while your malloc returned null, or are you cheating by using calloc?, what?", ft_strjoin("Did you protect", " your malloc?"), NULL, true, false);
	TEST_END
	return (0);
}