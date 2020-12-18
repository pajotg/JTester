#include "libft.h"
#include "test_utils.h"
#include <string.h>


int main(int argc, char *argv[])
{
	TEST_START
		char Arr[42];
		tu_eq_pt("Your memset does not return dst!", ft_memset(Arr, 42, 42), Arr, false, false);
		for (int i = 0; i < 42; i++)
			tu_eq_char("Your memset did not set pt[%i] to 42", Arr[i], 42, i);
		tu_eq_pt("Your memset does not return dst!", ft_memset(Arr, 21, 21), Arr, false, false);
		for (int i = 0; i < 21; i++)
			tu_eq_char("Your memset did not set pt[%i] to 21!", Arr[i], 21, i);
		for (int i = 21; i < 42; i++)
			tu_eq_char("Your memset overrode pt[%i] to 21!", Arr[i], 42, i);
	TEST
		char Arr[42];
		tu_eq_pt("Your memset does not return dst!", ft_memset(Arr, -42, 42), Arr, false, false);
		for (int i = 0; i < 42; i++)
			tu_eq_char("Your memset did not set unsigned values correctly! expected %i but got %i!", Arr[i], -42, -42, Arr[i]);
	TEST_END
	return (0);
}