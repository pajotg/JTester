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

int main(int argc, char *argv[])
{
	TEST_START
		t_list* lst0 = lst_new(1);
		t_list* lst1 = lst_new(1);
		t_list* lst2 = lst_new(1);
		t_list* lst3 = lst_new(1);

		lst0->next = lst1;
		lst1->next = lst2;
		lst2->next = lst3;

		tu_eq_int("lstsize does not return 1 with no next!", ft_lstsize(lst3), 1);
		tu_eq_int("lstsize does not return 2!", ft_lstsize(lst2), 2);
		tu_eq_int("lstsize does not return 3!", ft_lstsize(lst1), 3);
		tu_eq_int("lstsize does not return 4!", ft_lstsize(lst0), 4);

		free(lst0);
		free(lst1);
		free(lst2);
		free(lst3);
	TEST
		tu_test_can_crash();
		tu_eq_int("lstsize does not crash and does not return 0 when given a null pointer", ft_lstsize(NULL),0);
	TEST_END

	return (0);
}