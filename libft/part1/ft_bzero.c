#include "libft.h"
#include "test_utils.h"

int main(int argc, char *argv[])
{
	TEST_START
		char* allocated = (char*)malloc(42);
		for (int i = 0; i < 42; i++)
			allocated[i] = 42;
		ft_bzero(allocated, 21);
		for (int i = 0; i < 21; i++)
			if (allocated[i] != 0)
				tu_ko_exit("Failed to write 42 at position %i/%i",i,21);
		for (int i = 21; i < 42; i++)
			if (allocated[i] != 42)
				tu_ko_exit("wrote too much! at position %i/%i",i,21);
		free(allocated);
	TEST
		ft_bzero(NULL, 0);
	TEST
		tu_test_can_crash();
		ft_bzero(NULL, 21);
	TEST_END
	return (0);
}