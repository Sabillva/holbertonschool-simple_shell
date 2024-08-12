#include <stdio.h>
#include <unistd.h>

int main(void)
{
	pid_t my_pid = getpid();
	printf("PID: %u\n", my_pid);
	return (0);
}
