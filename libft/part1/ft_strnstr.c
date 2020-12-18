#include "libft.h"
#include "test_utils.h"
#include <string.h>

int main(int argc, char *argv[])
{
	TEST_START
		tu_eq_str("basic input", ft_strnstr("Hello World", "World", 20), "World", false, false);
	TEST
		tu_eq_str("(x, x, strlen(x)) != x", ft_strnstr("World", "World", 5), "World", false, false);
	TEST
		tu_eq_str("(x, x, strlen(x) - 1) != NULL", ft_strnstr("World", "World", 4), NULL, false, false);
	TEST
		tu_eq_str("abat in ababat", ft_strnstr("ababat", "abat", 6), "abat", false, false);
	TEST
		tu_eq_str("abat found in ababat while len does not allouw it", ft_strnstr("ababat", "abat", 5), NULL, false, false);
	TEST
		tu_eq_str("empty needle", ft_strnstr("Hello World", "", 5), "Hello World", false, false);
	TEST
		tu_eq_str("empty needle with length 0", ft_strnstr("Hello World", "", 0), "Hello World", false, false);
	TEST
		ft_strnstr(NULL, "", 5);
	TEST
		tu_test_should_crash();
		ft_strnstr(NULL, "hey", 1);
	TEST
		tu_test_should_crash();
		ft_strnstr("ah yes", NULL, 0);
	TEST_END
	return (0);
}