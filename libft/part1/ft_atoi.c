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
		tu_eq_int("non number input", ft_atoi("hello"), 0);
	else if (tu_is_test(argv[1],"1"))
		tu_eq_int("basic input", ft_atoi("5"), 5);
	else if (tu_is_test(argv[1],"2"))
		tu_eq_int("basic input",ft_atoi("-5"), -5);
	else if (tu_is_test(argv[1],"3"))
		tu_eq_int("zero",ft_atoi("0"), 0);
	else if (tu_is_test(argv[1],"4"))
		tu_eq_int("+ sign", ft_atoi("+5"), 5);
	else if (tu_is_test(argv[1],"5"))
		tu_eq_int("spaces", ft_atoi("   -5 56"), -5);
	else if (tu_is_test(argv[1],"6"))
		tu_eq_int("maximum number", ft_atoi("+2147483647"), 2147483647);
	else if (tu_is_test(argv[1],"7"))
		tu_eq_int("minimum number", ft_atoi("-2147483648"), -2147483648);
	else if (tu_is_test(argv[1],"8"))
	{
		tu_test_should_crash();
		ft_atoi(NULL);
	}
	else if (tu_is_test(argv[1],"9"))
		tu_eq_int("empty string", ft_atoi(""), 0);
	else
		tu_test_stop();
	tu_test_finish();
	return (0);
}