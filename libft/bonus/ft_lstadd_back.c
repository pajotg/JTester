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
		ft_lstadd_back(&lst, new);
		tu_eq_pt("lstadd_back did not set *lst when *lst == null", lst, new, false, false);
		tu_eq_pt("lstadd_back set next while it should not have done so!", lst->next, NULL, false, false);
		free(new);
	TEST
		t_list* lst = lst_new();
		t_list* new = lst_new();
		ft_lstadd_back(&lst, new);
		tu_eq_pt("lstadd_back did not append to lst", lst->next, new, false, true);
		free(lst);
	TEST
		t_list* lst = lst_new();
		t_list* new1 = lst_new();
		t_list* new2 = lst_new();
		t_list* new3 = lst_new();
		t_list* new4 = lst_new();
		ft_lstadd_back(&lst, new1);
		ft_lstadd_back(&lst, new2);
		ft_lstadd_back(&lst, new3);
		ft_lstadd_back(&lst, new4);
		tu_eq_pt("lstadd_back did not append to lst", lst->next, new1, false, false);
		tu_eq_pt("lstadd_back did not append to lst->next", lst->next->next, new2, false, false);
		tu_eq_pt("lstadd_back did not append to lst->next->next", lst->next->next->next, new3, false, false);
		tu_eq_pt("lstadd_back did not append to lst->next->next->next", lst->next->next->next->next, new4, false, false);
		free(lst);
		free(new1);
		free(new2);
		free(new3);
		free(new4);
	TEST_END

	return (0);
}