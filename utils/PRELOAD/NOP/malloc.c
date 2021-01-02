#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void error()
{
	fprintf(stderr, "Failed to use LD_PRELOAD to override NOP functions!");
	exit(1);
}

void tu_malloc_enable() { error(); };
void tu_malloc_disable() { error(); };
bool tu_malloc_is_enabled() { error(); return -1; }

void tu_malloc_reset() { error(); };
int tu_malloc_count() { error(); return -1; }
int tu_malloc_non_null_count() { error(); return -1; }
int tu_free_count() { error(); return -1; }
int tu_free_non_null_count() { error(); return -1; };
void tu_malloc_null_in(int num_mallocs) { error(); }
void tu_malloc_set_random(bool random) { error(); }
void tu_free_set_random(bool random) { error(); }