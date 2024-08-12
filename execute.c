#include "main.h"
/**
 * execute - Executes a command by forking a child process
 * @args: Null-terminated array of arguments (the command to execute)
 *
 * Return: 1 if the shell should continue running, 0 if it should terminate
 */
int execute(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("hsh");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("hsh");
	}
	else
	{
	do
	{
	waitpid(pid, &status, WUNTRACED);
	}while
	{
	(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	}
	return (1);
}
