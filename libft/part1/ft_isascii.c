#include "libft.h"
#include "test_utils.h"

int main(int argc, char *argv[])
{
	tu_test_init(argc, argv);
	if (tu_is_test(argv[1],"0"))
	{
		for (char i = -128; i < 0; i++)
			if (ft_isascii(i))
				tu_ko_message_exit("-128 to 0");
		for (char i = 0; i >= 0; i++)
			if (!ft_isascii(i))
				tu_ko_message_exit("0 to 127");
		tu_ok();
	}
	else
		tu_test_stop();
	tu_test_finish();
	return (0);
}