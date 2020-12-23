#include "test_utils.h"
#include <stdio.h>

// Set that the test has been completed, used to determine if it has crashed or not
void tu_test_init(int argc, char *argv[])
{
	tu_nop_pt(argv);
	if (argc != 2)
	{
		write(STDOUT_FILENO, "argc != 2", 9);
		exit(1);
	}
	tu_malloc_reset();

	// Just testing it
	tu_malloc_set_random(true);
	tu_free_set_random(true);
}
void tu_test_finish()
{
	tu_malloc_set_random(false);
	tu_free_set_random(false);

	if (!*get_has_written_result())
		if (tu_malloc_non_null_count() != tu_free_non_null_count())
			tu_ko_message("Leaks detected! mallocs != frees (%i != %i)", tu_malloc_non_null_count(), tu_free_non_null_count());
		else if (tu_free_non_null_count() != tu_free_count())
			tu_warning_message("Null pointer free detected!");
		else
			tu_ok();
	write(STDOUT_FILENO, FINISH_CHR, 1);
}
// A test has multiple test cases, 0 through N, call this function when the current number does not have a case
void tu_test_stop()
{
	write(STDOUT_FILENO, STOP_CHR, 1);
}
// Call this function to incidate that this test case should segfault
void tu_test_should_crash()
{
	write(STDOUT_FILENO, SHOULD_CRASH_CHR, 1);
}
// Call this function to incidate that this test case CAN segfault and still be correct
void tu_test_can_crash()
{
	write(STDOUT_FILENO, CAN_CRASH_CHR, 1);
}