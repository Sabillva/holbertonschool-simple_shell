#include "shell_utilities.h"

/**
 * resolve_path - Handles path lookup for the command
 * @args: command arguments
 * @path: path to command
 * @env_path: environment PATH
 * @found: flag for whether the path was found
 */
void resolve_path(char **args, char **path, char **env_path, int *found)
{
    char *path_token = NULL;

    if (*env_path == NULL)
    {
        fprintf(stderr, "%s: 1: %s: not found\n", args[0], args[0]);
        free(*env_path);
        free(*path);
        exit(127);
    }
    path_token = strtok(*env_path, ":");

    while (path_token != NULL)
    {
        strcpy(*path, path_token);
        strcat(*path, "/");
        strcat(*path, args[0]);
        if (access(*path, X_OK) != -1)
        {
            *found = 1;
            break;
        }
        path_token = strtok(NULL, ":");
    }
    free(*env_path);
}

/**
 * execute_input_cmd - Execute command based on input
 * @input_command: user input command
 * @shell_name: name of the shell program
 */
void execute_input_cmd(char *input_command, char *shell_name)
{
    char *args[MAX_LENGTH], *path = NULL, *env_path = NULL;
    int found = 0;

    initialize_shell_env(&env_path, &path);
    split_command(input_command, args);

    if (args[0] == NULL)
    {
        free(env_path);
        free(path);
        return;
    }

    if (strchr(args[0], '/') != NULL)
    {
        if (access(args[0], X_OK) == -1)
        {
            fprintf(stderr, "%s: 1: %s: not found\n", shell_name, args[0]);
            free(path);
            free(env_path);
            exit(127);
        }
        free(path);
        free(env_path);
        path = strdup(args[0]);
        found = 1;
    }
    else
        resolve_path(args, &path, &env_path, &found);

    if (found == 0)
    {
        fprintf(stderr, "%s: 1: %s: not found\n", shell_name, args[0]);
        free(path);
        exit(127);
    }

    execute_cmd(args, path, shell_name);
    free(path);
}

