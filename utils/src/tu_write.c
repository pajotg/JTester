#include "../include/test_utils.h"
#include <string.h>

bool* get_has_written_result()
{
	static bool has_written_result = false;
	return &has_written_result;
}

static void before_write_result()
{
	bool* has_written_result = get_has_written_result();
	if (*has_written_result)
	{
		write(STDERR_FILENO, "Test failed: tried to write multiple results", 44);
		tu_test_finish();
		exit(0);
	}
	*has_written_result = true;
}

void tu_ok()
{
	before_write_result();
	write(STDOUT_FILENO, OK_CHR, 1);
}
void tu_ok_message(char *message)
{
	before_write_result();
	write(STDOUT_FILENO, OK_CHR, 1);
	write(STDOUT_FILENO, message, strlen(message));
}
void tu_ko()
{
	before_write_result();
	write(STDOUT_FILENO, KO_CHR, 1);
}
void tu_ko_message(char *message)
{
	before_write_result();
	write(STDOUT_FILENO, KO_CHR, 1);
	write(STDOUT_FILENO, message, strlen(message));
}
void tu_warning()
{
	before_write_result();
	write(STDOUT_FILENO, WARNING_CHR, 1);
}
void tu_warning_message(char *message)
{
	before_write_result();
	write(STDOUT_FILENO, WARNING_CHR, 1);
	write(STDOUT_FILENO, message, strlen(message));
}

void tu_ok_exit()
{
	tu_ok();
	tu_test_finish();
	exit(0);
}
void tu_ok_message_exit(char *message)
{
	tu_ok_message(message);
	tu_test_finish();
	exit(0);
}
void tu_ko_exit()
{
	tu_ko();
	tu_test_finish();
	exit(0);
}
void tu_ko_message_exit(char* message)
{
	tu_ko_message(message);
	tu_test_finish();
	exit(0);
}
void tu_warning_exit()
{
	tu_warning();
	tu_test_finish();
	exit(0);
}
void tu_warning_message_exit(char* message)
{
	tu_warning_message(message);
	tu_test_finish();
	exit(0);
}