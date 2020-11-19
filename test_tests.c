#include "libft.h"
#include "test_utils.h"
#include <signal.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	tu_test_init(argc, argv);

	if (tu_is_test(argv[1],"0"))
		tu_ko_message_exit("this, ok, ko, no crash, good SEG, bad SEG, bad SIGKILL, wierd sig, can crash, can crash seg, can crash KO, can crash KO message, OK message, can crash OK message, should crash OK message (wat?), malloc tests, warnings, leaks detected, free(NULL)");
	if (tu_is_test(argv[1],"1"))
		tu_ok_exit();
	else if (tu_is_test(argv[1],"2"))
		tu_ko_exit();
	else if (tu_is_test(argv[1],"3"))
		tu_test_should_crash();
	else if (tu_is_test(argv[1],"4"))
	{
		tu_test_should_crash();
		raise(SIGSEGV);
	}
	else if (tu_is_test(argv[1],"5"))
		raise(SIGSEGV);
	else if (tu_is_test(argv[1],"6"))
		raise(SIGKILL);
	else if (tu_is_test(argv[1],"7"))
		raise(SIGPIPE);
	else if (tu_is_test(argv[1],"8"))
		tu_test_can_crash();
	else if (tu_is_test(argv[1],"9"))
	{
		tu_test_can_crash();
		raise(SIGSEGV);
	}
	else if (tu_is_test(argv[1],"10"))
	{
		tu_test_can_crash();
		tu_ko_exit();
	}
	else if (tu_is_test(argv[1],"11"))
	{
		tu_test_can_crash();
		tu_ko_message_exit("can crash KO");
	}
	else if (tu_is_test(argv[1],"12"))
	{
		tu_ok_message("message with OK");
	}
	else if (tu_is_test(argv[1],"13"))
	{
		tu_test_can_crash();
		tu_ok_message("message with OK can crash");
	}
	else if (tu_is_test(argv[1],"14"))
	{
		tu_test_should_crash();
		tu_ok_message("message with OK should crash.. should not be a thing");
	}
	else if (tu_is_test(argv[1],"15"))
	{
		if (tu_malloc_count() != 0 || tu_free_count() != 0)
			tu_ko_message_exit("Failed to reset malloc/free count!");
		free(malloc(25));
		if (tu_malloc_count() != 1 || tu_free_count() != 1)
			tu_ko_message_exit("Failed to count malloc/free count!");
	}
	else if (tu_is_test(argv[1],"16"))
	{
		tu_malloc_null_in(1);	// This took roughly 5 hours to get working, wow
		void* a = malloc(25);	// 0th call
		void* b = malloc(25);	// 1st call	(returns null)
		void* c = malloc(25);	// 2nd call
		if (tu_malloc_count() != 3)
			tu_ko_message_exit("Failed to count mallocs count!");
		if (a != NULL && b == NULL && c != NULL)
			tu_ok_message("Successfully controlled malloc null return");
		else
			tu_ko_message_exit("Failed to controll mallocs!");
	}
	else if (tu_is_test(argv[1],"17"))
		tu_warning();
	else if (tu_is_test(argv[1],"18"))
		tu_warning_message("Hey there, this is a warning!");
	else if (tu_is_test(argv[1],"19"))
		tu_nop_pt(malloc(25));
	else if (tu_is_test(argv[1],"20"))
	{
		void* pt = NULL;
		free(pt);
	}
	else
		tu_test_stop();
	tu_test_finish();
	return (0);
}