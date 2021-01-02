#ifndef PRINTF_H
# define PRINTF_H

#include "test_utils.h"
#include <stdio.h>
#include <string.h>

extern char* test_length_field[];
extern const int num_test_length_field;
extern char* test_bonus_flags[];
extern const int num_test_bonus_flags;
extern char* test_mandatory_flags[];
extern const int num_test_mandatory_flags;
extern char* test_width_len[];
extern const int num_test_width_len;
extern char* test_width_len_1[];
extern const int num_test_width_len_1;
extern char* test_width_len_2[];
extern const int num_test_width_len_2;

extern float TestFloats[];
extern const int num_TestFloats;
extern int TestInts[];
extern const int num_TestInts;
extern void* TestPointers[];
extern const int num_TestPointers;
extern char TestChars[];
extern const int num_TestChars;
extern char* TestStrings[];
extern const int num_TestStrings;

int	ft_printf(const char *str, ...);

void comp(capture_data* data, char* str, char* buff_ft, char* buff_real, int ft_out, int real_out, int read_out);

void do_test(capture_data* data, char* str);

void do_test_i(capture_data* data, char* str, int _1);
void do_test_ii(capture_data* data, char* str, int _1, int _2);
void do_test_iii(capture_data* data, char* str, int _1, int _2, int _3);

void do_test_s(capture_data* data, char* str, char* _1);
void do_test_is(capture_data* data, char* str, int _1, char* _2);
void do_test_iis(capture_data* data, char* str, int _1, int _2, char* _3);

void do_test_p(capture_data* data, char* str, void* _1);
void do_test_ip(capture_data* data, char* str, int _1, void* _2);
void do_test_iip(capture_data* data, char* str, int _1, int _2, void* _3);

void do_test_f(capture_data* data, char* str, float _1);
void do_test_if(capture_data* data, char* str, int _1, float _2);
void do_test_iif(capture_data* data, char* str, int _1, int _2, float _3);

#endif