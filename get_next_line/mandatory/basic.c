#include "gnl_utils.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	TEST_START
		char* test_str = "Hello World! what an amazing day we are having huh?";
		int fd = tu_create_temp_fd(test_str);

		tu_init_static_gnl();
		tu_malloc_reset();

		int ret;
		char* line = NULL;

		ret = get_next_line(fd, &line); tu_check(ret, line, 1, test_str);
		ret = get_next_line(fd, &line); tu_check(ret, line, 0, NULL);

		close(fd);
		free(line);
	TEST
		char* test_str = "Hello World!\nwhat an amazing day\nwe are having huh?";
		int fd = tu_create_temp_fd(test_str);

		tu_init_static_gnl();
		tu_malloc_reset();

		char* line = NULL;
		int ret;

		ret = get_next_line(fd, &line); tu_check(ret, line, 1, "Hello World!");
		ret = get_next_line(fd, &line); tu_check(ret, line, 1, "what an amazing day");
		ret = get_next_line(fd, &line); tu_check(ret, line, 1, "we are having huh?");
		ret = get_next_line(fd, &line); tu_check(ret, line, 0, NULL);

		close(fd);
		free(line);
	TEST
		char* test_str = "a\na\naa\naa\naaa\naaa\n";
		int fd = tu_create_temp_fd(test_str);

		tu_init_static_gnl();
		tu_malloc_reset();

		char* line = NULL;
		int ret;

		ret = get_next_line(fd, &line); tu_check(ret, line, 1, "a");
		ret = get_next_line(fd, &line); tu_check(ret, line, 1, "a");
		ret = get_next_line(fd, &line); tu_check(ret, line, 1, "aa");
		ret = get_next_line(fd, &line); tu_check(ret, line, 1, "aa");
		ret = get_next_line(fd, &line); tu_check(ret, line, 1, "aaa");
		ret = get_next_line(fd, &line); tu_check(ret, line, 1, "aaa");
		ret = get_next_line(fd, &line); tu_check(ret, line, 1, "");
		ret = get_next_line(fd, &line); tu_check(ret, line, 0, NULL);

		close(fd);
		free(line);
	TEST
		char* test_str = tu_rand_str(1024*8);	// HUGEE string
		int fd = tu_create_temp_fd(test_str);

		tu_init_static_gnl();
		tu_malloc_reset();

		char* line = NULL;
		int ret;

		ret = get_next_line(fd, &line); tu_check(ret, line, 1, test_str);
		ret = get_next_line(fd, &line); tu_check(ret, line, 0, NULL);

		close(fd);
		free(line);
	TEST
		char* test_strs[] = { tu_rand_str(16), tu_rand_str(64), tu_rand_str(256), tu_rand_str(1024), tu_rand_str(1024 * 4), tu_rand_str(1024 * 4 * 4), NULL };	// HUGEE strings
		int fd = tu_create_temp_fd_arr(test_strs);

		tu_init_static_gnl();
		tu_malloc_reset();

		char* line = NULL;
		int ret;

		ret = get_next_line(fd, &line); tu_check(ret, line, 1, test_strs[0]);
		ret = get_next_line(fd, &line); tu_check(ret, line, 1, test_strs[1]);
		ret = get_next_line(fd, &line); tu_check(ret, line, 1, test_strs[2]);
		ret = get_next_line(fd, &line); tu_check(ret, line, 1, test_strs[3]);
		ret = get_next_line(fd, &line); tu_check(ret, line, 1, test_strs[4]);
		ret = get_next_line(fd, &line); tu_check(ret, line, 1, test_strs[5]);
		ret = get_next_line(fd, &line); tu_check(ret, line, 0, NULL);

		close(fd);
		free(line);
	TEST
		tu_init_static_gnl();
		tu_malloc_reset();

		char* original = tu_rand_str(16);
		char* line = original;
		int ret;

		ret = get_next_line(-1, &line);
		if (line == original)
			tu_ko_message_exit("Your get next line does not clear line with a invalid FD!");
		tu_check(ret, line, -1, NULL);
		try_free(line);
	TEST
		tu_init_static_gnl();
		tu_malloc_reset();

		char* original = tu_rand_str(16);
		char* line = original;
		int ret;

		ret = get_next_line(42, &line);
		if (line == original)
			tu_ko_message_exit("Your get next line does not clear line with a invalid FD!");
		tu_check(ret, line, -1, NULL);

		try_free(line);
	TEST_END
	return (0);
}