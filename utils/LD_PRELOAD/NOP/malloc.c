#include <stdbool.h>

void tu_malloc_reset() {};
int tu_malloc_count() { return -1; }
int tu_malloc_non_null_count() { return -1; }
int tu_free_count() { return -1; }
int tu_free_non_null_count() { return -1; };
void tu_malloc_null_in(int num_mallocs) {}
void tu_malloc_set_random(bool random) {}