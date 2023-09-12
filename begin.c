#include "shell.h"

void debut_shell(void)
{
	char *line = NULL;
	char **commands;
	char *envp[] = {NULL};
	size_t size_line = 0;
	ssize_t nread;
	int i;

	while (1)
	{
		nread = read_command(&line, &size_line);
		if (nread == -1)
		{
			perror("getline");
			free(line);
			exit(EXIT_FAILURE);
		}
		commands = tokenize_string(line, " \n\t");

		if (commands[0] && strcmp(commands[0], "exit") == 0)
		{
			free(commands);
			free(line);
			exit(EXIT_SUCCESS);
		}
		for (i = 0; commands[i] != NULL; i++)
		{
			execute_command(commands[i], envp);
		}

		free(commands);
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

