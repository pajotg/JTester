#include "test_utils.h"

int tu_rand_range(int min, int max)
{
	int range = max-min;
	int value = rand() % range;
	return min + value;
}

void tu_randomize_arr(void* arr, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		((char*)arr)[i] = (char)rand();
	}
}
void tu_randomize_arr_range(void* arr, int Size, char min, char max)
{
	for (int i = 0; i < Size; i++)
	{
		((char*)arr)[i] = (char)tu_rand_range(min, max);
	}
}
void tu_randomize_arr_map(void* arr, int Size, char* values, int value_count)
{
	for (int i = 0; i < Size; i++)
		((char*)arr)[i] = values[tu_rand_range(0, value_count)];
}

char* tu_rand_arr(int size)
{
	char* arr = malloc(size);
	tu_randomize_arr(arr, size);
	return arr;
}
char* tu_rand_map(int size, char* values, int value_count)
{
	char* arr = malloc(size);
	tu_randomize_arr_map(arr, size, values, value_count);
	return arr;
}
char* tu_rand_str(int size)
{
	char* arr = malloc(size + 1);
	tu_randomize_arr_map(arr, size, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ", 63);
	arr[size] = '\0';
	return arr;
}