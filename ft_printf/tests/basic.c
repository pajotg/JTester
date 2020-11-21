#include "test_utils_printf.h"

int main(int argc, char *argv[])
{
	TEST_START
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test(&data, "%%");
		tu_malloc_reset();	// Static variables...
		do_test(&data, "%5%");
		do_test(&data, "%-5%");
		do_test(&data, "%0-5%");
		do_test(&data, "%-05%");
		do_test(&data, "%-5.0%");
		do_test(&data, "%5.1%");
		do_test(&data, "%-5.2%");
		do_test(&data, "%5.3%");
		do_test(&data, "%2%%5%%.2%");
		do_test(&data, "Hey %% %% %% there!");
		tu_stop_capture_fd(&data);
	TEST(1)
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test_i(&data, "%c", 'A');
		tu_malloc_reset();	// Static variables...
		static char TestChars[] = { 'A', 'a', '9', '\0', 255, -25 };
		for (int i = 0; i < 6; i++)
		{
			char c = TestChars[i];
			do_test_i(&data, "%5c", c);
			do_test_i(&data, "%-5c", c);
			do_test_i(&data, "%0-5c", c);
			do_test_i(&data, "%-05c", c);
			do_test_i(&data, "%-5.0c", c);
			do_test_i(&data, "%5.1c", c);
			do_test_i(&data, "%-5.2c", c);
			do_test_i(&data, "%5.3c", c);
			do_test_i(&data, "%05.3c", c);
			do_test_ii(&data, "%0*.3c", 5, c);
			do_test_ii(&data, "%0*.3c", -5, c);
			do_test_ii(&data, "%05.*c", 5, c);
			do_test_ii(&data, "%05.*c", -5, c);
			do_test_ii(&data, "%05.*c", 8, c);
			do_test_ii(&data, "%05.*c", -8, c);
		}
		tu_stop_capture_fd(&data);
	TEST(2)
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test_i(&data, "%i", 5);
		tu_malloc_reset();	// Static variables...
		for (int i = -1; i <= 1; i++)
		{
			do_test_i(&data, "%5i", i);
			do_test_i(&data, "%-5i", i);
			do_test_i(&data, "%0-5i", i);
			do_test_i(&data, "%-05i", i);
			do_test_i(&data, "%-5.0i", i);
			do_test_i(&data, "%5.1i", i);
			do_test_i(&data, "%-5.2i", i);
			do_test_i(&data, "%5.3i", i);
			do_test_i(&data, "%05.3i", i);
			do_test_ii(&data, "%0*.3i", 5, i);
			do_test_ii(&data, "%0*.3i", -5, i);
			do_test_ii(&data, "%05.*i", 5, i);
			do_test_ii(&data, "%05.*i", -5, i);
			do_test_ii(&data, "%05.*i", 8, i);
			do_test_ii(&data, "%05.*i", -8, i);
		}
		tu_stop_capture_fd(&data);
	TEST_END
	return (0);
}