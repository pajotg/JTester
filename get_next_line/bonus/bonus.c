#include "gnl_utils.h"

int main(int argc, char *argv[])
{
	TEST_START
		int fd1 = tu_create_temp_fd("This is your first line\nand this is your third!");
		int fd2 = tu_create_temp_fd("This is yoru second line\nand this is your fourth!");

		char* line1 = NULL;
		char* line2 = NULL;
		int ret;
		ret = get_next_line(fd1, &line1); tu_check(ret, line1, 1, "This is your first line");
		ret = get_next_line(fd2, &line2); tu_check(ret, line2, 1, "This is yoru second line");
		ret = get_next_line(fd1, &line1); tu_check(ret, line1, 0, "and this is your third!");
		ret = get_next_line(fd2, &line2); tu_check(ret, line2, 0, "and this is your fourth!");
		close(fd1);
		close(fd2);
		free(line1);
		free(line2);
		tu_malloc_reset();	// since we use static variables, we should ignore those, we will later test for memory leaks
	TEST_END
	return (0);
}