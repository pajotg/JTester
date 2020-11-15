#include <string.h>
#include "../include/test_utils.h"

bool tu_is_test(char* curr, char* target)
{
	return strcmp(curr, target) == 0;
}