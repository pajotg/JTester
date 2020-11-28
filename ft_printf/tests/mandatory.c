#include "test_utils_printf.h"

CREATE_TMP_VPRINTF(tmp_sprintf,1024)

// cspdiuxX%
// u

int main(int argc, char *argv[])
{
	TEST_START
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test(&data, "%%");
		tu_malloc_reset();	// Static variables...
		for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
		{
			char* prefix = test_mandatory_flags[prefix_id];

			for (int i = 0; i < num_test_width_len; i++)
				do_test(&data, tmp_sprintf("%%%s%s%%", prefix, test_width_len[i]));
			for (int i = 0; i < num_test_width_len_1; i++)
				do_test_i(&data, tmp_sprintf("%%%s%s%%", prefix, test_width_len_1[i]), tu_rand_range(-5, 5));
			for (int i = 0; i < num_test_width_len_2; i++)
				do_test_ii(&data, tmp_sprintf("%%%s%s%%", prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5));
		}
		do_test(&data, "%2%%5%%.2%");
		do_test(&data, "Hey %% %% %% there!");
		tu_stop_capture_fd(&data);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test_i(&data, "%c", 'A');
		tu_malloc_reset();	// Static variables...
		for (int i = 0; i < num_TestChars; i++)
		{
			char c = TestChars[i];
			for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
			{
				char* prefix = test_mandatory_flags[prefix_id];

				for (int i = 0; i < num_test_width_len; i++)
					do_test_i(&data, tmp_sprintf("%%%s%sc", prefix, test_width_len[i]), c);
				for (int i = 0; i < num_test_width_len_1; i++)
					do_test_ii(&data, tmp_sprintf("%%%s%sc", prefix, test_width_len_1[i]), tu_rand_range(-5, 5), c);
				for (int i = 0; i < num_test_width_len_2; i++)
					do_test_iii(&data, tmp_sprintf("%%%s%sc", prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), c);
			}
		}
		tu_stop_capture_fd(&data);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test_i(&data, "%i", 5);
		tu_malloc_reset();	// Static variables...
		for (int i = 0; i < num_TestInts; i++)
		{
			int c = TestInts[i];
			for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
			{
				char* prefix = test_mandatory_flags[prefix_id];

				for (int i = 0; i < num_test_width_len; i++)
					do_test_i(&data, tmp_sprintf("%%%s%si", prefix, test_width_len[i]), c);
				for (int i = 0; i < num_test_width_len_1; i++)
					do_test_ii(&data, tmp_sprintf("%%%s%si", prefix, test_width_len_1[i]), tu_rand_range(-5, 5), c);
				for (int i = 0; i < num_test_width_len_2; i++)
					do_test_iii(&data, tmp_sprintf("%%%s%si", prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), c);
			}
		}
		tu_stop_capture_fd(&data);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test_p(&data, "%p", NULL);
		tu_malloc_reset();	// Static variables...
		for (int i = 0; i < num_TestPointers; i++)
		{
			void* c = TestPointers[i];
			for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
			{
				char* prefix = test_mandatory_flags[prefix_id];

				for (int i = 0; i < num_test_width_len; i++)
					do_test_p(&data, tmp_sprintf("%%%s%sp", prefix, test_width_len[i]), c);
				for (int i = 0; i < num_test_width_len_1; i++)
					do_test_ip(&data, tmp_sprintf("%%%s%sp", prefix, test_width_len_1[i]), tu_rand_range(-5, 5), c);
				for (int i = 0; i < num_test_width_len_2; i++)
					do_test_iip(&data, tmp_sprintf("%%%s%sp", prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), c);
			}
		}
		tu_stop_capture_fd(&data);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test_p(&data, "%d", NULL);
		tu_malloc_reset();	// Static variables...
		for (int i = 0; i < num_TestInts; i++)
		{
			int c = TestInts[i];
			for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
			{
				char* prefix = test_mandatory_flags[prefix_id];

				for (int i = 0; i < num_test_width_len; i++)
					do_test_i(&data, tmp_sprintf("%%%s%sd", prefix, test_width_len[i]), c);
				for (int i = 0; i < num_test_width_len_1; i++)
					do_test_ii(&data, tmp_sprintf("%%%s%sd", prefix, test_width_len_1[i]), tu_rand_range(-5, 5), c);
				for (int i = 0; i < num_test_width_len_2; i++)
					do_test_iii(&data, tmp_sprintf("%%%s%sd", prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), c);
			}
		}
		tu_stop_capture_fd(&data);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test_p(&data, "%x", NULL);
		tu_malloc_reset();	// Static variables...
		for (int i = 0; i < num_TestInts; i++)
		{
			int c = TestInts[i];
			for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
			{
				char* prefix = test_mandatory_flags[prefix_id];

				for (int i = 0; i < num_test_width_len; i++)
					do_test_i(&data, tmp_sprintf("%%%s%sx", prefix, test_width_len[i]), c);
				for (int i = 0; i < num_test_width_len_1; i++)
					do_test_ii(&data, tmp_sprintf("%%%s%sx", prefix, test_width_len_1[i]), tu_rand_range(-5, 5), c);
				for (int i = 0; i < num_test_width_len_2; i++)
					do_test_iii(&data, tmp_sprintf("%%%s%sx", prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), c);
			}
		}
		tu_stop_capture_fd(&data);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test_p(&data, "%X", NULL);
		tu_malloc_reset();	// Static variables...
		for (int i = 0; i < num_TestInts; i++)
		{
			int c = TestInts[i];
			for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
			{
				char* prefix = test_mandatory_flags[prefix_id];

				for (int i = 0; i < num_test_width_len; i++)
					do_test_i(&data, tmp_sprintf("%%%s%sX", prefix, test_width_len[i]), c);
				for (int i = 0; i < num_test_width_len_1; i++)
					do_test_ii(&data, tmp_sprintf("%%%s%sX", prefix, test_width_len_1[i]), tu_rand_range(-5, 5), c);
				for (int i = 0; i < num_test_width_len_2; i++)
					do_test_iii(&data, tmp_sprintf("%%%s%sX", prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), c);
			}
		}
		tu_stop_capture_fd(&data);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test_p(&data, "%u", NULL);
		tu_malloc_reset();	// Static variables...
		for (int i = 0; i < num_TestInts; i++)
		{
			int c = TestInts[i];
			for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
			{
				char* prefix = test_mandatory_flags[prefix_id];

				for (int i = 0; i < num_test_width_len; i++)
					do_test_i(&data, tmp_sprintf("%%%s%su", prefix, test_width_len[i]), c);
				for (int i = 0; i < num_test_width_len_1; i++)
					do_test_ii(&data, tmp_sprintf("%%%s%su", prefix, test_width_len_1[i]), tu_rand_range(-5, 5), c);
				for (int i = 0; i < num_test_width_len_2; i++)
					do_test_iii(&data, tmp_sprintf("%%%s%su", prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), c);
			}
		}
		tu_stop_capture_fd(&data);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test_p(&data, "%s", NULL);
		tu_malloc_reset();	// Static variables...
		for (int i = 0; i < num_TestStrings; i++)
		{
			char* c = TestStrings[i];
			for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
			{
				char* prefix = test_mandatory_flags[prefix_id];
				for (int i = 0; i < num_test_width_len; i++)
					do_test_s(&data, tmp_sprintf("%%%s%ss", prefix, test_width_len[i]), c);
				for (int i = 0; i < num_test_width_len_1; i++)
					do_test_is(&data, tmp_sprintf("%%%s%ss", prefix, test_width_len_1[i]), tu_rand_range(-5, 5), c);
				for (int i = 0; i < num_test_width_len_2; i++)
					do_test_iis(&data, tmp_sprintf("%%%s%ss", prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), c);
			}
		}
		tu_stop_capture_fd(&data);
	TEST_END
	return (0);
}