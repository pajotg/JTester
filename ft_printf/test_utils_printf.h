#ifndef PRINTF_H
# define PRINTF_H

#include "test_utils.h"
#include <stdio.h>
#include <string.h>

int	ft_printf(const char *str, ...);

void comp(capture_data* data, char* str, char* buff_ft, char* buff_real, int ft_out, int real_out, int read_out);

void do_test(capture_data* data, char* str);
void do_test_i(capture_data* data, char* str, int _1);
void do_test_ii(capture_data* data, char* str, int _1, int _2);

#endif