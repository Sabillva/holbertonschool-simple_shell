#include "shell_utilities.h"

/**
 * display_shell_env - Print environment variables
 */
void display_shell_env(void)
{
    char **env_ptr = environ;

    while (*env_ptr != NULL)
    {
        printf("%s\n", *env_ptr);
        env_ptr++;
    }
}

/**
 * initialize_shell_env - Initialize environment and paths
 * @env_path: pointer to environment PATH
 * @path: pointer to path buffer
 */
void initialize_shell_env(char **env_path, char **path)
{
    int i;

    *path = malloc(MAX_LENGTH);
    if (!*path)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    memset(*path, 0, MAX_LENGTH);

    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], ENV_PATH, 5) == 0)
        {
            *env_path = strdup(environ[i] + 5);
            break;
        }
    }
}

