#include "libft.h"
#include "test_utils.h"
#include <ctype.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		write(STDOUT_FILENO, "argc != 2", 9);
		return (1);
	}
	if (tu_is_test(argv[1],"0"))
	{
		for (int i = -128; i <= 127; i++)
			if ((char)ft_toupper(i) != (char)toupper(i))
			{
				// toupper returns a unsigned char while most ft_toupper implementations dont, so cast to char to not care
				char str[54];
				snprintf(str, 54, "(%i = ft_toupper(%i)) != (%i = toupper(%i))", ft_toupper(i), i, toupper(i), i);
				tu_ko_message_exit(str);
			}
		tu_ok_exit();
	}
	else
		tu_test_stop();
	tu_test_finish();
	return (0);
}