#include "shell.h"

/**
 * debut_shell - Starts the shell's main loop
 *
 * Description: Initializes the shell, handles user input,
 * tokenizes commands and executes them.
 */

/**
 * debut_shell - Starts the shell's main loop
 *
 * Description: Initializes the shell, handles user input,
 * tokenizes commands and executes them.
 */
void debut_shell(void)
{
	char *line = NULL, **commands, *envp[] = {NULL};
	size_t size_line = 0;
	ssize_t nread;
	int status = 0;

	while (1)
	{
		nread = read_command(&line, &size_line);
		if (nread == -1)
		{
			perror("getline");
			free(line);
			line = NULL;
			exit(EXIT_FAILURE);
		}
		commands = tokenize_string(line, " \n\t");
		if (commands[0])
		{
			if (_strcmp(commands[0], "exit") == 0)
			{
				free_array(commands);
				free(line);
				line = NULL;
				exit(EXIT_SUCCESS);
				break;
			}
			else {
				_execvep(commands, envp, &status);
			}
		}
		free_array(commands);
		free(line);
		line = NULL;
	}
}


/**
 * read_command - Reads a line of command from the user
 * @line: The line buffer to store command
 * @size_line: The size of the line buffer
 *
 * Return: Returns the number of characters read.
 */
ssize_t read_command(char **line, size_t *size_line)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
	return (getline(line, size_line, stdin));
}
/**
 * write_error - Writes an error message to STDERR
 *
 * @command: command
 * Description: Writes an error message
 */
void write_error(char *command)
{
	write(STDERR_FILENO, "./hsh: 1: ", 10);
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": not found\n", 12);
}
/**
 * free_array - Frees memory allocated for an array of strings.
 * @array: A pointer to the dynamically allocated array of strings.
 *
 * This function frees the memory allocated for an array of strings.
 */
void free_array(char **array)
{
	int i;

	if (!array)
		return;
	for (i = 0; array[i] != NULL; i++)
	{
		free(array[i]);
	}
	free(array);
}
