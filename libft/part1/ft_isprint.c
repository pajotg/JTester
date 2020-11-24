#include "libft.h"
#include "test_utils.h"
#include <ctype.h>

int main(int argc, char *argv[])
{
	TEST_START
		for (char i = '\0'; i < '0'; i++)
			if ((bool)ft_isprint(i) != (bool)isprint(i))
			{
				if (isprint(i))
					tu_ko_message_exit("%c(%i) is a printable character, but your function does not agree!", i != 0 ? i : 127, i);
				else
					tu_ko_message_exit("%c(%i) not a printable character, but your function does not agree!", i != 0 ? i : 127, i);
			}
	TEST_END
	return (0);
}