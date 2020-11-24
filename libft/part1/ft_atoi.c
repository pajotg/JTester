#include "libft.h"
#include "test_utils.h"

int main(int argc, char *argv[])
{
	TEST_START
		tu_eq_int("non number input", ft_atoi("hello"), 0);
	TEST
		tu_eq_int("basic input", ft_atoi("5"), 5);
	TEST
		tu_eq_int("basic input",ft_atoi("-5"), -5);
	TEST
		tu_eq_int("zero",ft_atoi("0"), 0);
	TEST
		tu_eq_int("+ sign", ft_atoi("+5"), 5);
	TEST
		tu_eq_int("spaces", ft_atoi("   -5 56"), -5);
	TEST
		tu_eq_int("maximum number", ft_atoi("+2147483647"), 2147483647);
	TEST
		tu_eq_int("minimum number", ft_atoi("-2147483648"), -2147483648);
	TEST
		tu_test_should_crash();
		ft_atoi(NULL);
	TEST
		tu_eq_int("empty string", ft_atoi(""), 0);
	TEST_END
	return (0);
}