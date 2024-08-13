#include "shell.h"
/**
 * execute_command - Executes a given command
 * @args: Array of arguments for the command
 * @full_path: Full path of the command
 */
void execute_command(char **args, char *full_path)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork Failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(full_path, args, environ) == -1)
		{
			free(full_path);
			fprintf(stderr, "./simple_shell: %s: command not found\n", args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			free(full_path);
			perror("Wait failed");
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * parse_command - Parses the user input into a command and its arguments
 * @input: The input string from the user
 * @args: Array to store the parsed command and arguments
 */
void parse_command(char *input, char **args)
{
	char *token = strtok(input, "\t");
	int i = 0;

	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;
}

/**
 * process_input - Processes the raw input from the user
 * @input: Raw input string containing commands
 * @command_list: Array to store each individual command
 */
void process_input(char *input, char **command_list)
{
	char *command;
	int i = 0;

	command = strtok(input, "\n");
	while (command != NULL)
	{
		command_list[i] = command;
		command = strtok(NULL, "\n");
		i++;
	}
	command_list[i] = NULL;
}

/**
 * handle_commands - Handles the list of commands
 * @command_list: Array of command strings
 */

void handle_commands(char **command_list)
{
	int i = 0;
	char *command;

	while (command_list[i] != NULL)
	{
		command = command_list[i];
		if (strcmp(command, "exit") == 0)
		{
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(command, "env") == 0)
		{
			print_env();
		}
		else
		{
			execute_command(command(command_list[i]);
		}
		i++;
	}
}
