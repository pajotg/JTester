#include "libft.h"
#include "test_utils.h"
#include <string.h>


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		write(STDOUT_FILENO, "argc != 2", 9);
		return (1);
	}
	if (tu_is_test(argv[1],"0"))
	{
		tu_eq_str_msize("Your strdup returned the wrong string!", "Your strdup allocated the wrong ammount, what?", ft_strdup("Hello world!"), "Hello world!", true, false);
	}
	else if (tu_is_test(argv[1],"1"))
	{
		tu_malloc_null_in(0);
		tu_eq_str_msize("Your strdup returned a string when your malloc returned null!", "Your strdup allocated the wrong ammount... when it should have returned null, what?", ft_strdup("Hello world!"), NULL, true, false);
	}
	else
		tu_test_stop();
	tu_test_finish();
	return (0);
}