#include "test_utils_printf.h"

#define BUFF_SIZE 1024

static char buff_ft[BUFF_SIZE];
static char buff_real[BUFF_SIZE];

void comp(capture_data* data, char* str, char* buff_ft, char* buff_real, int ft_out, int real_out, int read_out)
{
	if (read_out != ft_out) // This is a sanity check for my code, so it should give a warning
	{
		tu_stop_capture_fd(data);
		tu_warning_message_exit("FT output (%i) != read output (%i) %s FT: \"%.*s\" RE: \"%.*s\"", ft_out, read_out, str, ft_out, buff_ft, real_out, buff_real);
	}

	if (real_out != ft_out)
	{
		tu_stop_capture_fd(data);
		tu_ko_message_exit("FT output (%i) != real output (%i) %s FT: \"%.*s\" RE: \"%.*s\"", ft_out, real_out, str, ft_out, buff_ft, real_out, buff_real);
	}
	if (memcmp(buff_ft, buff_real, ft_out))
	{
		tu_stop_capture_fd(data);
		tu_ko_message_exit("FT output != read output %s FT: \"%.*s\" RE: \"%.*s\"", str, ft_out, buff_ft, real_out, buff_real);
	}
}

void do_test(capture_data* data, char* str)
{
	int ft_out = ft_printf(str);
	int real_out = snprintf(buff_real, BUFF_SIZE, str, NULL);	// y u complain when i dont have this null?
	int read_out = read(data->read_end, buff_ft, BUFF_SIZE);

	comp(data, str, buff_ft, buff_real, ft_out, real_out, read_out);
	tu_nop_int(read_out);
}

void do_test_i(capture_data* data, char* str, int _1)
{
	int ft_out = ft_printf(str, _1);
	int real_out = snprintf(buff_real, BUFF_SIZE, str, _1);
	int read_out = read(data->read_end, buff_ft, BUFF_SIZE);

	comp(data, str, buff_ft, buff_real, ft_out, real_out, read_out);
	tu_nop_int(read_out);
}
void do_test_ii(capture_data* data, char* str, int _1, int _2)
{
	int ft_out = ft_printf(str, _1, _2);
	int real_out = snprintf(buff_real, BUFF_SIZE, str, _1, _2);
	int read_out = read(data->read_end, buff_ft, BUFF_SIZE);

	comp(data, str, buff_ft, buff_real, ft_out, real_out, read_out);
	tu_nop_int(read_out);
}
