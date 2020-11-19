#include "libft.h"
#include "test_utils.h"
#include <string.h>


int main(int argc, char *argv[])
{
	tu_test_init(argc, argv);
	if (tu_is_test(argv[1],"0"))
	{
		char Arr[42];
		tu_eq_pt("Your memset does not return dst!", ft_memset(Arr, 42, 42), Arr, false, false);
		tu_eq_pt("Your memset does not return dst!", ft_memset(Arr, 21, 21), Arr, false, false);
		for (int i = 0; i < 42; i++)
			tu_eq_char("Your memset did not set value!", Arr[i], i < 21 ? 21 : 42);
	}
	else if (tu_is_test(argv[1],"1"))
	{
		char Arr[42];
		tu_eq_pt("Your memset does not return dst!", ft_memset(Arr, -42, 42), Arr, false, false);
		for (int i = 0; i < 42; i++)
			tu_eq_char("Your memset did not set value!", Arr[i], -42);
	}
	else
		tu_test_stop();
	tu_test_finish();
	return (0);
}