#ifndef SHELL_H
#define SHELL_H

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<stddef.h>
#include<string.h>
#include <sys/wait.h>

extern char **environ;

/* built function*/
void debut_shell(void);
void non_interactive_mode(char *token, int *status);
ssize_t read_command(char **line, size_t *size_line);

/* execute command*/
void execute_command_non_interactive(char *command, char **argv, int *status);
void _execvep(char **commands, char **envp, int *status);
void search_path(char **commands, char **envp, int *status);
void wait_child_process(int *status);
char *mygetenv(const char *path);

/* handle line and delimiters(/n...)*/
char **tokenize_string(char *str, char *delimiters);

/* write messages */
void write_error(char *command);
void print_env_var(void);

/* string fucntion*/
char *_strdup(const char *src);
int _strlen(char *str);
int _strcmp(char *s1, char *s2);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);


/* free memory leak*/
void free_array(char **array);

#endif
