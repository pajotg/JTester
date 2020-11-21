#include "test_utils_printf.h"

#define BUFF_SIZE 1024

char* test_mandatory_flags[] = { "", "0", "-", "-0", "0-" };
const int num_test_mandatory_flags = 5;

char* test_width_len[] = { "", "5", "5.0", "5.1", "5.3", "5.7", ".3", ".2", ".7" };
const int num_test_width_len = 9;

char* test_width_len_1[] = { "*", "*.0", "*.1", "*.3", "*.5", ".*", "0.*", "1.*", "3.*", "5.*" };
const int num_test_width_len_1 = 10;

char* test_width_len_2[] = { "*.*" };
const int num_test_width_len_2 = 1;

static char buff_ft[BUFF_SIZE];
static char buff_real[BUFF_SIZE];

void comp(capture_data* data, char* str, char* buff_ft, char* buff_real, int ft_out, int real_out, int read_out)
{
	if (real_out != ft_out)
	{
		tu_stop_capture_fd(data);
		tu_ko_message_exit("FT ret (%i) != real ret (%i) %s FT: \"%.*s\" RE: \"%.*s\"", ft_out, real_out, str, ft_out, buff_ft, real_out, buff_real);
	}

	if (read_out != ft_out) // This is a sanity check for my code, so it should give a warning, when the ft_out != read but ft_out == real_out then read problems?
	{
		tu_stop_capture_fd(data);
		tu_warning_message_exit("FT ret (%i) != read ret (%i) %s FT: \"%.*s\" RE: \"%.*s\"", ft_out, read_out, str, ft_out, buff_ft, real_out, buff_real);
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
}

#define CREATE_TEST1(name, type1) void do_test_##name(capture_data* data, char* str, type1 _1)\
{\
	int ft_out = ft_printf(str, _1);\
	int real_out = snprintf(buff_real, BUFF_SIZE, str, _1);\
	int read_out = read(data->read_end, buff_ft, BUFF_SIZE);\
	comp(data, str, buff_ft, buff_real, ft_out, real_out, read_out);\
}
#define CREATE_TEST2(name, type1, type2) void do_test_##name(capture_data* data, char* str, type1 _1, type2 _2)\
{\
	int ft_out = ft_printf(str, _1, _2);\
	int real_out = snprintf(buff_real, BUFF_SIZE, str, _1, _2);\
	int read_out = read(data->read_end, buff_ft, BUFF_SIZE);\
	comp(data, str, buff_ft, buff_real, ft_out, real_out, read_out);\
}
#define CREATE_TEST3(name, type1, type2, type3) void do_test_##name(capture_data* data, char* str, type1 _1, type2 _2, type3 _3)\
{\
	int ft_out = ft_printf(str, _1, _2, _3);\
	int real_out = snprintf(buff_real, BUFF_SIZE, str, _1, _2, _3);\
	int read_out = read(data->read_end, buff_ft, BUFF_SIZE);\
	comp(data, str, buff_ft, buff_real, ft_out, real_out, read_out);\
}

// Macros with parameters are so usefull, glorious! why does not norm not allouw them?
// But then again, c++ fixes the entire reason i did this, you can pas ... to other functions in c++
CREATE_TEST1(i,int)
CREATE_TEST2(ii,int,int)
CREATE_TEST3(iii,int,int,int)

CREATE_TEST1(s,char*)
CREATE_TEST2(is,int,char*)
CREATE_TEST3(iis,int,int,char*)

CREATE_TEST1(p,void*)
CREATE_TEST2(ip,int,void*)
CREATE_TEST3(iip,int,int,void*)