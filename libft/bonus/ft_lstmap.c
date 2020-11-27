#include "libft.h"
#include "test_utils.h"
#include <string.h>
#include <stdio.h>

static t_list* lst_new(size_t index)
{
	t_list* new = malloc(sizeof(t_list));
	if (new == NULL)
		tu_warning_message_exit("Malloc failed in test!");
	bzero(new, sizeof(t_list));
	new->content = (void*)index;
	return new;
}

void* map_content(void* content)
{
	return content + 5;
}

void* clone_content(void* content)
{
	return content;
}
void* null_content(void* content)
{
	(void)content;
	return NULL;
}

static int num_deletions = 0;
static void* deleted[5];
static void del(void* content)
{
	if (num_deletions == 5)
	{
		tu_ko_message_exit("lstmap called the del function too much!");
		exit(1);
	}
	deleted[num_deletions] = content;
	num_deletions++;
}

t_list* create_lst(int size)
{
	if (size == 0)
		return NULL;
	int count = 0;
	t_list* start = lst_new(count++);
	t_list* curr = start;

	while (count < size)
	{
		curr->next = lst_new(count++);
		curr = curr->next;
	}
	return start;
}

void free_lst(t_list* lst)
{
	if (lst->next)
		free_lst(lst->next);
	free(lst);
}

void compare(t_list* input, t_list* output, void *(*f)(void *))
{
	while (input && output)
	{
		if (output->content != f(input->content))
			tu_ko_message_exit("lstmap did not correctly apply the content!");
		input = input->next;
		output = output->next;
	}
	if (output != NULL || input != NULL)
		tu_ko_message_exit("Input length and output length are not the same!");
}

int main(int argc, char *argv[])
{
	TEST_START
		t_list* lst = create_lst(1);
		t_list* new = ft_lstmap(lst, map_content, del);
		compare(lst, new, map_content);
		free_lst(lst);
		free_lst(new);
	TEST
		t_list* lst = create_lst(5);

		t_list* new = ft_lstmap(lst, map_content, del);
		compare(lst, new, map_content);
		free_lst(lst);
		free_lst(new);
	TEST
		t_list* lst = create_lst(5);

		tu_malloc_null_in(0);
		t_list* new = ft_lstmap(lst, map_content, del);
		tu_eq_pt("Your lstmap still returns a list even tho your malloc returned null, are you cheating by using calloc?", new, NULL, false, false);
		tu_eq_int("Your lstmap called the del function on... something...", num_deletions, 0);
		free_lst(lst);
	TEST
		t_list* lst = create_lst(5);

		tu_malloc_null_in(1);
		t_list* new = ft_lstmap(lst, map_content, del);
		tu_eq_pt("Your lstmap still returns a list even tho your second malloc returned null, are you cheating by using calloc?", new, NULL, false, false);
		tu_eq_int("Your lstmap did not call the del function on your already allocated lists", num_deletions, 1);
		free_lst(lst);
	TEST
		t_list* lst = create_lst(5);

		tu_malloc_null_in(4);
		t_list* new = ft_lstmap(lst, map_content, del);
		tu_eq_pt("Your lstmap still returns a list even tho your last malloc returned null, are you cheating by using calloc?", new, NULL, false, false);
		tu_eq_int("Your lstmap did not call the del function on your already allocated lists", num_deletions, 4);
		free_lst(lst);
	TEST
		tu_test_can_crash();
		t_list* lst = create_lst(5);

		t_list* new = ft_lstmap(lst, NULL, del);
		if (new)
		{
			if (new->content == NULL)
				compare(lst, new, null_content);
			else
				compare(lst, new, clone_content);
			free_lst(new);
		}
		else
		{
			tu_ok_message("lstmap returns NULL with null f");
		}
		free_lst(lst);
	TEST
		tu_test_can_crash();
		t_list* lst = create_lst(5);

		tu_malloc_null_in(4);
		t_list* new = ft_lstmap(lst, map_content, NULL);
		tu_eq_pt("Your lstmap still returns a list even tho your last malloc returned null, are you cheating by using calloc?", new, NULL, false, false);
		free_lst(lst);
	TEST_END

	return (0);
}