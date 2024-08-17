#ifndef MY_SHELL
#define MY_SHELL

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int run_command(char *const cmd_input[], char **envp);
int display_env(void);
char *find_env_path(const char *name, char **envp);
void tokenize_input(char cmd_input[], char **envp);

#endif /* MY_SHELL */
