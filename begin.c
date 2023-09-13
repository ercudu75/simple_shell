#include "shell.h"

/**
 * debut_shell - Starts the shell's main loop
 *
 * Description: Initializes the shell, handles user input,
 * tokenizes commands and executes them.
 */
void debut_shell(void)
{
	char *line = NULL;
	char **commands;
	char *envp[] = {NULL};
	size_t size_line = 0;
	ssize_t nread;
	char *line_copy;

	while (1)
	{
		nread = read_command(&line, &size_line);
		if (nread == -1)
		{
			perror("getline");
			free(line);
			exit(EXIT_FAILURE);
		}
		line_copy = _strdup(line);
		commands = tokenize_string(line_copy, " \n\t");
		if (commands[0] && strcmp(commands[0], "exit") == 0)
		{
			free(commands);
			free(line);
			exit(EXIT_SUCCESS);
		}
		execute_command(commands[0], envp, commands);
		free(line_copy);
	}
}
/**
 * execute_command - Executes a given shell command
 * @command: The command to execute
 * @envp: The environment variables
 * @argv: The command arguments
 *
 * Return: Returns the status code of the executed command.
 */
int execute_command(char *command, char **envp, char **argv)
{
	int pid, status = 0;

	pid = fork();
	if (pid == 0)
	{
		if (execve(command, argv, envp) == -1)
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
 * Description: Writes an error message
 */
void write_error(void)
{
	write(STDERR_FILENO, "./hsh: No such file or directory", 35);
}
