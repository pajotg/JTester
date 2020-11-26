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

static int num_iterations = 0;
static size_t iterated[5];
static void iter(void* content)
{
	if (num_iterations == 5)
	{
		tu_ko_message_exit("lstiter called the iter function too much!");
		exit(1);
	}
	iterated[num_iterations] = (size_t)content;
	num_iterations++;
}

static bool has_iterated(size_t c)
{
	for (int i = 0; i < num_iterations; i++)
		if (iterated[i] == c)
			return true;
	return false;
}

int main(int argc, char *argv[])
{
	TEST_START
		t_list* lst0 = lst_new(1);
		t_list* lst1 = lst_new(2);
		t_list* lst2 = lst_new(3);
		t_list* lst3 = lst_new(4);

		lst0->next = lst1;
		lst1->next = lst2;
		lst2->next = lst3;

		ft_lstiter(lst0, iter);

		tu_eq_int("lstiter did not call the iter function the correct ammount of times!", num_iterations, 4);
		tu_eq_bool("lstiter did not call the iter function on the first index!", has_iterated(1), true);
		tu_eq_bool("lstiter did not call the iter function on the second index!", has_iterated(2), true);
		tu_eq_bool("lstiter did not call the iter function on the third index!", has_iterated(3), true);
		tu_eq_bool("lstiter did not call the iter function on the last index!", has_iterated(4), true);

		free(lst0);
		free(lst1);
		free(lst2);
		free(lst3);
	TEST
		tu_test_can_crash();
		ft_lstiter(NULL, iter);
		tu_eq_int("lstiter called the iter function with a null list!", num_iterations, 0);
	TEST
		tu_test_can_crash();
		ft_lstiter(NULL, NULL);
	TEST
		tu_test_can_crash();
		t_list* lst0 = lst_new(1);
		lst0->next = (void*)5;	// this should create a segfault, while making any check for null return false
		// Thus, this will crash if you checked the iter function inside the loop instead of before
		ft_lstiter(lst0, NULL);
		free(lst0);
	TEST_END

	return (0);
}