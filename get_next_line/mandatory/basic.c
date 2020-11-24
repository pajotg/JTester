#include "get_next_line.h"
#include "test_utils.h"
#include <string.h>
#include <errno.h>
#include <stdio.h>

void check(int ret, char* line, int expected_ret, char* expected_line)
{
	if (ret != expected_ret)
	{
		if (expected_ret == 0)
			tu_ko_message_exit("your get_next_line did not return a eof when it should have done so! returned: %i", ret);
		else
			tu_ko_message_exit("your get_next_line did not return a 1 when it should have done so! returned: %i", ret);
	}
	if (strcmp(line, expected_line))
		tu_ko_message_exit("your get_next_line did not read the correct line: %s expected: %s", line, expected_line);
}

int create_temp_fd(char* str)
{
	FILE* file = tmpfile();
	int fd = fileno(file);

	size_t wrote = write(fd, str, strlen(str));
	if (wrote != strlen(str))
		tu_warning_message_exit("For some reason we could not write!");
	fseek(file, 0, SEEK_SET);
	return fileno(file);
}

int main(int argc, char *argv[])
{
	TEST_START
		char* test_str = "Hello World! what an amazing day we are having huh?";
		int fd = create_temp_fd(test_str);

		char* line;
		int ret = get_next_line(fd, &line);
		close(fd);

		check(ret, line, 0, test_str);
		free(line);
		tu_malloc_reset();	// since we use static variables, we should ignore those, we will later test for memory leaks
	TEST
		char* test_str = "Hello World!\nwhat an amazing day\nwe are having huh?";
		int fd = create_temp_fd(test_str);

		char* line;
		int ret;

		ret = get_next_line(fd, &line); check(ret, line, 1, "Hello World!");	// This call will init all static variables
		free(line);	// free it, so the next call does not have to call free
		line = NULL;

		//tu_malloc_reset();	// since we use static variables, we should ignore those, we will later test for memory leaks
		ret = get_next_line(fd, &line); check(ret, line, 1, "what an amazing day");
		ret = get_next_line(fd, &line); check(ret, line, 0, "we are having huh?");
		close(fd);
		free(line);
		// my get next line also clears the static variables once it reaches the end, so it will have 1 more free, how do i account for that properly?
	TEST_END
	return (0);
}