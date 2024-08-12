#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * main - Simple shell example
 *
 * Return: Always 0.
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    printf("$ ");
    nread = getline(&line, &len, stdin);
    if (nread == -1)
    {
        perror("Error:");
        free(line);
        exit(EXIT_FAILURE);
    }

    printf("%s", line);
    free(line);

    return (0);
}

