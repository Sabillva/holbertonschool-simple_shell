#include "myshell.h"

/* Declare the global variable for full path */
char *cmd_fullpath;

/**
 * display_error - displays error for command not found
 * @cmd_input: command inserted
 */

void display_error(char *const cmd_input[])
{
    fprintf(stderr, "./myshell: 1: %s: not found\n", cmd_input[0]);
    free(*cmd_input);
    exit(127);
}

/**
 * find_env_path - get environment variable by name
 * @name: name of environment variable
 * @envp: pointer to environment variables
 * Return: pointer to environment variable
 */

char *find_env_path(const char *name, char **envp)
{
    char **env, *separator;

    for (env = envp; *env != NULL; env++)
    {
        separator = strchr(*env, '=');
        if (separator != NULL)
        {
            if (strncmp(*env, name, separator - *env) == 0)
            {
                return (separator + 1);
            }
        }
    }
    return (NULL);
}

/**
 * resolve_path - resolves the correct path for a given command
 * @cmd: given input to check for path
 * @cmd_input: argument array
 * @envp: pointer to environment variables
 * Return: pointer to the resolved command path or NULL if failed
 */

char **resolve_path(char *cmd, char **cmd_input, char **envp)
{
    char *current_path, *temp_path;
    char *path_tok;
    size_t cmd_len = strlen(cmd);

    cmd_fullpath = NULL;

    if (strchr(cmd, '/') != NULL && access(cmd, F_OK) == 0)
    {
        cmd_input[0] = cmd;
        return (cmd_input);
    }

    path_tok = NULL;
    current_path = find_env_path("PATH", envp);
    temp_path = strdup(current_path);
    path_tok = strtok(temp_path, ":");

    while (path_tok)
    {
        cmd_fullpath = malloc(cmd_len + strlen(path_tok) + 2);
        sprintf(cmd_fullpath, "%s/%s", path_tok, cmd);
        if (access(cmd_fullpath, F_OK) == 0)
        {
            cmd_input[0] = cmd_fullpath;
            free(temp_path);
            return (cmd_input);
        }
        path_tok = strtok(NULL, ":");
        free(cmd_fullpath);
    }
    free(temp_path);
    return (NULL);
}

/**
 * run_command - function to execute commands
 * @cmd_input: input from user
 * @envp: environment path
 * Return: -1 if failed and 0 if success
 */

int run_command(char *const cmd_input[], char **envp)
{
    pid_t pid;
    int status, i;
    char **resolved_cmd = resolve_path(cmd_input[0], (char **) cmd_input, envp);

    if (resolved_cmd != NULL)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork failed");
            return (-1);
        } else if (pid == 0)
        {
            if (find_env_path("PATH", envp) == NULL && access(cmd_input[0], F_OK) != 0)
                display_error(cmd_input);
            execve(resolved_cmd[0], cmd_input, envp);
            for (i = 0; cmd_input[i] != NULL; i++)
                free(cmd_input[i]);
            exit(EXIT_FAILURE);
        }
        wait(&status);
        free(cmd_fullpath);
    } else
        display_error(cmd_input);
    if (errno == -1)
    {
        free(*cmd_input);
        exit(2);
    }
    return (0);
}

