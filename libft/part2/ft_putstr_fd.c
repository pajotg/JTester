#include "libft.h"
#include "test_utils.h"
#include <stdio.h>
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
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		ft_putstr_fd("Hello World!", STDOUT_FILENO);
		tu_stop_capture_fd(&data);
		char buff[13];
		size_t num_chars = read(data.read_end, buff, 13);
		if (num_chars != 12)
			tu_ko_message_exit("Wrong number of characters printed");
		tu_eq_str("Wrong string printed", buff, "Hello World!", false, false);
	}
	else if (tu_is_test(argv[1],"1"))
	{
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		for (int i = 0; i < 250; i++)
		{
			size_t length = tu_rand_range(0,125);
			char* str = tu_rand_str(length);
			ft_putstr_fd(str, STDOUT_FILENO);
			char buff[length + 1];
			size_t num_chars = read(data.read_end, buff, length + 1);
			if (num_chars != length)
			{
				tu_stop_capture_fd(&data);
				tu_ko_message_exit("Wrong number of random characters printed");
			}
			if (strncmp(buff, str, num_chars) != 0)
			{
				tu_stop_capture_fd(&data);
				tu_ko_message_exit("Wrong random string printed");
			}
			free(str);
		}
		tu_stop_capture_fd(&data);
	}
	else
		tu_test_stop();
	tu_test_finish();
	return (0);
}