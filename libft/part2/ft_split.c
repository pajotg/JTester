#include "libft.h"
#include "test_utils.h"
#include <stdio.h>
#include <string.h>

void do_test(char* input, char split, char** expected, char* message, char* msize_message)
{
	char** result = ft_split(input, split);
	if (result == NULL)
		tu_ko_message_exit("split returned NULL");

	int id = 0;
	while (expected[id])
	{
		if (result[id] == NULL)
			tu_ko_message_exit("split returned less than expected");
		tu_eq_str_msize(message, msize_message, result[id], expected[id], true, false);
		id++;
	}
	tu_eq_msize("split msize", result, id * sizeof(char*), true);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		write(STDOUT_FILENO, "argc != 2", 9);
		return (1);
	}

	if (tu_is_test(argv[1],"0"))
	{
		char* Expected[6] = { "Breaking", "ft_split", "since", "1981", NULL };
		do_test("Breaking ft_split since 1981", ' ', Expected, "Basic input", "Basic input msize, what?");
	}
	else if (tu_is_test(argv[1],"1"))
	{
		char* Expected[6] = { "Breaking", "ft_split", "since", "1981", NULL };
		do_test("  Breaking ft_split since 1981  ", ' ', Expected, "split at end and start", "split at end and start msize, what?");
	}
	else if (tu_is_test(argv[1],"2"))
	{
		char* Expected[1] = { NULL };
		do_test("     ", ' ', Expected, "only split char", "only split char msize, what?");
	}
	else if (tu_is_test(argv[1],"2"))
	{
		char* Expected[2] = { "Breaking ft_split since 1981", NULL };
		do_test("Breaking ft_split since 1981", '-', Expected, "no split char", "no split char msize, what?");
	}
	else if (tu_is_test(argv[1],"3"))
	{
		char* Expected[2] = { NULL };
		do_test("", '-', Expected, "empty string", "empty string msize, what?");
	}
	else if (tu_is_test(argv[1],"4"))
	{
		tu_test_can_crash();
		char* Expected[2] = { "Evil null terminator", NULL };
		do_test("Evil null terminator", '\0', Expected, "null terminator split char", "null terminator split char msize, what?");
	}
	else if (tu_is_test(argv[1],"5"))
	{
		tu_test_can_crash();
		char* Expected[1] = { NULL };
		do_test(NULL, '\0', Expected, "double NULL split char", "double NULL msize, what?");
	}
	else if (tu_is_test(argv[1],"6"))
	{
		tu_malloc_null_in(0);
		tu_eq_pt("Somehow you returned a string array while your malloc for your array returned null, or are you cheating by using calloc?, what?", ft_split("Did you protect your malloc?", ' '), NULL, true, false);
	}
	else if (tu_is_test(argv[1],"7"))
	{
		tu_malloc_null_in(1);
		tu_eq_pt("Somehow you returned a string array while your first malloc for a substring returned null, or are you cheating by using calloc?, what?", ft_split("Did you protect your malloc?", ' '), NULL, true, false);
	}
	else if (tu_is_test(argv[1],"8"))
	{
		tu_malloc_null_in(5);
		tu_eq_pt("Somehow you returned a string array while your last malloc for a substring returned null, or are you cheating by using calloc?, what?", ft_split("Did you protect your malloc?", ' '), NULL, true, false);
	}
	else
		tu_test_stop();
	tu_test_finish();
	return (0);
}