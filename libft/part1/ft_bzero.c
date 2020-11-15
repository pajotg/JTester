#include "libft.h"
#include "test_utils.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		write(STDOUT_FILENO, "argc != 2", 9);
		return (1);
	}
	if (tu_is_test(argv[1],"0"))
	{
		char* allocated = (char*)malloc(42);
		for (int i = 0; i < 42; i++)
			allocated[i] = 42;
		ft_bzero(allocated, 21);
		for (int i = 0; i < 21; i++)
			if (allocated[i] != 0)
				tu_ko_exit("Failed to write");
		for (int i = 21; i < 42; i++)
			if (allocated[i] != 42)
				tu_ko_exit("wrote too much!");
		tu_ok_exit();
	}
	else if (tu_is_test(argv[1],"1"))
	{
		ft_bzero(NULL, 0);
		tu_ok_exit();
	}
	else if (tu_is_test(argv[1],"2"))
	{
		tu_test_can_crash();
		ft_bzero(NULL, 21);
		tu_ok_exit();
	}
	else
		tu_test_stop();
	tu_test_finish();
	return (0);
}