#include "gnl_utils.h"

int main(int argc, char *argv[])
{
	TEST_START
		char* test_str = "Hello World! what an amazing day we are having huh?";
		int fd = tu_create_temp_fd(test_str);

		tu_init_static_gnl();
		tu_malloc_reset();

		char* line = NULL;
		int ret = get_next_line(fd, &line); tu_check(ret, line, 0, test_str);

		close(fd);
	TEST
		char* test_str = "Hello World!\nwhat an amazing day\nwe are having huh?";
		int fd = tu_create_temp_fd(test_str);

		tu_init_static_gnl();
		tu_malloc_reset();

		char* line = NULL;
		int ret;

		ret = get_next_line(fd, &line); tu_check(ret, line, 1, "Hello World!");
		ret = get_next_line(fd, &line); tu_check(ret, line, 1, "what an amazing day");
		ret = get_next_line(fd, &line); tu_check(ret, line, 0, "we are having huh?");

		close(fd);
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
		ret = get_next_line(fd, &line); tu_check(ret, line, 0, "");

		close(fd);
	TEST
		char* test_str = tu_rand_str(1024*8);	// HUGEE string
		int fd = tu_create_temp_fd(test_str);

		tu_init_static_gnl();
		tu_malloc_reset();

		char* line = NULL;
		int ret;

		ret = get_next_line(fd, &line); tu_check(ret, line, 0, test_str);

		close(fd);
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
		ret = get_next_line(fd, &line); tu_check(ret, line, 0, test_strs[5]);

		close(fd);
	TEST
		tu_init_static_gnl();
		tu_malloc_reset();

		char* original = tu_rand_str(16);
		char* line = original;
		int ret;

		ret = get_next_line(-1, &line);
		if (line == original)
			tu_warning_message_exit("Your get next line does not clear line with a invalid FD!");
		tu_check(ret, line, -1, NULL);
		try_free(original);
	TEST
		int fd = tu_create_temp_fd("");
		close(fd);

		tu_init_static_gnl();
		tu_malloc_reset();

		char* original = tu_rand_str(16);
		char* line = original;
		int ret;

		ret = get_next_line(fd, &line);
		if (line == original)
			tu_warning_message_exit("Your get next line does not clear line with a invalid FD!");
		tu_check(ret, line, -1, NULL);
		try_free(original);
	TEST
		char* test_strs[] = { tu_rand_str(16), tu_rand_str(64), tu_rand_str(256), tu_rand_str(1024), tu_rand_str(1024 * 4), tu_rand_str(1024 * 4 * 4), NULL };	// HUGEE strings
		int fd = tu_create_temp_fd_arr(test_strs);

		tu_init_static_gnl();
		tu_malloc_reset();

		int ret;
		char* line = NULL;

		ret = get_next_line(fd, &line); tu_check(ret, line, 1, test_strs[0]);
		ret = get_next_line(fd, &line); tu_check(ret, line, 1, test_strs[1]);
		ret = get_next_line(fd, &line); tu_check(ret, line, 1, test_strs[2]);

		char* prev = line;
		tu_malloc_null_in(0);	// Malloc checking
		ret = get_next_line(fd, &line);
		if (line == prev)
			line = NULL;
		tu_check(ret, line, -1, NULL);

		close(fd);
	TEST
		char* test_strs[] = { tu_rand_str(16), tu_rand_str(64), tu_rand_str(256), NULL };	// HUGEE strings
		int fd1 = tu_create_temp_fd_arr(test_strs);
		int fd2 = tu_create_temp_fd_arr(test_strs);

		tu_init_static_gnl();
		tu_malloc_reset();

		int ret;
		char* line = NULL;

		ret = get_next_line(fd1, &line); tu_check(ret, line, 1, test_strs[0]);
		ret = get_next_line(fd1, &line); tu_check(ret, line, 1, test_strs[1]);
		ret = get_next_line(fd1, &line); tu_check(ret, line, 0, test_strs[2]);

		tu_malloc_null_in(tu_malloc_non_null_count() - 1);	// Last malloc will be NULL

		ret = get_next_line(fd2, &line); tu_check(ret, line, 1, test_strs[0]);
		ret = get_next_line(fd2, &line); tu_check(ret, line, 1, test_strs[1]);
		char* prev = line;
		ret = get_next_line(fd2, &line);
		if (line == prev)
			line = NULL;
		tu_check(ret, line, -1, NULL);

		close(fd1);
		close(fd2);
	TEST
		char* test_strs[] = { tu_rand_str(16), tu_rand_str(64), tu_rand_str(256), NULL };	// HUGEE strings
		int fd1 = tu_create_temp_fd_arr(test_strs);
		int fd2 = tu_create_temp_fd_arr(test_strs);

		tu_init_static_gnl();
		tu_malloc_reset();

		int ret;
		char* line = NULL;

		ret = get_next_line(fd1, &line); tu_check(ret, line, 1, test_strs[0]);
		ret = get_next_line(fd1, &line); tu_check(ret, line, 1, test_strs[1]);
		int start_count = tu_malloc_non_null_count();
		ret = get_next_line(fd1, &line); tu_check(ret, line, 0, test_strs[2]);
		int end_count = tu_malloc_non_null_count();

		tu_malloc_null_in((start_count + end_count) / 2);	// a malloc somewhere inbetween the last call will be null

		ret = get_next_line(fd2, &line); tu_check(ret, line, 1, test_strs[0]);
		ret = get_next_line(fd2, &line); tu_check(ret, line, 1, test_strs[1]);
		char* prev = line;
		ret = get_next_line(fd2, &line);
		if (line == prev)
			line = NULL;
		tu_check(ret, line, -1, NULL);

		close(fd1);
		close(fd2);
	TEST_END
	return (0);
}