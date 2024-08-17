#include "myshell.h"
/*char **env_vars, *cmd_input;*/

/**
 * display_env - prints the environment variables
 * Return: zero
 */
int display_env(void)
{
	int i = 0;

	if (env_vars == NULL)
	{
		return (-1);
	}
	while (env_vars[i])
	{
		printf("%s\n", env_vars[i++]);
	}
	return (0);
}
/**
 * tokenize_input - tokenizes the input command
 * @cmd_input: command from the user
 * @envp: environment path
 */
void tokenize_input(char cmd_input[], char **envp)
{
	char *args[11];
	char *token = strtok(cmd_input, " ");
	int arg_count = 0;

	while (token != NULL && arg_count < 10)
	{
		args[arg_count++] = token;
		token = strtok(NULL, " ");
	}
	if (arg_count > 11)
	{
		perror("Error: Too many arguments");
		return;
	}
	args[arg_count] = NULL;
	if (arg_count > 0)
	{
		if (envp != NULL)
		{
			run_command(args,envp);
		}
		else
		{
			fprintf(stderr, "./myshell: 1: %s: not found\n",args[0]);
			exit(127);
		}
	}
}
/**
 * get_user_input - prompts user for input and processes it
 * @cmd_input: pointer to the command
 * @size: size of the command
 */
void get_user_input(char **cmd_input, size_t *size)
{
	size_t read_bytes;

	read_bytes = getline(cmd_input, size, stdin);
	if ((int) read_bytes == EOF)
	{
		if (isatty(STDIN_FILENO) != 0)
			printf("\n");
		if (*cmd_input != NULL)
			free(*cmd_input);
		exit(EXIT_SUCCESS);
	}
	if ((*cmd_input) [read_bytes - 1] == '\n')
		(*cmd_input) [read_bytes - 1] = '\0';
}
/**
 * main - Main function for the shell (interactive or non-interactive)
 * @argc: argument count
 * @argv: argument vector
 * @envp: environmental variable
 * Return: 1 if command fails
 */
int main(int argc, char *argv[], char **envp)
{
	size_t size;

	env_vars = envp;
	cmd_input = NULL;
	(void) argv;
	if (argc > 1)
	{
		printf("./myshell: command doesn't exist\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		size = 0;
		if (isnatty(STDIN_FILENO))
			printf("myshell($) ");
		get_user_input(&cmd_input, size);
		if (strcmp(cmd_input, "exit") == 0)
		{
			free(cmd_input);
			exit(EXIT_SUCCESS);
		}
		if (strcmp(cmd_input, "env") == 0)
		{
			display_env();
			free(cmd_imput);
			exit(EXIT_SUCCESS);
		}
		if (find_env_path("PATH", envp) == NULL)
		{
			if (cmd_input[0] != '/')
			{
				fprintf(stderr, "./myshell: 1: %s: not found\n", cmd_input);
				free(cmd_input);
				exit(127);
			}
		}
		tokenize_input(cmd_input, envp);
		free(cmd_input);
	}
	return (0);
}
