#include "libft.h"
#include "test_utils.h"

int main(int argc, char *argv[])
{
	TEST_START
		tu_eq_str("zero", ft_itoa(0), "0", true, false);
	TEST
		tu_eq_str("basic input", ft_itoa(5), "5", true, false);
	TEST
		tu_eq_str("basic input",ft_itoa(-5), "-5", true, false);
	TEST
		tu_eq_str("maximum value",ft_itoa(2147483647), "2147483647", true, false);
	TEST
		tu_eq_str("minimum value",ft_itoa(-2147483648), "-2147483648", true, false);
	TEST_END
	return (0);
}