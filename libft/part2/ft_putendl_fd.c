#include "libft.h"
#include "test_utils.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	TEST_START
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		ft_putendl_fd("Hello World!", STDOUT_FILENO);
		tu_stop_capture_fd(&data);
		char buff[14];
		size_t num_chars = read(data.read_end, buff, 14);
		if (num_chars != 13)
			tu_ko_message_exit("Wrong number of characters printed! expected %i but got %i: \"%s\"", 126, num_chars, buff);
		if (strcmp("Hello World!\n", buff) != 0)
			tu_ko_message_exit("Wrong string printed! expected \"%s\" but got \"%s\"", "Hello World!\n", buff);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		for (int i = 0; i < 250; i++)
		{
			size_t length = tu_rand_range(0,125);
			char* str = tu_rand_str(length);
			ft_putendl_fd(str, STDOUT_FILENO);
			char buff[length + 2];
			size_t num_chars = read(data.read_end, buff, length + 2);
			if (num_chars != length + 1)
			{
				tu_stop_capture_fd(&data);
				tu_ko_message_exit("Wrong number of random characters printed Expected \"%s\" but got \"%.*s\"", str, num_chars, buff);
			}
			if (strncmp(buff, str, length) != 0 || buff[length] != '\n')
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