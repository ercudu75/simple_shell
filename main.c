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

	if (!isatty(0))
	{
		while (getline(&line, &size_line, stdin) != -1)
		{
			non_interactive_mode(line, &status);
		}
		if (line)
		{
			free(line);
			line = NULL;
		}
		return (status);
	}
	debut_shell();
	return (0);
}
/**
 * non_interactive_mode - Executes shell commands in non_nteractive_mode
 * @token: The string containing commands separated by newline characters
 * @status: integer store the number
 * Return: Returns status.
 */
void non_interactive_mode(char *token, int *status)
{
	char **single_command;

	token[strlen(token) - 1] = '\0';
	single_command = tokenize_string(token, " \t");
	if (single_command[0])
	{
		if (!_strcmp(single_command[0], "exit"))
		{
			free_array(single_command);
			free(token);
			exit(*status);
		}
		execute_command_non_interactive(single_command[0], single_command, status);
	}
	free_array(single_command);
}
/**
 * execute_command_non_interactive - Executes a single shell command
 * @command: The command to execute
 * @argv: The arguments for the command
 * @status: integer store the number
 *
 * Return: Returns status.
 */
void execute_command_non_interactive(char *command, char **argv, int *status)
{
	int pid;

	*status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (execve(command, argv, NULL) == -1)
		{
			write_error(command);
			*status = 127;
		}
	}
	else
	{
		wait(status);
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
	}
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
		result[count] = _strdup(token);
		count++;
		token = strtok(NULL, delimiters);
	}
	result[count] = NULL;

	return (result);
}
