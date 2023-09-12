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
	char *commands[64];
	char *envp[] = {NULL};
	size_t size_line = 0;
	ssize_t nread;
	int command_count, i;

	while (1)
	{
		command_count = 0;
		nread = read_command(&line, &size_line);
		if (nread == -1)
		{
			perror("getline");
			free(line);
			exit(EXIT_FAILURE);
		}
		token = strtok(line, " \t\n");
		while (token != NULL)
		{
			commands[command_count] = token;
			command_count++;
			token = strtok(NULL, " \t\n");
		}
		commands[command_count] = NULL;
		for (i = 0; i < command_count; i++)
		{
			if (commands[i] && !strcmp(commands[i], "exit"))
			{
				free(line);
				return;
			}
			execute_command(commands[i], envp);
		}
	}
}

int execute_command(char *token, char **envp)
{
	int pid, status = 0;
	char *argv[2];

	argv[0] = token;
	argv[1] = NULL;

	pid = fork();
	if (pid == 0)
	{
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


