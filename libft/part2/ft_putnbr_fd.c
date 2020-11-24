#include "libft.h"
#include "test_utils.h"
#include <stdio.h>
#include <string.h>

void do_test(int value, char* correct, char* message_num_chars, char* message_string)
{
	capture_data data;
	tu_start_capture_fd(STDOUT_FILENO, &data);
	ft_putnbr_fd(value, STDOUT_FILENO);
	tu_stop_capture_fd(&data);

	size_t correct_len = strlen(correct);
	char buff[correct_len + 1];
	size_t num_chars = read(data.read_end, buff, correct_len + 1);
	if (num_chars != correct_len)
		tu_ko_message_exit(message_num_chars);
	if (strncmp(buff, correct, num_chars) != 0)
		tu_ko_message_exit(message_string);
}

int main(int argc, char *argv[])
{
	TEST_START
		do_test(0, "0", "\"0\" did not write 1 character", "\"0\" did not write the '0' character");
	TEST
		do_test(5, "5", "\"5\" did not write 1 character", "\"5\" did not write the '5' character");
	TEST
		do_test(-5, "-5", "-5 wrong length", "-5 wrong characters");
	TEST
		do_test(2147483647, "2147483647", "2147483647 wrong length", "2147483647 wrong characters");
	TEST
		do_test(-2147483648, "-2147483648", "-2147483648 wrong length", "-2147483648 wrong characters");
	TEST
		tu_malloc_null_in(0);
		do_test(5, "5", "using malloc in ft_putnbr is forbidden!", "using malloc in ft_putnbr is forbidden!");
	TEST_END
	return (0);
}