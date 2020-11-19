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

static char* tmp_printfstr(char* format, va_list lst)
{
	const int buffer_size = 1024;
	static char str[1024];	// why cant i put buffer_size in it? ITS CONSTANT! dont complain about it not being constant!

	int print_size = vsnprintf(str, buffer_size, format, lst);
	if (print_size == buffer_size)
	{
		fprintf(stderr, "Tried to print a error message longer than %i! increase buffer size!", buffer_size);
	}

	return str;
}

void tu_ok()
{
	before_write_result();
	write(STDOUT_FILENO, OK_CHR, 1);
}
void tu_vok_message(char *message, va_list lst)
{
	before_write_result();
	write(STDOUT_FILENO, OK_CHR, 1);

	char* str = tmp_printfstr(message, lst);
	write(STDOUT_FILENO, str, strlen(str));
}
void tu_ok_message(char *message, ...)
{
	va_list lst;
	va_start(lst, message);
	tu_vok_message(message, lst);
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

	char* str = tmp_printfstr(message, lst);
	write(STDOUT_FILENO, str, strlen(str));
}
void tu_ko_message(char *message, ...)
{
	va_list lst;
	va_start(lst, message);
	tu_vko_message(message, lst);
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

	char* str = tmp_printfstr(message, lst);
	write(STDOUT_FILENO, str, strlen(str));
}
void tu_warning_message(char *message, ...)
{
	va_list lst;
	va_start(lst, message);
	tu_vwarning_message(message, lst);
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
}