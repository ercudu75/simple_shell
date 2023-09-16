#ifndef SHELL_H
#define SHELL_H

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stddef.h>
#include<string.h>
#include <sys/wait.h>

/* built function*/
void debut_shell(void);
void non_interactive_mode(char *token, int *status);
ssize_t read_command(char **line, size_t *size_line);

/* execute command*/
int execute_command(char *command, char **envp, char **argv);
void execute_command_non_interactive(char *command, char **argv,int *status);
/* handle line and delimiters(/n...)*/
char **tokenize_string(char *str, char *delimiters);

/* write messages */
void write_error(char *command);

/* string fucntion*/
char *_strdup(const char *src);
int _strlen(char *str);
int _strcmp(char *s1, char *s2);

/* free memory leak*/
void free_array(char **array);

#endif
