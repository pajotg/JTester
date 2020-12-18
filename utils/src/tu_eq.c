#include "../include/test_utils.h"
#include <string.h>

#if __linux__
# include <malloc.h>
# define MALLOC_SIZE malloc_usable_size
#else
# include "malloc/malloc.h"
# define MALLOC_SIZE malloc_size
#endif

void tu_eq_msize(char* message, void* got, int expected, bool free_got)
{
	void* correct_size = malloc(expected);
	if (got == NULL || MALLOC_SIZE(got) != MALLOC_SIZE(correct_size))
	{
		tu_ko_message_exit(message, MALLOC_SIZE(got), MALLOC_SIZE(correct_size));
	}
	if (free_got && got)
		try_free(got);
	try_free(correct_size);	// Not that it really matters for such a short test programm, oh well
}

void tu_eq_int(char* message, int got, int expected, ...)
{
	if (got != expected) {
		va_list lst;
		va_start(lst, expected);
		tu_vko_message_exit(message, lst);
		va_end(lst);
	}
}
void tu_eq_char(char* message, char got, char expected, ...)
{
	if (got != expected) {
		va_list lst;
		va_start(lst, expected);
		tu_vko_message_exit(message, lst);
		va_end(lst);
	}
}
void tu_eq_bool(char* message, bool got, bool expected, ...)
{
	if (got != expected) {
		va_list lst;
		va_start(lst, expected);
		tu_vko_message_exit(message, lst);
		va_end(lst);
	}
}

void tu_eq_str(char* message, char* got, char* expected, bool free_got, bool free_expected)
{
	if (got != expected && (got == NULL || expected == NULL || strcmp(got,expected) != 0)) {
		tu_ko_message_exit(message, got, expected);
	}
	if (free_got && got)
		try_free(got);
	if (free_expected && expected)
		try_free(expected);
}
void tu_eq_str_msize(char* message, char* msize_message, char* got, char* expected, bool free_got, bool free_expected)
{
	if (got != expected && (got == NULL || expected == NULL || strcmp(got,expected) != 0)) {
		tu_ko_message_exit(message, got, expected);
	} else if (expected != NULL) {
		tu_eq_msize(msize_message, got, strlen(expected + 1), false);
	}
	if (free_got && got)
		try_free(got);
	if (free_expected && expected)
		try_free(expected);
}

void tu_eq_arr(char* message, void* got, void* expected, int size, bool free_got, bool free_expected)
{
	if (got != expected && (got == NULL || expected == NULL || memcmp(got,expected, size) != 0)) {
		tu_ko_message_exit(message);
	}
	if (free_got && got)
		try_free(got);
	if (free_expected && expected)
		try_free(expected);
}

void tu_eq_pt(char* message, void* got, void* expected, bool free_got, bool free_expected)
{
	if (got != expected) {
		tu_ko_message_exit(message, got, expected);
	}
	if (free_got && got)
		try_free(got);
	if (free_expected && expected)
		try_free(expected);
}