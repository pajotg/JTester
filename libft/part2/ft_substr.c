#include "libft.h"
#include "test_utils.h"
#include <string.h>

void do_test(char* input, char* expected, int start, int len, char* message, char* msize_message)
{
	tu_eq_str_msize(message, msize_message, ft_substr(input, start, len), expected, true, false);
}

int main(int argc, char *argv[])
{
	TEST_START
		do_test("Hello World!", "llo Wor", 2, 7, "Basic input", "Basic input malloc size got: %i expected: %i, what?");
	TEST
		do_test("Hello World!", "", 2, 0, "Zero len", "Zero len malloc size got: %i expected: %i, what?");
	TEST
		do_test("Hello World!", "", 25, 5, "Out of range start", "Out of range malloc size got: %i expected: %i, what?");
	TEST
		do_test("Hello World!", "Hello World!", 0, 1024, "ft_substr with a length > strlen", "len = 1024, strlen(input) = 12, malloc size != strlen(output) got: %i expected: %i");
	TEST
		do_test("Hello World!", "ello World!", 1, 13, "ft_substr with a start+length > strlen", "len = 13, strlen(input) = 12, malloc size != strlen(output) got: %i expected: %i");
	TEST
		for (int i = 0; i < 250; i++)
		{
			int size = tu_rand_range(0,125);
			char* str = tu_rand_arr(size);
			try_free(ft_substr(str, tu_rand_range(0,130), tu_rand_range(0,130)));
			free(str);
		}
	TEST
		tu_test_can_crash();
		try_free(ft_substr(NULL, 5, 5));
	TEST
		tu_malloc_null_in(0);
		tu_eq_str("Somehow you returned a string while your malloc returned null, or are you cheating by using calloc?, what?", ft_substr("Did you protect your malloc?", 5, 5), NULL, true, false);
	TEST
		char* str = ft_substr("abc\0def", 4, 3);
		if (str != NULL)
			tu_eq_str("calling substr on \"abc\\0def\" with a start of 4 and length of 3 does not return \"\"", str, "", true, false);
	TEST
		char* stra = ft_substr("abc", 0, 4);	// length > strlen
		char* strb = ft_substr("abc", 1, 3);	// start+length > strlen
		if ((stra == NULL) != (strb == NULL))	// Basically: if both return null or none return null then its good, otherwise: BAD
			tu_ko_message("Calling substring with a length > strlen and start+length > strlen arent consistent!");
		try_free(stra);
		try_free(strb);
	TEST_END
	return (0);
}