#include "test_utils.h"

#include <stdio.h>

void tu_start_capture_fd(int fd, capture_data* ref)
{
	ref->fd = fd;
	ref->restore = dup(fd);

	int pipefd[2];
	pipe(pipefd);	// pipe2(pipefd, 0); // O_NONBLOCK);
	ref->read_end = pipefd[0];
	ref->write_end = pipefd[1];

	fcntl(ref->read_end, F_SETFL, O_NONBLOCK);
	fcntl(ref->write_end, F_SETFL, O_NONBLOCK);

	// What used to be fd will now go to the pipe
	dup2(ref->write_end, fd);
}

int tu_stop_capture_fd(capture_data* ref)
{
	fflush(NULL);	// how to get a FILE* from a fd? dunno, so just flush em all.
	close(ref->write_end);
	dup2(ref->restore, ref->fd);
	return (ref->read_end);
}