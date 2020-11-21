#include "test_utils.h"
#include <stdio.h>

void try_free(void* pt)
{
	if (pt != NULL)
		free(pt);
}