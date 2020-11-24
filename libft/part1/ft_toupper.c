#include "libft.h"
#include "test_utils.h"
#include <ctype.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	TEST_START
		for (int i = -128; i <= 127; i++)
			if ((char)ft_toupper(i) != (char)toupper(i))
			{
				// toupper returns a unsigned char while most ft_toupper implementations dont, so cast to char to not care
				tu_ko_message_exit("(%i = ft_toupper(%i)) != (%i = toupper(%i))", ft_toupper(i), i, toupper(i), i);
			}
	TEST_END
	return (0);
}