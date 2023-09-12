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
	char **commands;
	int pid, status = 0;
	int i;
	char *argv[2];

	commands = tokenize_string(token, " \n\t");
	for (i = 0; commands[i] != NULL; i++)
	{
		pid = fork();
		if (pid == 0)
		{
			argv[0] = commands[i];
			argv[1] = NULL;
			if (execve(commands[i], argv, NULL) == -1)
			{
				write(STDOUT_FILENO, "No such file or directory\n", 27);
				return (EXIT_FAILURE);
			}
		else
		{
			wait(&status);
		}
		}
	}
	free(commands);
	return (0);
}

char **tokenize_string(char *str, char *delimiters)
{
	int count = 0;
	char *token;
	char **result = malloc(20 * sizeof(char *)); // Assuming max 20 tokens for demonstration.

	token = strtok(str, delimiters);
	while (token != NULL) {
		result[count] = token;
		count++;
		token = strtok(NULL, delimiters);
	}
	result[count] = NULL;

	return result;
}
