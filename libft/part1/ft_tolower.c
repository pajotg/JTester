#include "libft.h"
#include "test_utils.h"
#include <ctype.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	TEST_START
		for (int i = -128; i <= 127; i++)
			if ((char)ft_tolower(i) != (char)tolower(i))
			{
				// tolower returns a unsigned char while most ft_tolower implementations dont, so cast to char to not care
				tu_ko_message_exit("(%i = ft_tolower(%i)) != (%i = tolower(%i))", ft_tolower(i), i, tolower(i), i);
			}
	TEST_END
	return (0);
}