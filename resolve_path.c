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
        *found = 0;
        return;
    }

    path_token = strtok(*env_path, ":");
    while (path_token != NULL)
    {
        strcpy(*path, path_token);
        strcat(*path, "/");
        strcat(*path, args[0]);
        if (access(*path, X_OK) == 0)  /* Check if command is executable */
        {
            *found = 1;
            return;
        }
        path_token = strtok(NULL, ":");
    }

    *found = 0;  /* Command not found in PATH */
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

    if (strchr(args[0], '/') != NULL)  /* Check if command is a path (e.g., "./hbtn_ls") */
    {
        if (access(args[0], X_OK) == -1)
        {
            fprintf(stderr, "%s: 1: %s: not found\n", shell_name, args[0]);
            free(path);
            free(env_path);
            return;
        }
        free(path);
        free(env_path);
        path = strdup(args[0]);
        found = 1;
    }
    else
    {
        resolve_path(args, &path, &env_path, &found);
    }

    if (found == 0)  /* Command not found, do not fork */
    {
        fprintf(stderr, "%s: 1: %s: not found\n", shell_name, args[0]);
        free(path);
        return;
    }

    /* Only fork when we have a valid command to execute */
    execute_cmd(args, path, shell_name);
    free(path);
}

