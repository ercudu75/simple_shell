#include "shell.h"

/**
 * handle_exit_status - Handles the exit status for a command.
 * @my_status: The status to check.
 * @single_command: The command arguments.
 * @token: A pointer to dynamically allocated memory.
 * @status: A pointer to an int to hold the status value.
 *
 * Return: void.
 */
void handle_exit_status(int my_status, char **single_command, char **token,
						int *status)
{
	if (my_status == -1 ||
		(my_status == 0 && single_command[1][0] != '0') ||
		my_status < 0)
	{
		write_exit_error(single_command[1]);
		*status = 2;
	}
	else
	{
		free(*token);
		free_array(single_command);
		exit(my_status);
	}
}

/**
 * handle_custom_exit - Handles custom exit statuses for a command.
 * @my_status: The exit status to check.
 * @commands: The array containing the command and its arguments.
 * @line: A pointer to the input line.
 * @status: A pointer to an int to hold the return status value.
 *
 * Return: void.
 */
void handle_custom_exit(int my_status, char **commands,
						char *line, int *status)
{
	if (my_status == -1 ||
		(my_status == 0 && commands[1][0] != '0') ||
		my_status < 0)
	{
		write_exit_error(commands[1]);
		*status = 2;
	}
	else
	{
		free(line);
		free_array(commands);
		exit(my_status);
	}
}
/**
 * handle_getline_error - Handles getline() error.
 * @line: A pointer to the input line.
 *
 * Return: void.
 */
void handle_getline_error(char *line)
{
	perror("getline");
	free(line);
	line = NULL;
	exit(EXIT_FAILURE);
}

