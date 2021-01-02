#include "test_utils_printf.h"
#include <math.h>

#define BUFF_SIZE 1024

char* test_length_field[] = { "", "l", "ll", "h", "hh"};
const int num_test_length_field = 5;

char* test_bonus_flags[] = { "", "+", " ", " +", "#", "#+", "# ", "# +"};
const int num_test_bonus_flags = 8;

char* test_mandatory_flags[] = { "", "0", "-", "-0", "0-" };
const int num_test_mandatory_flags = 5;

char* test_width_len[] = { "", "5", "5.0", "5.1", "5.3", "5.7", ".3", ".2", ".7", "0.7", "3.7", "1.13", ".06" };
const int num_test_width_len = 13;

char* test_width_len_1[] = { "*", "*.0", "*.1", "*.3", "*.5", ".*", "0.*", "1.*", "3.*", "5.*" };
const int num_test_width_len_1 = 10;

char* test_width_len_2[] = { "*.*" };
const int num_test_width_len_2 = 1;

int TestInts[] = { -1, 0, 1, 2147483647, -2147483648 };
const int num_TestInts = 5;

float TestFloats[] = { -1, 0, 1, 23012308.512352, 12308.197279, -823671.23, INFINITY, NAN, -INFINITY, -NAN, M_PI };
const int num_TestFloats = 11;

void* TestPointers[] = { NULL, &TestInts, (void*)5, (void*)1892391235 };
const int num_TestPointers = 5;

char TestChars[] = { 'A', 'a', '9', '\0', 255, -25 };
const int num_TestChars = 6;

char* TestStrings[] = { NULL, "", "Hello World!", "€", "⅐⅑⅒⅓⅔⅕⅖⅗⅘⅙⅚⅛⅜⅝⅞⅟ⅠⅡⅢⅣⅤⅥⅦⅧⅨⅩⅪⅫⅬⅭⅮⅯⅰⅱⅲⅳⅴⅵⅶⅷⅸⅹⅺⅻⅼⅽⅾⅿↀↁↂↃↄↅↆↇↈ↉↊↋🐮🦈🚲⛔🕯️➕🔺💇🧠📻🥤🍝🍥💴🌬️🥓🙍⚓👰🐂📽️🏅⛅🇦🇪🇵🇪🧜📮⛳🔽🚂🏌️🐇🏍️🎲🥛🎣👱🎏🕷️🦍🔘🐅🏇🔐🏩👺🅱️🚙🐧⚖️🎃🌄🎾🐚🎺❇️🎫⌚🌋💒👳❎👟👃🛌🚓⏬📈⛄⏱️😾🛫🤱🍐☮️🚃⏳🌜📹🐛👔👗🐌🎱🌰🌮🕵️🔅✉️🇪🇬🚑📦🤥🔄🤳💲🎋🗓️🤖🥔"};
const int num_TestStrings = 5;

// Total unique tests = (num_test_mandatory_flags*num_test_bonus_flags) * (num_test_width_len + num_test_width_len_1 + num_test_width_len_2) * (num_TestInts + num_TestPointers + num_TestChars + num_TestStrings)
// That equals.. 20160, nice! (40 * 24 * 21)
// Now multiply that by the number of conversions... and we have 181440 unique tests! (20160 * 9)

static char buff_ft[BUFF_SIZE];
static char buff_real[BUFF_SIZE];

void comp(capture_data* data, char* str, char* buff_ft, char* buff_real, int ft_out, int real_out, int read_out)
{
	if (real_out == BUFF_SIZE) // Sanity check
		tu_warning_message_exit("real_out == BUFF_SIZE, increase it!");

	if (real_out != ft_out)
	{
		tu_stop_capture_fd(data);
		tu_ko_message_exit("FT ret (%i) != real ret (%i) %s FT: \"%.*s\" RE: \"%.*s\"", ft_out, real_out, str, ft_out, buff_ft, real_out, buff_real);
	}

	if (ft_out != 0 && read_out != ft_out) // This is a sanity check for my code, so it should give a warning, when the ft_out != read but ft_out == real_out then read problems?
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

CREATE_TMP_VPRINTF(tmp_sprintf,1024)

#define CREATE_TEST1(name, print, type1) void do_test_##name(capture_data* data, char* str, type1 _1)\
{\
	int ft_out = ft_printf(str, _1);\
	int real_out = snprintf(buff_real, BUFF_SIZE, str, _1);\
	int read_out = read(data->read_end, buff_ft, BUFF_SIZE);\
	comp(data, tmp_sprintf("%s |"#print"|", str, _1), buff_ft, buff_real, ft_out, real_out, read_out);\
}
#define CREATE_TEST2(name, print, type1, type2) void do_test_##name(capture_data* data, char* str, type1 _1, type2 _2)\
{\
	int ft_out = ft_printf(str, _1, _2);\
	int real_out = snprintf(buff_real, BUFF_SIZE, str, _1, _2);\
	int read_out = read(data->read_end, buff_ft, BUFF_SIZE);\
	comp(data, tmp_sprintf("%s |"#print"|", str, _1, _2), buff_ft, buff_real, ft_out, real_out, read_out);\
}
#define CREATE_TEST3(name, print, type1, type2, type3) void do_test_##name(capture_data* data, char* str, type1 _1, type2 _2, type3 _3)\
{\
	int ft_out = ft_printf(str, _1, _2, _3);\
	int real_out = snprintf(buff_real, BUFF_SIZE, str, _1, _2, _3);\
	int read_out = read(data->read_end, buff_ft, BUFF_SIZE);\
	comp(data, tmp_sprintf("%s |"#print"|", str, _1, _2, _3), buff_ft, buff_real, ft_out, real_out, read_out);\
}

// Macros with parameters are so usefull, glorious! why does not norm not allouw them?
// But then again, c++ fixes the entire reason i did this, you can pas ... to other functions in c++
CREATE_TEST1(i,%i,int)
CREATE_TEST2(ii,%i %i,int,int)
CREATE_TEST3(iii,%i %i %i,int,int,int)

CREATE_TEST1(s,%s,char*)
CREATE_TEST2(is,%i %s,int,char*)
CREATE_TEST3(iis,%i %i %s,int,int,char*)

CREATE_TEST1(p,%p,void*)
CREATE_TEST2(ip,%i %p,int,void*)
CREATE_TEST3(iip,%i %i %p,int,int,void*)

CREATE_TEST1(f,%f,float)
CREATE_TEST2(if,%i %f,int,float)
CREATE_TEST3(iif,%i %i %f,int,int,float)
