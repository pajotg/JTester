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
	tu_test_init(argc, argv);
	if (tu_is_test(argv[1],"0"))
		do_test("Hello", " World", "Hello World", "Basic input", "Basic input msize, what?");
	else if (tu_is_test(argv[1],"1"))
		do_test("Hello", "", "Hello", "Empty suffix", "Empty suffix msize, what?");
	else if (tu_is_test(argv[1],"2"))
		do_test("", "World", "World", "Empty prefix", "Empty prefix msize, what?");
	else if (tu_is_test(argv[1],"3"))
	{
		tu_test_can_crash();
		char* str = ft_strjoin("Hello", NULL);
		if (str != NULL)
			tu_eq_str_msize("NULL suffix", "NULL suffix msize, what?", str, "Hello", true, false);
		else
			tu_warning_message("Calling strjoin with null suffix returns NULL instead of the prefix");
	}
	else if (tu_is_test(argv[1],"4"))
	{
		tu_test_can_crash();
		char* str = ft_strjoin(NULL, " World");
		if (str != NULL)
			tu_eq_str_msize("NULL prefix", "NULL prefix msize, what?", str, " World", true, false);
		else
			tu_warning_message("Calling strjoin with null prefix returns NULL instead of the suffix");
	}
	else if (tu_is_test(argv[1],"5"))
	{
		tu_test_can_crash();
		char* str = ft_strjoin(NULL, NULL);
		if (str != NULL)
			tu_eq_str_msize("NULL NULL", "NULL NULL msize, what?", str, "", true, false);
	}
	else if (tu_is_test(argv[1],"6"))
	{
		tu_malloc_null_in(0);
		tu_eq_str("Somehow you returned a string while your malloc returned null, or are you cheating by using calloc?, what?", ft_strjoin("Did you protect", " your malloc?"), NULL, true, false);
	}
	else
		tu_test_stop();
	tu_test_finish();
	return (0);
}