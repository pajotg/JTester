#ifndef TEST_UTILS_H
# define TEST_UTILS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdarg.h>

#define OK_CHR "+"
#define KO_CHR "-"
#define WARNING_CHR "?"
#define STOP_CHR "s"
#define FINISH_CHR "f"
#define SHOULD_CRASH_CHR "X"
#define CAN_CRASH_CHR "x"

// How annoying that i have to use something like this to expand the __COUNTER__
#define JTMP_STRINGIFY_2(a) #a
#define STRINGIFY(a) JTMP_STRINGIFY_2(a)

#define TEST_START tu_test_init(argc, argv);\
	if (tu_is_test(argv[1],STRINGIFY(__COUNTER__)))\
	{

#define TEST }\
	else if (tu_is_test(argv[1],STRINGIFY(__COUNTER__)))\
	{

#define TEST_END }\
	else\
		tu_test_stop();\
	tu_test_finish();

// Okay, this is not the best use of macros, maybe this usage is why they are not the norm
#define CREATE_TMP_VPRINTF(name, BUFF_SIZE) static char* v##name(char* format, va_list lst)\
{\
	static char str[BUFF_SIZE];\
	int print_size = vsnprintf(str, BUFF_SIZE, format, lst);\
	if (print_size == BUFF_SIZE)\
	{\
		fprintf(stderr, "Tried to print a error message longer than "#BUFF_SIZE"! increase buffer size!");\
	}\
	return str;\
}\
static char* name(char* format, ...)\
{\
	va_list lst;\
	va_start(lst, format);\
	char* str = v##name(format, lst);\
	va_end(lst);\
	return str;\
}

typedef struct s_capture_data
{
	int fd;
	int restore;
	int read_end;
	int write_end;
} capture_data;

void tu_test_init(int argc, char *argv[]);
void tu_test_stop();
void tu_test_finish();

bool tu_is_test(char* curr, char* target);

void tu_test_should_crash();
void tu_test_can_crash();

bool* get_has_written_result();
void tu_ok();
void tu_vok_message(char *message, va_list lst);
void tu_ok_message(char *message, ...);
void tu_ko();
void tu_vko_message(char *message, va_list lst);
void tu_ko_message(char *message, ...);
void tu_warning();
void tu_vwarning_message(char *message, va_list lst);
void tu_warning_message(char *message, ...);

void tu_ok_exit();
void tu_vok_message_exit(char *message, va_list lst);
void tu_ok_message_exit(char *message, ...);
void tu_ko_exit();
void tu_vko_message_exit(char *message, va_list lst);
void tu_ko_message_exit(char *message, ...);
void tu_warning_exit();
void tu_vwarning_message_exit(char *message, va_list lst);
void tu_warning_message_exit(char *message, ...);

void tu_eq_msize(char* message, void* got, int expected, bool free_got);
void tu_eq_int(char* message, int got, int expected, ...);
void tu_eq_char(char* message, char got, char expected, ...);
void tu_eq_bool(char* message, bool got, bool expected, ...);
void tu_eq_str(char* message, char* got, char* expected, bool free_got, bool free_expected);
void tu_eq_str_msize(char* message, char* msize_message, char* got, char* expected, bool free_got, bool free_expected);
void tu_eq_arr(char* message, void* got, void* expected, int size, bool free_got, bool free_expected);
void tu_eq_pt(char* message, void* got, void* expected, bool free_got, bool free_expected);

int tu_rand_range(int min, int max);
void tu_randomize_arr(void* arr, int Size);
void tu_randomize_arr_range(void* arr, int Size, char min, char max);
void tu_randomize_arr_map(void* arr, int Size, char* values, int value_count);
char* tu_rand_arr(int size);
char* tu_rand_str(int size);

void tu_start_capture_fd(int fd, capture_data* ref);
int tu_stop_capture_fd(capture_data* ref);

void try_free(void* pt);

void tu_nop_int(int value);
void tu_nop_pt(void* value);

extern void tu_malloc_enable();
extern void tu_malloc_disable();
extern bool tu_malloc_is_enabled();
extern void tu_malloc_reset();
extern int tu_malloc_count();
extern int tu_free_count();
extern int tu_free_non_null_count();
extern void tu_malloc_null_in(int num_mallocs);
extern int tu_malloc_non_null_count();
extern void tu_malloc_set_random(bool random);
extern void tu_free_set_random(bool random);

#endif