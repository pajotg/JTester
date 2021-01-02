#define _GNU_SOURCE

#if !__linux__
#define USE_INTERSPOSE
#endif


#if __linux__
# include <malloc.h>
# define MALLOC_SIZE malloc_usable_size
#else
# include "malloc/malloc.h"
# define MALLOC_SIZE malloc_size
#endif

#include <stdio.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef USE_INTERSPOSE
void *(*original_malloc)(size_t);
void (*original_free)(void*);

// Because we need a functioning malloc to get the original malloc pt we use a bootstrap malloc
static char bootstrap_data[1024*32]; // 32K ought to be enough
static size_t bootstrap_loc = 0;
static bool bootstrap = false;
#endif

static int malloc_count = 0;
static int malloc_non_null_count = 0;
static int free_count = 0;
static int free_non_null_count = 0;
static int malloc_stop_id = -1;
static bool malloc_random = false;
static bool free_random = false;

static bool enabled = true;

void tu_malloc_enable()
{
	enabled = true;
}
void tu_malloc_disable()
{
	enabled = false;
}
bool tu_malloc_is_enabled()
{
	return enabled;
}

void tu_malloc_reset()
{
	malloc_count = 0;
	malloc_non_null_count = 0;
	free_count = 0;
	free_non_null_count = 0;
}
int  tu_malloc_count()
{
	return malloc_count;
}
int  tu_malloc_non_null_count()
{
	return malloc_non_null_count;
}
int  tu_free_count()
{
	return free_count;
}
int  tu_free_non_null_count()
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
void tu_free_set_random(bool random)
{
	free_random = random;
}


#ifndef USE_INTERSPOSE
__attribute__((constructor))
static void Constructor()//(int argc, const char **argv)
{
	bootstrap = true;
	//fprintf(stderr, "Init!");

	original_malloc = dlsym(RTLD_NEXT, "malloc");
	original_free = dlsym(RTLD_NEXT, "free");

	bootstrap = false;
}

void* bootstrap_malloc(size_t bytes)
{
	char* pt = &bootstrap_data[bootstrap_loc];
	bootstrap_loc += bytes;
	return pt;
}
#endif

#ifdef USE_INTERSPOSE
void* my_malloc(size_t bytes)
#else
void* malloc(size_t bytes)
#endif
{
	#ifndef USE_INTERSPOSE
	if (bootstrap)
		return bootstrap_malloc(bytes);
	#endif

	if (enabled)
	{
		malloc_count++;
		if (malloc_count == malloc_stop_id) {
			return (NULL);
		}
	}

	#ifdef USE_INTERSPOSE
	void* pt = malloc(bytes);
	#else
	void* pt = original_malloc(bytes);
	#endif
	if (pt && enabled)
	{
		malloc_non_null_count++;
		if (malloc_random)
		{
			bytes = MALLOC_SIZE(pt);
			for (size_t i = 0; i < bytes; i++)
				((unsigned char*)pt)[i] = rand();
		}
	}
	return pt;
}

#ifdef USE_INTERSPOSE
void my_free(void* pt)
#else
void free(void* pt)
#endif
{
	#ifndef USE_INTERSPOSE
	if (bootstrap)
		return ;
	#endif

	if (enabled)
	{
		free_count++;
		if (pt != NULL)	// Freeing a null pointer does nothing, dont count towards the free count
			free_non_null_count++;
	}

	if (free_random && pt != NULL && enabled)
	{
		size_t bytes = MALLOC_SIZE(pt);
		for (size_t i = 0; i < bytes; i++)
			((unsigned char*)pt)[i] = rand();
	}

	#ifdef USE_INTERSPOSE
	free(pt);
	#else
	original_free(pt);
	#endif
}

#ifdef USE_INTERSPOSE

// 2 interspose options
#if 1
#define DYLD_INTERPOSE(_replacement,_replacee) \
	__attribute__((used)) static struct{ const void* replacement; const void* replacee; } _interpose_##_replacee \
	__attribute__ ((section ("__DATA,__interpose"))) = { (const void*)(unsigned long)&_replacement, (const void*)(unsigned long)&_replacee };

DYLD_INTERPOSE(my_malloc, malloc)
DYLD_INTERPOSE(my_free, free)

#else

typedef struct	interspose_s
{
	void *new_func;
	void *orig_func;
}				interspose_t;

__attribute__((used)) static const interspose_t interspose_functions[] __attribute__((section("__DATA, __interspose"))) =
{
	{ PREFIX(tu_malloc_reset), 			tu_malloc_reset },
	{ PREFIX(tu_malloc_count),			tu_malloc_count},
	{ PREFIX(tu_malloc_non_null_count),	tu_malloc_non_null_count},
	{ PREFIX(tu_free_count),			tu_free_count},
	{ PREFIX(tu_free_non_null_count),	tu_free_non_null_count},
	{ PREFIX(tu_malloc_null_in),		tu_malloc_null_in},
	{ PREFIX(tu_malloc_set_random),		tu_malloc_set_random},
	{ PREFIX(malloc),					malloc},
	{ PREFIX(free),						free},
};
#endif

#endif
