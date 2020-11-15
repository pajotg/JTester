#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <stdlib.h>

void *(*original_malloc)(size_t);
void (*original_free)(void*);

// Because we need a functioning malloc to get the original malloc pt we use a bootstrap malloc
static char bootstrap_data[1024*32]; // 32K ought to be enough
static size_t bootstrap_loc = 0;
static bool bootstrap = false;

static int malloc_count = 0;
static int malloc_non_null_count = 0;
static int free_count = 0;
static int free_non_null_count = 0;
static int malloc_stop_id = -1;
static bool malloc_random = false;

void tu_malloc_reset()
{
	malloc_count = 0;
	free_count = 0;
}
int tu_malloc_count()
{
	return malloc_count;
}
int tu_malloc_non_null_count()
{
	return malloc_non_null_count;
}
int tu_free_count()
{
	return free_count;
}
int tu_free_non_null_count()
{
	return free_non_null_count;
}

void tu_malloc_null_in(int num_mallocs)
{
	malloc_stop_id = malloc_count + num_mallocs + 1;
}
void tu_malloc_set_random(bool random)
{
	malloc_random = random;
}

void _init()
{
	bootstrap = true;
	//fprintf(stderr, "Init!");

	original_malloc = dlsym(RTLD_NEXT, "malloc");
	original_free = dlsym(RTLD_NEXT, "free");
	bootstrap = false;
}

void *bootstrap_malloc(size_t bytes)
{
	char* pt = &bootstrap_data[bootstrap_loc];
	bootstrap_loc += bytes;
	return pt;
}
void *malloc(size_t bytes)
{
	if (bootstrap)
		return bootstrap_malloc(bytes);

	malloc_count++;
	if (malloc_count == malloc_stop_id) {
		return (NULL);
	}
	void* pt = original_malloc(bytes);
	if (pt)
	{
		malloc_non_null_count++;
		if (malloc_random)
			for (size_t i = 0; i < bytes; i++)
				((unsigned char*)pt)[i] = rand();
	}
	return pt;
}
void free(void* pt)
{
	if (bootstrap)
		return ;

	free_count++;
	if (pt != NULL)	// Freeing a null pointer does nothing, dont count towards the free count
		free_non_null_count++;
	return original_free(pt);
}