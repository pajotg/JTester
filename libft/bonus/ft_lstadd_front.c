#include "libft.h"
#include "test_utils.h"
#include <string.h>
#include <stdio.h>

static t_list* lst_new()
{
	t_list* new = malloc(sizeof(t_list));
	bzero(new, sizeof(t_list));
	return new;
}

int main(int argc, char *argv[])
{
	TEST_START
		t_list* lst = NULL;
		t_list* new = lst_new();
		ft_lstadd_front(&lst, new);
		tu_eq_pt("lstadd_front did not set *lst when *lst == null", lst, new, false, true);
	TEST
		t_list* lst = NULL;
		t_list* new = lst_new();
		ft_lstadd_front(&lst, new);
		tu_eq_pt("lstadd_front did not append to lst", lst, new, false, false);
		free(new);
	TEST
		t_list* lst = NULL;
		t_list* new1 = lst_new();
		t_list* new2 = lst_new();
		t_list* new3 = lst_new();
		t_list* new4 = lst_new();
		ft_lstadd_front(&lst, new1);
		ft_lstadd_front(&lst, new2);
		ft_lstadd_front(&lst, new3);
		ft_lstadd_front(&lst, new4);
		tu_eq_pt("lstadd_front did not append to lst", lst, new4, false, false);
		tu_eq_pt("lstadd_front did not append to lst->next", lst->next, new3, false, false);
		tu_eq_pt("lstadd_front did not append to lst->next->next", lst->next->next, new2, false, false);
		tu_eq_pt("lstadd_front did not append to lst->next->next->next", lst->next->next->next, new1, false, false);
		free(new1);
		free(new2);
		free(new3);
		free(new4);
	TEST_END

	return (0);
}