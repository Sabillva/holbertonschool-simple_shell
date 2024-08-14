#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_ARGS 1024
extern char **environ;

void print_prompt(void);
void parse_command(char *input, char **args);
void execute_command(char **args);
void handle_commands(char **command_list);
void print_env(void);

#endif /* SHELL_H */

