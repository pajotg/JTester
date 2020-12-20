#include "gnl_utils.h"

int main(int argc, char *argv[])
{
	TEST_START
		int fd1 = tu_create_temp_fd("This is your first line\nand this is your third!");
		int fd2 = tu_create_temp_fd("This is your second line\nand this is your fourth!");

		tu_init_static_gnl();
		tu_malloc_reset();

		char* line1 = NULL;
		char* line2 = NULL;
		int ret;
		ret = get_next_line(fd1, &line1); tu_check(ret, line1, 1, "This is your first line");
		ret = get_next_line(fd2, &line2); tu_check(ret, line2, 1, "This is your second line");
		ret = get_next_line(fd1, &line1); tu_check(ret, line1, 0, "and this is your third!");
		ret = get_next_line(fd2, &line2); tu_check(ret, line2, 0, "and this is your fourth!");
		close(fd1);
		close(fd2);
	TEST
		int fd1 = tu_create_temp_fd("a\na\naa\naa\naaa\naaa\n");
		int fd2 = tu_create_temp_fd("b\nb\nbb\nbb\nbbb\nbbb\n");

		tu_init_static_gnl();
		tu_malloc_reset();

		char* line = NULL;
		int ret;

		// FD1
		ret = get_next_line(fd1, &line); tu_check(ret, line, 1, "a");
		ret = get_next_line(fd1, &line); tu_check(ret, line, 1, "a");
		// FD2
		ret = get_next_line(fd2, &line); tu_check(ret, line, 1, "b");
		ret = get_next_line(fd2, &line); tu_check(ret, line, 1, "b");
		ret = get_next_line(fd2, &line); tu_check(ret, line, 1, "bb");
		// FD1
		ret = get_next_line(fd1, &line); tu_check(ret, line, 1, "aa");
		ret = get_next_line(fd1, &line); tu_check(ret, line, 1, "aa");
		ret = get_next_line(fd1, &line); tu_check(ret, line, 1, "aaa");
		// FD2
		ret = get_next_line(fd2, &line); tu_check(ret, line, 1, "bb");
		ret = get_next_line(fd2, &line); tu_check(ret, line, 1, "bbb");
		// FD1
		ret = get_next_line(fd1, &line); tu_check(ret, line, 1, "aaa");
		ret = get_next_line(fd1, &line); tu_check(ret, line, 0, "");
		// FD2
		ret = get_next_line(fd2, &line); tu_check(ret, line, 1, "bbb");
		ret = get_next_line(fd2, &line); tu_check(ret, line, 0, "");

		close(fd1);
		close(fd2);
	TEST
		char* test_strs1[] = { tu_rand_str(16), tu_rand_str(64), tu_rand_str(256), tu_rand_str(1024), tu_rand_str(1024 * 4), tu_rand_str(1024 * 4 * 4), NULL };	// HUGEE strings
		char* test_strs2[] = { tu_rand_str(16), tu_rand_str(64), tu_rand_str(256), tu_rand_str(1024), tu_rand_str(1024 * 4), tu_rand_str(1024 * 4 * 4), NULL };	// HUGEE strings
		int fd1 = tu_create_temp_fd_arr(test_strs1);
		int fd2 = tu_create_temp_fd_arr(test_strs2);

		tu_init_static_gnl();
		tu_malloc_reset();

		char* line = NULL;
		int ret;

		ret = get_next_line(fd1, &line); tu_check(ret, line, 1, test_strs1[0]);
		ret = get_next_line(fd1, &line); tu_check(ret, line, 1, test_strs1[1]);
		ret = get_next_line(fd1, &line); tu_check(ret, line, 1, test_strs1[2]);

		ret = get_next_line(fd2, &line); tu_check(ret, line, 1, test_strs2[0]);
		ret = get_next_line(fd2, &line); tu_check(ret, line, 1, test_strs2[1]);
		ret = get_next_line(fd2, &line); tu_check(ret, line, 1, test_strs2[2]);

		ret = get_next_line(fd1, &line); tu_check(ret, line, 1, test_strs1[3]);
		ret = get_next_line(fd1, &line); tu_check(ret, line, 1, test_strs1[4]);
		ret = get_next_line(fd1, &line); tu_check(ret, line, 0, test_strs1[5]);

		ret = get_next_line(fd2, &line); tu_check(ret, line, 1, test_strs2[3]);
		ret = get_next_line(fd2, &line); tu_check(ret, line, 1, test_strs2[4]);
		ret = get_next_line(fd2, &line); tu_check(ret, line, 0, test_strs2[5]);

		close(fd1);
		close(fd2);
	TEST
		char* test_strs[] = { tu_rand_str(16), tu_rand_str(64), NULL };
		int fd = tu_create_temp_fd_arr(test_strs);

		tu_init_static_gnl();
		tu_malloc_reset();

		char* original = tu_rand_str(16);

		char* line = NULL;
		int ret;

		// An invalid fd should not mess up the other valid FD's
		ret = get_next_line(fd, &line); tu_check(ret, line, 1, test_strs[0]);
		line = original;
		ret = get_next_line(-1, &line);
		if (line == original)	// Setting to null and doing nothing is fine, but NO STRINGS!
			line = NULL;
		tu_check(ret, line, -1, NULL);
		ret = get_next_line(fd, &line); tu_check(ret, line, 0, test_strs[1]);
		free(original);
	TEST_END
	return (0);
}