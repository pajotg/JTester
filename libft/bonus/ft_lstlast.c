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

		tu_eq_pt("lstlast does not return itself with no next!", ft_lstlast(lst3), lst3, false, false);
		tu_eq_pt("lstlast does not return the last element!", ft_lstlast(lst2), lst3, false, false);
		tu_eq_pt("lstlast does not return the last element!", ft_lstlast(lst1), lst3, false, false);
		tu_eq_pt("lstlast does not return the last element!", ft_lstlast(lst0), lst3, false, false);

		free(lst0);
		free(lst1);
		free(lst2);
		free(lst3);
	TEST
		tu_test_can_crash();
		tu_eq_pt("lstlast does not crash and does not return 0 when given a null pointer", ft_lstlast(NULL), NULL, false, false);
	TEST_END

	return (0);
}