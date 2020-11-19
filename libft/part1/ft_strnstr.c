#include "libft.h"
#include "test_utils.h"
#include <string.h>

int main(int argc, char *argv[])
{
	tu_test_init(argc, argv);
	if (tu_is_test(argv[1],"0"))
		tu_eq_str("basic input", ft_strnstr("Hello World", "World", 20), "World", false, false);
	else if (tu_is_test(argv[1],"1"))
		tu_eq_str("(x, x, strlen(x)) != x", ft_strnstr("World", "World", 5), "World", false, false);
	else if (tu_is_test(argv[1],"2"))
		tu_eq_str("(x, x, strlen(x) - 1) != NULL", ft_strnstr("World", "World", 4), NULL, false, false);
	else if (tu_is_test(argv[1],"3"))
		tu_eq_str("abat in ababat", ft_strnstr("ababat", "abat", 6), "abat", false, false);
	else if (tu_is_test(argv[1],"4"))
		tu_eq_str("abat found in ababat while len does not allouw it", ft_strnstr("ababat", "abat", 5), NULL, false, false);
	else if (tu_is_test(argv[1],"5"))
		tu_eq_str("empty needle", ft_strnstr("Hello World", "", 5), "Hello World", false, false);
	else if (tu_is_test(argv[1],"6"))
		tu_eq_str("empty needle len 0", ft_strnstr("Hello World", "", 0), "Hello World", false, false);
	else if (tu_is_test(argv[1],"7"))
		ft_strnstr(NULL, "", 5);
	else if (tu_is_test(argv[1],"8"))
	{
		tu_test_should_crash();
		ft_strnstr(NULL, "hey", 0);
	}
	else if (tu_is_test(argv[1],"9"))
	{
		tu_test_should_crash();
		ft_strnstr("ah yes", NULL, 0);
	}
	else
		tu_test_stop();
	tu_test_finish();
	return (0);
}