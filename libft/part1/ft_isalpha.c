#include "libft.h"
#include "test_utils.h"

int main(int argc, char *argv[])
{
	tu_test_init(argc, argv);
	if (tu_is_test(argv[1],"0"))
	{
		for (char i = -128; i < 'A'; i++)
			if (ft_isalpha(i))
				tu_ko_message_exit("-128 to A");
		for (char i = 'A'; i <= 'Z'; i++)
			if (!ft_isalpha(i))
				tu_ko_message_exit("A to Z");
		for (char i = 'Z'+1; i < 'a'; i++)
			if (ft_isalpha(i))
				tu_ko_message_exit("Z to a");
		for (char i = 'a'; i <= 'z'; i++)
			if (!ft_isalpha(i))
				tu_ko_message_exit("a to z");
		for (char i = 'z'+1; i > 0; i++)
			if (ft_isalpha(i))
				tu_ko_message_exit("z to 127");
		tu_ok_exit();
	}
	else
		tu_test_stop();
	tu_test_finish();
	return (0);
}