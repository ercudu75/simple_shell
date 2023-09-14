#include "shell.h"

/**
 * main - Entry point for the shell program
 *
 * Return: Returns 0 on success, or status of the non_interactive_mode
 */
int main(void)
{
	size_t size_line = 0;
	char *line = NULL;
	int status = 0;
	char *line_copy;

	if (!isatty(0))
	{
		while (getline(&line, &size_line, stdin) != -1)
		{
			line_copy = _strdup(line);
			status = non_interactive_mode(line_copy);
			free(line_copy);
		}
		free(line);
		return (status);
	}
	debut_shell();
	return (0);
}
/**
 * non_interactive_mode - Executes shell commands in non_nteractive_mode
 * @token: The string containing commands separated by newline characters
 *
 * Return: Returns status.
 */
int non_interactive_mode(char *token)
{
	char **commands;
	int i, status;
	char **single_command;

	commands = tokenize_string(token, "\n");

	for (i = 0; commands[i] != NULL; i++)
	{
		single_command = tokenize_string(commands[i], " \t");
		if (single_command[0])
		{
			if (!_strcmp(single_command[0], "exit"))
			{
				free(single_command);
				exit(EXIT_SUCCESS);
			}
			status = execute_command_non_interactive(single_command[0], single_command);
		}
		else
		{
			status = 0;
		}
		free(single_command);
	}

	free(commands);
	return (status);
}
/**
 * execute_command_non_interactive - Executes a single shell command
 * @command: The command to execute
 * @argv: The arguments for the command
 *
 * Return: Returns status.
 */
int execute_command_non_interactive(char *command, char **argv)
{
	int pid, status = 0;

	pid = fork();
	if (pid == 0)
	{
		if (execve(command, argv, NULL) == -1)
		{
			write_error();
			exit(127);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	return (status);
}
/**
 * tokenize_string - Splits a string into tokens
 * @str: The string to tokenize
 * @delimiters: The delimiters to use for tokenization
 *
 * Return: Returns result.
 */
char **tokenize_string(char *str, char *delimiters)
{
	int count = 0;
	char *token;
	char **result = malloc(20 * sizeof(char *));

	if (result == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
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
