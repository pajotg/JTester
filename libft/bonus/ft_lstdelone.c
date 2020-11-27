#include "libft.h"
#include "test_utils.h"
#include <string.h>
#include <stdio.h>

static t_list* lst_new(size_t index)
{
	t_list* new = malloc(sizeof(t_list));
	bzero(new, sizeof(t_list));
	new->content = (void*)index;
	return new;
}

static int num_deletions = 0;
static void* deleted[5];
static void del(void* content)
{
	if (num_deletions == 5)
	{
		tu_ko_message_exit("lstdelone called the del function too much!");
		exit(1);
	}
	deleted[num_deletions] = content;
	num_deletions++;
}

int main(int argc, char *argv[])
{
	TEST_START
		ft_lstdelone(lst_new(1), del);
		tu_eq_int("lstdelone did not call the delete function!", num_deletions, 1);
		tu_eq_pt("lstdelone did not call the delete function.. but it did... what?", deleted[0], (void*)1, false, false);
	TEST
		tu_test_can_crash();
		ft_lstdelone(lst_new(1), NULL);
		if (tu_free_non_null_count() == 0)
			tu_ko_message_exit("lstdelone did not free the list, but also did not crash when the del function was null!");
	TEST
		tu_test_can_crash();
		ft_lstdelone(NULL, del);
		tu_eq_int("lstdelone called the delete function even tho lst == NULL", num_deletions, 0);
	TEST_END

	return (0);
}