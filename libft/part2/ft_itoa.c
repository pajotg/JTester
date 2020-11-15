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
		tu_eq_str("zero", ft_itoa(0), "0", true, false);
	else if (tu_is_test(argv[1],"1"))
		tu_eq_str("basic input", ft_itoa(5), "5", true, false);
	else if (tu_is_test(argv[1],"2"))
		tu_eq_str("basic input",ft_itoa(-5), "-5", true, false);
	else if (tu_is_test(argv[1],"3"))
		tu_eq_str("basic input",ft_itoa(2147483647), "2147483647", true, false);
	else if (tu_is_test(argv[1],"4"))
		tu_eq_str("basic input",ft_itoa(-2147483648), "-2147483648", true, false);
	else
		tu_test_stop();
	tu_test_finish();
	return (0);
}