#include "test_utils.h"

void try_free(void* pt)
{
	if (pt != NULL)
		free(pt);
}