#include "shell.h"

/**
 * print_prompt - Prints the shell prompt
 */
void print_prompt(void)
{
    printf("#cisfun$ ");
}

/**
 * print_env - Prints the environment variables
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
 * parse_command - Parses the user input into a command and its arguments
 * @input: The input string from the user
 * @args: Array to store the parsed command and arguments
 */
void parse_command(char *input, char **args)
{
    char *token = strtok(input, " \t\n");
    int i = 0;

    while (token != NULL && i < MAX_ARGS - 1)
    {
        args[i] = token;
        i++;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

/**
 * execute_command - Executes a given command
 * @args: Array of arguments for the command
 */
void execute_command(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (execve(args[0], args, environ) == -1)
        {
            fprintf(stderr, "./simple_shell: %s: command not found\n", args[0]);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("Wait failed");
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * handle_commands - Handles the list of commands
 * @command_list: Array of command strings
 */
void handle_commands(char **command_list)
{
    int i = 0;

    while (command_list[i] != NULL)
    {
        if (strcmp(command_list[i], "exit") == 0)
        {
            exit(EXIT_SUCCESS);
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
 * main - Entry point of the shell program
 * Return: Always 0
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    char *command_list[MAX_ARGS]; /* Moved declaration to the top */

    while (1)
    {
        print_prompt();  /* Prompt should be printed here */
        if (getline(&line, &len, stdin) == -1)
        {
            if (feof(stdin))  /* Remove feof() since it's not allowed */
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
        command_list[0] = line; /* Single command per line */
        command_list[1] = NULL;

        handle_commands(command_list);
        /* Ensure the prompt is not printed again after executing the command */
    }

    free(line);
    return 0;
}

