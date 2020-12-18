#include "libft.h"
#include "test_utils.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	TEST_START
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		ft_putstr_fd("Hello World!", STDOUT_FILENO);
		tu_stop_capture_fd(&data);
		char buff[13];
		size_t num_chars = read(data.read_end, buff, 13);
		if (num_chars != 12)
			tu_ko_message_exit("Wrong number of characters printed");
		tu_eq_str("Wrong string printed", buff, "Hello World!", false, false);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		for (int i = 0; i < 250; i++)
		{
			ssize_t length = tu_rand_range(0,125);
			char* str = tu_rand_str(length);
			ft_putstr_fd(str, STDOUT_FILENO);
			char buff[length + 1];
			ssize_t num_chars = read(data.read_end, buff, length + 1);
			if (length == 0 && num_chars == -1)	// read returns -1 if it read no characters, not 0
				num_chars = 0;
			if (num_chars != length)
			{
				tu_stop_capture_fd(&data);
				tu_ko_message_exit("Wrong number of random characters printed, expected length of %i but got %i, Expected \"%s\" but got \"%.*s\"", length, num_chars, str, num_chars, buff);
			}
			if (strncmp(buff, str, num_chars) != 0)
			{
				tu_stop_capture_fd(&data);
				tu_ko_message_exit("Wrong random string printed Expected \"%s\" but got \"%.*s\"", str, num_chars, buff);
			}
			free(str);
		}
		tu_stop_capture_fd(&data);
	TEST_END
	return (0);
}