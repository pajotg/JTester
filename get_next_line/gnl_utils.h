#ifndef GNL_UTILS_H
# define GNL_UTILS_H

# include "get_next_line.h"
# include "test_utils.h"
# include <string.h>
# include <errno.h>
# include <stdio.h>

void tu_check(int ret, char* line, int expected_ret, char* expected_line);

int tu_create_temp_fd(char* str);
int tu_create_temp_fd_arr(char** str);

void tu_init_static_gnl();

#endif