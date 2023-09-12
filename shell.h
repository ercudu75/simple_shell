#ifndef SHELL_H
#define SHELL_H

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stddef.h>
#include<string.h>
#include <sys/wait.h>

void debut_shell(void);
ssize_t read_command(char **line, size_t *size_line);
int execute_command(char *token, char **envp);
int non_interactive_mode(char *token);
ssize_t read_command(char **line, size_t *size_line);
char **tokenize_string(char *str, char *delimiters);

#endif
