#include "libft.h"
#include "test_utils.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	tu_test_init(argc, argv);
	if (tu_is_test(argv[1],"0"))
	{
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		for (char c = 1; c < 127; c++)
		{
			ft_putchar_fd(c, STDOUT_FILENO);
		}
		tu_stop_capture_fd(&data);
		char buff[127];
		size_t num_chars = read(data.read_end, buff, 127);
		if (num_chars != 126)
			tu_ko_message_exit("Wrong number of chars printed! expected %i but got %i: \"%s\"", 126, num_chars, buff);
		for (char c = 1; c < 127; c++)
			if (buff[c-1] != c)
				tu_ko_message_exit("Wrong char printed: %s", buff);
	}
	else
		tu_test_stop();
	tu_test_finish();
	return (0);
}