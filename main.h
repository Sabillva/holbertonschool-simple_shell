#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Function Prototypes */
char *read_line(void);
char **split_line(char *line);
int execute(char **args);

#endif /* MAIN_H */

