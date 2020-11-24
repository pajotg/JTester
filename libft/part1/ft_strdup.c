#include "libft.h"
#include "test_utils.h"
#include <string.h>


int main(int argc, char *argv[])
{
	TEST_START
		tu_eq_str_msize("Your strdup returned the wrong string!", "Your strdup allocated the wrong ammount, what?", ft_strdup("Hello world!"), "Hello world!", true, false);
	TEST
		tu_malloc_null_in(0);
		tu_eq_str_msize("Your strdup returned a string when your malloc returned null!", "Your strdup allocated the wrong ammount... when it should have returned null, what?", ft_strdup("Hello world!"), NULL, true, false);
	TEST_END
	return (0);
}