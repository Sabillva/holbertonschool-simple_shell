#include "shell_utilities.h"

/**
 * execute_cmd - Function to execute command
 * @args: command arguments
 * @path: path to executable
 */
void execute_cmd(char **args, char *path)
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
        if (execve(path, args, environ) == -1)
        {
            free(path);
            fprintf(stderr, "./my_shell: 1: %s: not found\n", args[0]);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if (wait(&status) == -1)
        {
            free(path);
            perror("Wait failed");
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * split_command - Function to parse command
 * @input_command: command input to be parsed
 * @args: parsed arguments
 */
void split_command(char *input_command, char **args)
{
    char *command = strtok(input_command, " \t");
    int i = 0;

    args[0] = NULL;
    while (command != NULL && i < MAX_LENGTH - 1)
    {
        args[i] = command;
        i++;
        command = strtok(NULL, " \t");
    }
    args[i] = NULL;
}

/**
 * parse_command_input - Parse input command string
 * @commands: input commands string
 * @commands_list: array to hold processed commands
 */
void parse_command_input(char *commands, char **commands_list)
{
    char *command;
    int a = 0;

    command = strtok(commands, "\n");
    while (command != NULL)
    {
        commands_list[a] = command;
        command = strtok(NULL, "\n");
        a++;
    }
    commands_list[a] = NULL;
}

/**
 * process_cmd_list - Process array of commands
 * @commands_list: list of commands to process
 */
void process_cmd_list(char **commands_list)
{
    int a = 0;
    char *command;

    if (strcmp(commands_list[a], "exit") == 0)
        exit(0);
    else if (strcmp(commands_list[a], "env") == 0)
        display_shell_env();
    else
        while (commands_list[a] != NULL)
        {
            command = commands_list[a];
            if (strcmp(command, "exit") == 0 && a > 0)
                exit(2);
            execute_input_cmd(command);
            a++;
        }
}

/**
 * main - Entry point for the shell
 * Return: Always 0
 */
int main(void)
{
    char commands[MAX_LENGTH];
    char *commands_list[MAX_LENGTH];
    ssize_t read_size;

    while (1)
    {
        read_size = read(STDIN_FILENO, commands, MAX_LENGTH);
        if (read_size == -1)
        {
            perror("Error reading command");
            exit(EXIT_FAILURE);
        }
        else if (read_size == 0)
            break;
        commands[read_size] = '\0';

        parse_command_input(commands, commands_list);
        process_cmd_list(commands_list);
    }
    return (0);
}

