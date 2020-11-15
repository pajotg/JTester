#include "libft.h"
#include "test_utils.h"
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		write(STDOUT_FILENO, "argc != 2", 9);
		return (1);
	}
	if (tu_is_test(argv[1],"0"))
		tu_eq_int("basic input", ft_strlen("Hello world!"), 12);
	else if (tu_is_test(argv[1],"1"))
		tu_eq_int("empty string", ft_strlen(""), 0);
	else if (tu_is_test(argv[1],"2"))
	{
		tu_test_can_crash();
		ft_strlen(NULL);
		tu_ok_exit();
	}
	else if (tu_is_test(argv[1],"3"))
		for (int i = 0; i < 250; i++)
		{
			int size = tu_rand_range(0,125);
			char* str = tu_rand_str(size);
			tu_eq_int("random valid string", ft_strlen(str), size);
			free(str);
		}
	else if (tu_is_test(argv[1],"4"))
		for (int i = 0; i < 250; i++)
		{
			int size = tu_rand_range(0,125);
			char* str = tu_rand_arr(size);
			tu_eq_int("random array", ft_strlen(str), strlen(str));
			free(str);
		}
	else
		tu_test_stop();
	tu_test_finish();
	return (0);
}