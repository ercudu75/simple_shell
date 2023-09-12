#include "shell.h"

int main(void)
{
	size_t size_line = 0;
	char *line = NULL;

	if (!isatty(0))
	{
		getline(&line, &size_line, stdin);
		return (non_interactive_mode(line));
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
	char *envp[] = {NULL};
	int i;
	commands = tokenize_string(token, " \n\t");

	if (commands[0] && strcmp(commands[0], "exit") == 0)
	{
		free(commands);
		exit(EXIT_SUCCESS);
	}

	for (i = 0; commands[i] != NULL; i++)
	{
		execute_command(commands[i], envp);
	}

	free(commands);
	return (0);
}

char **tokenize_string(char *str, char *delimiters)
{
	int count = 0;
	char *token;
	char **result = malloc(20 * sizeof(char *));

	token = strtok(str, delimiters);
	while (token != NULL)
	{
		result[count] = token;
		count++;
		token = strtok(NULL, delimiters);
	}
	result[count] = NULL;

	return (result);
}
