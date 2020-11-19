#include "libft.h"
#include "test_utils.h"

int main(int argc, char *argv[])
{
	tu_test_init(argc, argv);
	if (tu_is_test(argv[1],"0"))
	{
		for (char i = -128; i < ' '; i++)
			if (ft_isprint(i))
				tu_ko_message_exit("-128 to [space]");
		for (char i = ' '; i < 127; i++)
			if (!ft_isprint(i))
				tu_ko_message_exit("[space] to 126");
		if (ft_isprint(127))
			tu_ko_message_exit("127");
		tu_ok_exit();
	}
	else
		tu_test_stop();
	tu_test_finish();
	return (0);
}