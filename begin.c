#include "shell.h"

size_t _strlen(char *str)
{
	char *ptr = str;

	while (*ptr != '\0')
	{
		ptr++;
	}
	return (ptr - str);
}

void debut_shell(void)
{
	char *line = NULL;
	char *token = NULL;
	char *argv[2];
	char *envp[] = {NULL};
	size_t size_line = 0;
	ssize_t nread;

	while (1)
	{
		nread = read_command(&line, &size_line);
		if (nread == -1)
		{
			perror("getline");
			free(line);
			exit(EXIT_FAILURE);
		}
		token = strtok(line, "\n");
		if (token && !strcmp(token, "exit"))
		{
			free(line);
			break;
		}
		execute_command(token, argv, envp);
	}
}

int execute_command(char *token, char **argv, char **envp)
{
	int pid, status = 0;

	pid = fork();
	if (pid == 0)
	{
		argv[0] = token;
		argv[1] = NULL;
		if (execve(token, argv, envp) == -1)
		{
			write(STDOUT_FILENO, "Command not found\n", 18);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
	return (status);
}

ssize_t read_command(char **line, size_t *size_line)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
	return (getline(line, size_line, stdin));
}
