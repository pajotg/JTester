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
		for (int i = 0; i < num_test_bonus_flags; i++)
		{
			char* bonus_flag = test_bonus_flags[i];
			if (bonus_flag[0] == '\0')
				continue;
			for (int mandatory_flag_id = 0; mandatory_flag_id < num_test_mandatory_flags; mandatory_flag_id++)
			{
				char* mandatory_flag = test_mandatory_flags[mandatory_flag_id];

				for (int i = 0; i < num_test_width_len; i++)
					do_test(&data, tmp_sprintf("%%%s%s%s%%", bonus_flag, mandatory_flag, test_width_len[i]));
				for (int i = 0; i < num_test_width_len_1; i++)
					do_test_i(&data, tmp_sprintf("%%%s%s%s%%", bonus_flag, mandatory_flag, test_width_len_1[i]), tu_rand_range(-5, 5));
				for (int i = 0; i < num_test_width_len_2; i++)
					do_test_ii(&data, tmp_sprintf("%%%s%s%s%%", bonus_flag, mandatory_flag, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5));
			}
		}
		tu_malloc_disable();
		tu_stop_capture_fd(&data);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test_i(&data, "%c", 'A');
		tu_malloc_enable();
		for (int i = 0; i < num_TestChars; i++)
		{
			char c = TestChars[i];
			for (int i = 0; i < num_test_bonus_flags; i++)
			{
				char* bonus_flag = test_bonus_flags[i];
				if (bonus_flag[0] == '\0')
					continue;
				for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
				{
					char* prefix = test_mandatory_flags[prefix_id];

					for (int i = 0; i < num_test_width_len; i++)
						do_test_i(&data, tmp_sprintf("%%%s%s%sc", bonus_flag, prefix, test_width_len[i]), c);
					for (int i = 0; i < num_test_width_len_1; i++)
						do_test_ii(&data, tmp_sprintf("%%%s%s%sc", bonus_flag, prefix, test_width_len_1[i]), tu_rand_range(-5, 5), c);
					for (int i = 0; i < num_test_width_len_2; i++)
						do_test_iii(&data, tmp_sprintf("%%%s%s%sc", bonus_flag, prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), c);
				}
			}
		}
		tu_malloc_disable();
		tu_stop_capture_fd(&data);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test_i(&data, "%i", 5);
		tu_malloc_enable();
		for (int i = 0; i < num_TestInts; i++)
		{
			int c = TestInts[i];
			for (int i = 0; i < num_test_bonus_flags; i++)
			{
				char* bonus_flag = test_bonus_flags[i];
				if (bonus_flag[0] == '\0')
					continue;
				for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
				{
					char* prefix = test_mandatory_flags[prefix_id];

					for (int i = 0; i < num_test_width_len; i++)
						do_test_i(&data, tmp_sprintf("%%%s%s%si", bonus_flag, prefix, test_width_len[i]), c);
					for (int i = 0; i < num_test_width_len_1; i++)
						do_test_ii(&data, tmp_sprintf("%%%s%s%si", bonus_flag, prefix, test_width_len_1[i]), tu_rand_range(-5, 5), c);
					for (int i = 0; i < num_test_width_len_2; i++)
						do_test_iii(&data, tmp_sprintf("%%%s%s%si", bonus_flag, prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), c);
				}
			}
		}
		tu_malloc_disable();
		tu_stop_capture_fd(&data);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test_p(&data, "%p", NULL);
		tu_malloc_enable();
		for (int i = 0; i < num_TestPointers; i++)
		{
			void* c = TestPointers[i];
			for (int i = 0; i < num_test_bonus_flags; i++)
			{
				char* bonus_flag = test_bonus_flags[i];
				if (bonus_flag[0] == '\0')
					continue;
				for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
				{
					char* prefix = test_mandatory_flags[prefix_id];
					for (int i = 0; i < num_test_width_len; i++)
						do_test_p(&data, tmp_sprintf("%%%s%s%sp", bonus_flag, prefix, test_width_len[i]), c);
					for (int i = 0; i < num_test_width_len_1; i++)
						do_test_ip(&data, tmp_sprintf("%%%s%s%sp", bonus_flag, prefix, test_width_len_1[i]), tu_rand_range(-5, 5), c);
					for (int i = 0; i < num_test_width_len_2; i++)
						do_test_iip(&data, tmp_sprintf("%%%s%s%sp", bonus_flag, prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), c);
				}
			}
		}
		tu_malloc_disable();
		tu_stop_capture_fd(&data);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test_p(&data, "%d", NULL);
		tu_malloc_enable();
		for (int i = 0; i < num_TestInts; i++)
		{
			int c = TestInts[i];
			for (int i = 0; i < num_test_bonus_flags; i++)
			{
				char* bonus_flag = test_bonus_flags[i];
				if (bonus_flag[0] == '\0')
					continue;
				for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
				{
					char* prefix = test_mandatory_flags[prefix_id];
					for (int i = 0; i < num_test_width_len; i++)
						do_test_i(&data, tmp_sprintf("%%%s%s%sd", bonus_flag, prefix, test_width_len[i]), c);
					for (int i = 0; i < num_test_width_len_1; i++)
						do_test_ii(&data, tmp_sprintf("%%%s%s%sd", bonus_flag, prefix, test_width_len_1[i]), tu_rand_range(-5, 5), c);
					for (int i = 0; i < num_test_width_len_2; i++)
						do_test_iii(&data, tmp_sprintf("%%%s%s%sd", bonus_flag, prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), c);
				}
			}
		}
		tu_malloc_disable();
		tu_stop_capture_fd(&data);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test_p(&data, "%x", NULL);
		tu_malloc_enable();
		for (int i = 0; i < num_TestInts; i++)
		{
			int c = TestInts[i];
			for (int i = 0; i < num_test_bonus_flags; i++)
			{
				char* bonus_flag = test_bonus_flags[i];
				if (bonus_flag[0] == '\0')
					continue;
				for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
				{
					char* prefix = test_mandatory_flags[prefix_id];
					for (int i = 0; i < num_test_width_len; i++)
						do_test_i(&data, tmp_sprintf("%%%s%s%sx", bonus_flag, prefix, test_width_len[i]), c);
					for (int i = 0; i < num_test_width_len_1; i++)
						do_test_ii(&data, tmp_sprintf("%%%s%s%sx", bonus_flag, prefix, test_width_len_1[i]), tu_rand_range(-5, 5), c);
					for (int i = 0; i < num_test_width_len_2; i++)
						do_test_iii(&data, tmp_sprintf("%%%s%s%sx", bonus_flag, prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), c);
				}
			}
		}
		tu_malloc_disable();
		tu_stop_capture_fd(&data);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test_p(&data, "%X", NULL);
		tu_malloc_enable();
		for (int i = 0; i < num_TestInts; i++)
		{
			int c = TestInts[i];
			for (int i = 0; i < num_test_bonus_flags; i++)
			{
				char* bonus_flag = test_bonus_flags[i];
				if (bonus_flag[0] == '\0')
					continue;
				for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
				{
					char* prefix = test_mandatory_flags[prefix_id];
					for (int i = 0; i < num_test_width_len; i++)
						do_test_i(&data, tmp_sprintf("%%%s%s%sX", bonus_flag, prefix, test_width_len[i]), c);
					for (int i = 0; i < num_test_width_len_1; i++)
						do_test_ii(&data, tmp_sprintf("%%%s%s%sX", bonus_flag, prefix, test_width_len_1[i]), tu_rand_range(-5, 5), c);
					for (int i = 0; i < num_test_width_len_2; i++)
						do_test_iii(&data, tmp_sprintf("%%%s%s%sX", bonus_flag, prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), c);
				}
			}
		}
		tu_malloc_disable();
		tu_stop_capture_fd(&data);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test_p(&data, "%u", NULL);
		tu_malloc_enable();
		for (int i = 0; i < num_TestInts; i++)
		{
			int c = TestInts[i];
			for (int i = 0; i < num_test_bonus_flags; i++)
			{
				char* bonus_flag = test_bonus_flags[i];
				if (bonus_flag[0] == '\0')
					continue;
				for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
				{
					char* prefix = test_mandatory_flags[prefix_id];
					for (int i = 0; i < num_test_width_len; i++)
						do_test_i(&data, tmp_sprintf("%%%s%s%su", bonus_flag, prefix, test_width_len[i]), c);
					for (int i = 0; i < num_test_width_len_1; i++)
						do_test_ii(&data, tmp_sprintf("%%%s%s%su", bonus_flag, prefix, test_width_len_1[i]), tu_rand_range(-5, 5), c);
					for (int i = 0; i < num_test_width_len_2; i++)
						do_test_iii(&data, tmp_sprintf("%%%s%s%su", bonus_flag, prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), c);
				}
			}
		}
		tu_malloc_disable();
		tu_stop_capture_fd(&data);
	TEST
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test_p(&data, "%s", NULL);
		tu_malloc_enable();
		for (int i = 0; i < num_TestStrings; i++)
		{
			char* c = TestStrings[i];
			for (int i = 0; i < num_test_bonus_flags; i++)
			{
				char* bonus_flag = test_bonus_flags[i];
				if (bonus_flag[0] == '\0')
						continue;
				for (int prefix_id = 0; prefix_id < num_test_mandatory_flags; prefix_id++)
				{
					char* prefix = test_mandatory_flags[prefix_id];
					for (int i = 0; i < num_test_width_len; i++)
						do_test_s(&data, tmp_sprintf("%%%s%s%ss", bonus_flag, prefix, test_width_len[i]), c);
					for (int i = 0; i < num_test_width_len_1; i++)
						do_test_is(&data, tmp_sprintf("%%%s%s%ss", bonus_flag, prefix, test_width_len_1[i]), tu_rand_range(-5, 5), c);
					for (int i = 0; i < num_test_width_len_2; i++)
						do_test_iis(&data, tmp_sprintf("%%%s%s%ss", bonus_flag, prefix, test_width_len_2[i]), tu_rand_range(-5, 5), tu_rand_range(-5, 5), c);
				}
			}
		}
		tu_malloc_disable();
		tu_stop_capture_fd(&data);
	TEST_END
	return (0);
}