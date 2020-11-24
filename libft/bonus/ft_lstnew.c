#include "libft.h"
#include "test_utils.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	TEST_START
		tu_malloc_set_random(true);
		t_list* lst = ft_lstnew((void*)5);
		if (lst == NULL)
			tu_warning_message_exit("lstnew failed to allocated?");
		tu_eq_pt("lstnew did not clear next!", lst->next, NULL, false, false);
		tu_eq_pt("lstnew did not set content!", lst->content, (void*)5, false, false);
		free(lst);
	TEST
		tu_malloc_set_random(true);
		tu_malloc_null_in(0);
		t_list* lst = ft_lstnew((void*)5);
		tu_eq_pt("lstnew allocated while your malloc should have returned null? are you cheating by using calloc?", lst, NULL, false, false);
	TEST_END

	return (0);
}