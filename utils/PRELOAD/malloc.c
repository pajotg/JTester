#define _GNU_SOURCE

#if !__linux__
#define USE_INTERSPOSE
#endif

#include <stdio.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef USE_INTERSPOSE
#define PREFIX(_name) my_##_name
#else
#define PREFIX(_name) _name
#endif

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

void PREFIX(tu_malloc_reset)()
{
	malloc_count = 0;
	free_count = 0;
}
int  PREFIX(tu_malloc_count)()
{
	return malloc_count;
}
int  PREFIX(tu_malloc_non_null_count)()
{
	return malloc_non_null_count;
}
int  PREFIX(tu_free_count)()
{
	return free_count;
}
int  PREFIX(tu_free_non_null_count)()
{
	return free_non_null_count;
}

void PREFIX(tu_malloc_null_in)(int num_mallocs)
{
	malloc_stop_id = malloc_count + num_mallocs + 1;
}
void PREFIX(tu_malloc_set_random)(bool random)
{
	malloc_random = random;
}


__attribute__((constructor))
static void Constructor()//(int argc, const char **argv)
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
void *PREFIX(malloc)(size_t bytes)
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

void PREFIX(free)(void* pt)
{
	if (bootstrap)
		return ;

	free_count++;
	if (pt != NULL)	// Freeing a null pointer does nothing, dont count towards the free count
		free_non_null_count++;
	return original_free(pt);
}

#ifdef USE_INTERSPOSE

extern void tu_malloc_reset();
extern int tu_malloc_count();
extern int tu_free_count();
extern int tu_free_non_null_count();
extern void tu_malloc_null_in(int num_mallocs);
extern int tu_malloc_non_null_count();
extern void tu_malloc_set_random(bool random);

// 2 interspose options
#if 1
#define DYLD_INTERPOSE(_replacement,_replacee) \
	__attribute__((used)) static struct{ const void* replacement; const void* replacee; } _interpose_##_replacee \
	__attribute__ ((section ("__DATA,__interpose"))) = { (const void*)(unsigned long)&_replacement, (const void*)(unsigned long)&_replacee };

#define INTERSPOSE(func) DYLD_INTERPOSE(PREFIX(func),func)

INTERSPOSE(tu_malloc_reset);
INTERSPOSE(tu_malloc_count);
INTERSPOSE(tu_malloc_non_null_count);
INTERSPOSE(tu_free_count);
INTERSPOSE(tu_free_non_null_count);
INTERSPOSE(tu_malloc_null_in);
INTERSPOSE(tu_malloc_set_random);
INTERSPOSE(malloc);
INTERSPOSE(free);

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
