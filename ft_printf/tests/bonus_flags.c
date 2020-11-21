#include "test_utils_printf.h"

static char* test_bonus_flags[] = { "", "+", " ", " +", "#", "#+", "# ", "# +"};
static const int num_test_bonus_flags = 8;

CREATE_TMP_VPRINTF(tmp_sprintf,1024)

int main(int argc, char *argv[])
{
	TEST_START
		capture_data data;
		tu_start_capture_fd(STDOUT_FILENO, &data);
		do_test(&data, "%%");
		tu_malloc_reset();	// Static variables...
		for (int i = 0; i < num_test_bonus_flags; i++)
		{
			char* bonus_flag = test_bonus_flags[i];
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
		tu_stop_capture_fd(&data);
	TEST_END
	return (0);
}