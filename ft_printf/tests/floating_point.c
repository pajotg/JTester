#include "test_utils_printf.h"

CREATE_TMP_VPRINTF(tmp_sprintf,1024)

int main(int argc, char *argv[])
{
	tu_malloc_disable();
	TEST_START
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test(&data, "%%");
		tu_malloc_enable();
		for (int i = 0; i < num_TestFloats; i++)
		{
			float v = TestFloats[i];
			for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
			{
				char* prefix = test_mandatory_flags[prefix_id];

				for (int i = 0; i < num_test_width_len; i++)
					do_test_f(&data, tmp_sprintf("%%%s%sf", prefix, test_width_len[i]), v);
				for (int i = 0; i < num_test_width_len_1; i++)
					do_test_if(&data, tmp_sprintf("%%%s%sf", prefix, test_width_len_1[i]), tu_rand_range(-5, 5), v);
				for (int i = 0; i < num_test_width_len_2; i++)
					do_test_iif(&data, tmp_sprintf("%%%s%sf", prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), v);
			}
		}
		tu_malloc_disable();
		tu_stop_capture_fd(&data);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test(&data, "%%");
		tu_malloc_enable();
		for (int i = 0; i < num_TestFloats; i++)
		{
			float v = TestFloats[i];
			for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
			{
				char* prefix = test_mandatory_flags[prefix_id];

				for (int i = 0; i < num_test_width_len; i++)
					do_test_f(&data, tmp_sprintf("%%%s%sg", prefix, test_width_len[i]), v);
				for (int i = 0; i < num_test_width_len_1; i++)
					do_test_if(&data, tmp_sprintf("%%%s%sg", prefix, test_width_len_1[i]), tu_rand_range(-5, 5), v);
				for (int i = 0; i < num_test_width_len_2; i++)
					do_test_iif(&data, tmp_sprintf("%%%s%sg", prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), v);
			}
		}
		tu_malloc_disable();
		tu_stop_capture_fd(&data);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test(&data, "%%");
		tu_malloc_enable();
		for (int i = 0; i < num_TestFloats; i++)
		{
			float v = TestFloats[i];
			for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
			{
				char* prefix = test_mandatory_flags[prefix_id];

				for (int i = 0; i < num_test_width_len; i++)
					do_test_f(&data, tmp_sprintf("%%%s%se", prefix, test_width_len[i]), v);
				for (int i = 0; i < num_test_width_len_1; i++)
					do_test_if(&data, tmp_sprintf("%%%s%se", prefix, test_width_len_1[i]), tu_rand_range(-5, 5), v);
				for (int i = 0; i < num_test_width_len_2; i++)
					do_test_iif(&data, tmp_sprintf("%%%s%se", prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), v);
			}
		}
		tu_malloc_disable();
		tu_stop_capture_fd(&data);
	TEST_END
	return (0);
}