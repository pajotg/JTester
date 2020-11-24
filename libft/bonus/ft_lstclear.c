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
		tu_ko_message_exit("lstclear called the del function too much!");
		exit(1);
	}
	deleted[num_deletions] = content;
	num_deletions++;
}

static bool has_deleted(size_t c)
{
	for (int i = 0; i < num_deletions; i++)
		if (deleted[i] == (void*)c)
			return true;
	return false;
}

int main(int argc, char *argv[])
{
	TEST_START
		t_list* lst = lst_new(1);
		ft_lstclear(&lst, del);
		tu_eq_pt("lstclear did not set *lst to null", lst, NULL, false, false);
		tu_eq_int("lstclear did not call the delete function!", num_deletions, 1);
		tu_eq_pt("lstclear did not call the delete function.. but it did... what?", deleted[0], (void*)1, false, false);
	TEST
		t_list* new1 = lst_new(1);
		t_list* new2 = lst_new(2);
		t_list* new3 = lst_new(3);
		t_list* new4 = lst_new(4);
		new1->next = new2;
		new2->next = new3;
		new3->next = new4;
		ft_lstclear(&new1, del);
		tu_eq_pt("lstclear did not set *lst to null", new1, NULL, false, false);
		tu_eq_int("lstclear did not call the delete function!", num_deletions, 4);

		tu_eq_bool("lstclear did not call the delete function.. but it did... what?", has_deleted(1), true);
		tu_eq_bool("lstclear did not call the delete function.. but it did... what?", has_deleted(2), true);
		tu_eq_bool("lstclear did not call the delete function.. but it did... what?", has_deleted(3), true);
		tu_eq_bool("lstclear did not call the delete function.. but it did... what?", has_deleted(4), true);
	TEST
		tu_test_can_crash();
		ft_lstclear(NULL, del);
	TEST
		tu_test_can_crash();
		t_list* new1 = lst_new(1);
		ft_lstclear(&new1, NULL);
		tu_eq_int("In my opinion, lstclear should either crash or free the lst when given a NULL del function, but yours did not crash, or free the list", tu_free_non_null_count(), tu_malloc_non_null_count());
	TEST
		tu_free_set_random(true);
		t_list* new1 = lst_new(1);
		t_list* new2 = lst_new(2);
		t_list* new3 = lst_new(3);
		t_list* new4 = lst_new(4);
		new1->next = new2;
		new2->next = new3;
		new3->next = new4;
		ft_lstclear(&new1, del);

		tu_eq_pt("lstclear did not set *lst to null", new1, NULL, false, false);
		tu_eq_int("lstclear did not call the delete function!", num_deletions, 4);

		tu_eq_bool("lstclear did not call the delete function.. but it did... what?", has_deleted(1), true);
		tu_eq_bool("lstclear did not call the delete function.. but it did... what?", has_deleted(2), true);
		tu_eq_bool("lstclear did not call the delete function.. but it did... what?", has_deleted(3), true);
		tu_eq_bool("lstclear did not call the delete function.. but it did... what?", has_deleted(4), true);
	TEST_END

	return (0);
}