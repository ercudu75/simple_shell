#include "shell.h"

int main(void)
{
	size_t size_line = 0;
	char *line = NULL;
	char *token = NULL;

	if (!isatty(0))
	{
		getline(&line, &size_line, stdin);
		token = strtok(line, "\n");
		return (non_interactive_mode(token));
	}
	debut_shell();
	return (0);
}
/**
 * commands not found return 127,
 * directory khaweya return 2,
 * exit return 0
 */
int non_interactive_mode(char *token)
{
	char *argv[2];
	int pid, status = 0;

	argv[0] = token;
	argv[1] = NULL;
	pid = fork();
	if (pid == 0)
	{
		if (execve(token, argv, NULL) == -1)
		{
			write(STDOUT_FILENO, "No such file or directory\n", 27);
			return (EXIT_FAILURE);
		}
	else
	{
		wait(&status);
	}
	}
	return (200);
}
