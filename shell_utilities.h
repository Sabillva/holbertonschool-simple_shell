#ifndef SHELL_UTILITIES_H
#define SHELL_UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

#define MAX_LENGTH 100
#define SHELL_PROMPT ">> "
#define ENV_PATH "PATH="
extern char **environ;

void execute_cmd(char **args, char *path);
void split_command(char *input_command, char **args);
void resolve_path(char **args, char **path, char **env_path, int *found);
void execute_input_cmd(char *input_command);
void initialize_shell_env(char **env_path, char **path);
void parse_command_input(char *commands, char **commands_list);
void process_cmd_list(char **commands_list);
void display_shell_env(void);

#endif /* SHELL_UTILITIES_H */

