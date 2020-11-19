#include "libft.h"
#include "test_utils.h"
#include <ctype.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	tu_test_init(argc, argv);
	if (tu_is_test(argv[1],"0"))
	{
		for (int i = -128; i <= 127; i++)
			if ((char)ft_tolower(i) != (char)tolower(i))
			{
				// tolower returns a unsigned char while most ft_tolower implementations dont, so cast to char to not care
				tu_ko_message_exit("(%i = ft_tolower(%i)) != (%i = tolower(%i))", ft_tolower(i), i, tolower(i), i);
			}
		tu_ok_exit();
	}
	else
		tu_test_stop();
	tu_test_finish();
	return (0);
}