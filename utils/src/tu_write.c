#include "../include/test_utils.h"
#include <string.h>
#include <stdio.h>

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

CREATE_TMP_VPRINTF(tmp_sprintf,1024)

void tu_ok()
{
	before_write_result();
	write(STDOUT_FILENO, OK_CHR, 1);
}
void tu_vok_message(char *message, va_list lst)
{
	before_write_result();
	write(STDOUT_FILENO, OK_CHR, 1);

	char* str = vtmp_sprintf(message, lst);
	write(STDOUT_FILENO, str, strlen(str));
}
void tu_ok_message(char *message, ...)
{
	va_list lst;
	va_start(lst, message);
	tu_vok_message(message, lst);
	va_end(lst);
}

void tu_ko()
{
	before_write_result();
	write(STDOUT_FILENO, KO_CHR, 1);
}
void tu_vko_message(char *message, va_list lst)
{
	before_write_result();
	write(STDOUT_FILENO, KO_CHR, 1);

	char* str = vtmp_sprintf(message, lst);
	write(STDOUT_FILENO, str, strlen(str));
}
void tu_ko_message(char *message, ...)
{
	va_list lst;
	va_start(lst, message);
	tu_vko_message(message, lst);
	va_end(lst);
}

void tu_warning()
{
	before_write_result();
	write(STDOUT_FILENO, WARNING_CHR, 1);
}
void tu_vwarning_message(char *message, va_list lst)
{
	before_write_result();
	write(STDOUT_FILENO, WARNING_CHR, 1);

	char* str = vtmp_sprintf(message, lst);
	write(STDOUT_FILENO, str, strlen(str));
}
void tu_warning_message(char *message, ...)
{
	va_list lst;
	va_start(lst, message);
	tu_vwarning_message(message, lst);
	va_end(lst);
}

// output with exit
void tu_ok_exit()
{
	tu_ok();
	tu_test_finish();
	exit(0);
}
void tu_vok_message_exit(char *message, va_list lst)
{
	tu_vok_message(message, lst);

	tu_test_finish();
	exit(0);
}
void tu_ok_message_exit(char *message, ...)
{
	va_list lst;
	va_start(lst, message);
	tu_vok_message_exit(message, lst);
	va_end(lst);
}

void tu_ko_exit()
{
	tu_ko();
	tu_test_finish();
	exit(0);
}
void tu_vko_message_exit(char* message, va_list lst)
{
	tu_vko_message(message, lst);

	tu_test_finish();
	exit(0);
}
void tu_ko_message_exit(char *message, ...)
{
	va_list lst;
	va_start(lst, message);
	tu_vko_message_exit(message, lst);
	va_end(lst);
}

void tu_warning_exit()
{
	tu_warning();
	tu_test_finish();
	exit(0);
}
void tu_vwarning_message_exit(char* message, va_list lst)
{
	tu_vwarning_message(message, lst);

	tu_test_finish();
	exit(0);
}
void tu_warning_message_exit(char* message, ...)
{
	va_list lst;
	va_start(lst, message);
	tu_vwarning_message_exit(message, lst);
	va_end(lst);
}