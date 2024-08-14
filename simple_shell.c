#include "shell.h"

/**
 * print_prompt - Prints the shell prompt to the user.
 */
void print_prompt(void)
{
    printf("#cisfun$ ");
}

/**
 * parse_command - Parses the user input into a command and its arguments.
 * @input: The input string from the user.
 * @args: Array to store the parsed command and arguments.
 */
void parse_command(char *input, char **args)
{
    char *token;
    int i = 0;

    token = strtok(input, " \t\n");
    while (token != NULL && i < MAX_ARGS - 1)
    {
        args[i] = token;
        i++;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

/**
 * execute_command - Executes a given command.
 * @args: Array of arguments for the command.
 */
void execute_command(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (execve(args[0], args, environ) == -1)
        {
            perror(args[0]);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if (wait(&status) == -1)
        {
            perror("wait failed");
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * handle_commands - Handles the list of commands.
 * @command_list: Array of command strings.
 */
void handle_commands(char **command_list)
{
    int i = 0;

    while (command_list[i] != NULL)
    {
        if (strcmp(command_list[i], "exit") == 0)
        {
            exit(0);
        }
        else if (strcmp(command_list[i], "env") == 0)
        {
            print_env();
        }
        else
        {
            char *args[MAX_ARGS];
            parse_command(command_list[i], args);
            if (args[0] != NULL)
            {
                execute_command(args);
            }
        }
        i++;
    }
}

/**
 * print_env - Prints the environment variables.
 */
void print_env(void)
{
    char **env_ptr = environ;

    while (*env_ptr != NULL)
    {
        printf("%s\n", *env_ptr);
        env_ptr++;
    }
}

/**
 * main - Entry point of the shell program.
 * Return: Always returns 0.
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read_size;
    char *command_list[MAX_ARGS];

    while (1)
    {
        print_prompt();
        read_size = getline(&line, &len, stdin);
        if (read_size == -1)
        {
            if (feof(stdin))
            {
                free(line);
                exit(EXIT_SUCCESS);
            }
            else
            {
                perror("getline");
                free(line);
                exit(EXIT_FAILURE);
            }
        }

        /* Remove trailing newline character */
        if (line[read_size - 1] == '\n')
            line[read_size - 1] = '\0';

        /* Ignore empty input */
        if (line[0] == '\0')
            continue;

        command_list[0] = line;
        command_list[1] = NULL;

        handle_commands(command_list);
    }

    free(line);
    return (0);
}

