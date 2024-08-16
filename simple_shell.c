#include "shell.h"

/**
 * print_prompt - Prints the shell prompt to the user.
 */
void print_prompt(void)
{
    printf("#cisfun$ ");
    fflush(stdout);  /* Ensure the prompt is printed immediately */
}

/**
 * trim_whitespace - Removes leading and trailing whitespace from a string.
 * @str: The string to trim.
 * Return: Pointer to the trimmed string.
 */
char *trim_whitespace(char *str)
{
    char *end;

    /* Trim leading space manually */
    while (*str == ' ' || *str == '\t' || *str == '\n')
        str++;

    if (*str == '\0')  /* All spaces? */
        return str;

    /* Trim trailing space manually */
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
        end--;

    /* Write new null terminator */
    *(end + 1) = '\0';

    return str;
}

/**
 * run_shell - Core function to run the simple shell loop.
 */
void run_shell(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read_size;
    pid_t pid;
    int status;

    while (1)
    {
        print_prompt();

        read_size = getline(&line, &len, stdin);
        if (read_size == -1)
        {
            free(line);
            exit(EXIT_SUCCESS);  /* Exit gracefully on EOF (Ctrl+D) */
        }

        /* Trim whitespace and handle empty input */
        line = trim_whitespace(line);

        /* Ignore empty input */
        if (line[0] == '\0')
            continue;

        /* Fork a child process */
        pid = fork();
        if (pid == -1)
        {
            perror("fork failed");
            free(line);
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            /* Child process: execute the command */
            char *args[2];

            args[0] = line;  /* Command only, no arguments */
            args[1] = NULL;

            if (execve(args[0], args, environ) == -1)
            {
                fprintf(stderr, "./shell: %s: No such file or directory\n", args[0]);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* Parent process: wait for the child to finish */
            if (wait(&status) == -1)
            {
                perror("wait failed");
                free(line);
                exit(EXIT_FAILURE);
            }
        }
    }

    free(line);
}

/**
 * main - Entry point of the shell program.
 * Return: Always returns 0.
 */
int main(void)
{
    run_shell();
    return (0);
}

