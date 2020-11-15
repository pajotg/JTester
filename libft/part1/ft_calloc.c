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
		tu_malloc_set_random(true);
		unsigned char* pt = ft_calloc(42,21);
		tu_eq_msize("Your calloc allocated the wrong ammount of memory!", pt, 42 * 21, false);
		for (int i = 0; i < 42*21; i++)
			if (pt[i] != 0)
				tu_ko_message_exit("Your calloc did not set everything to zero!");
		free(pt);
	}
	else if (tu_is_test(argv[1],"1"))
	{
		tu_malloc_null_in(0);
		unsigned char* pt = ft_calloc(42,21);
		tu_eq_pt("Your calloc returned something while your malloc returned null!", pt, NULL, true, false);
	}
	else
		tu_test_stop();
	tu_test_finish();
	return (0);
}