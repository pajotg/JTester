#include "libft.h"
#include "test_utils.h"
#include <string.h>

int main(int argc, char *argv[])
{
	TEST_START
		tu_eq_int("basic input", ft_strlen("Hello world!"), 12);
	TEST
		tu_eq_int("empty string", ft_strlen(""), 0);
	TEST
		tu_test_can_crash();
		ft_strlen(NULL);
	TEST
		for (int i = 0; i < 250; i++)
		{
			int size = tu_rand_range(0,125);
			char* str = tu_rand_str(size);
			tu_eq_int("random valid string", ft_strlen(str), size);
			free(str);
		}
	TEST
		for (int i = 0; i < 250; i++)
		{
			int size = tu_rand_range(0,125);
			char* str = tu_rand_arr(size);
			tu_eq_int("random array", ft_strlen(str), strlen(str));
			free(str);
		}
	TEST_END
	return (0);
}