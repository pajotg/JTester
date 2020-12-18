#include "gnl_utils.h"

void tu_check(int ret, char* line, int expected_ret, char* expected_line)
{
	if (ret != expected_ret)
	{
		if (expected_ret == 0)
			tu_ko_message_exit("your get_next_line did not return a eof when it should have done so! returned: %i", ret);
		else
			tu_ko_message_exit("your get_next_line did not return a %i when it should have done so! returned: %i", expected_ret, ret);
	}
	if ((line == NULL) != (expected_line == NULL))
	{
		if (line == NULL)
			tu_ko_message_exit("your get_next_line returned null unexpectedly! expected: %s but got NULL", expected_line);
		else
			tu_ko_message_exit("your get_next_line returned a string unexpectedly! expected NULL but got %s", line);
	} else {
		if (expected_line != NULL && strcmp(line, expected_line))
			tu_ko_message_exit("your get_next_line did not read the correct line: %s expected: %s", line, expected_line);
	}
	try_free(line);
}

int tu_create_temp_fd(char* str)
{
	FILE* file = tmpfile();	// Mallocs
	int fd = fileno(file);

	size_t len = strlen(str);
	size_t wrote = write(fd, str, len);
	if (wrote != len)
		tu_warning_message_exit("For some reason we could not write!");
	fseek(file, 0, SEEK_SET);	// Mallocs
	return fileno(file);
}
int tu_create_temp_fd_arr(char** str)
{
	FILE* file = tmpfile();	// Mallocs
	int fd = fileno(file);

	int curr = 0;
	while (str[curr])
	{
		size_t len = strlen(str[curr]);
		size_t wrote = write(fd, str[curr], len);
		if (wrote != len)
			tu_warning_message_exit("For some reason we could not write!");
		if (str[curr+1])	// Only write this newline if this is not the last
		{
			wrote = write(fd, "\n", 1);
			if (wrote != 1)
				tu_warning_message_exit("For some reason we could not write the \\n!");
		}
		curr++;
	}
	fseek(file, 0, SEEK_SET);	// Mallocs
	return fileno(file);
}

void tu_init_static_gnl()
{
	int fd = tu_create_temp_fd("Hello world!\nThis is text!");

	char* line = NULL;

	get_next_line(fd,&line);
	get_next_line(fd,&line);

	free(line);

	close(fd);
}