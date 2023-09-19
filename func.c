#include "shell.h"

/**
 * _execvep - Execute shell command and its arguments by searching in PATH
 * @commands: The command and its arguments as an array of strings
 * @envp: The environment variables
 * @status: The pointer to an int where the status will be stored
 */
void _execvep(char **commands, char **envp, int *status)
{
	int pid;

	pid = fork();

	if (pid == 0)
	{
		if (access(commands[0], X_OK) == 0)
		{
			execve(commands[0], commands, envp);
			exit(0);
		}

		search_path(commands, envp, status);
	}
	else
	{
		wait_child_process(status);
	}
}

/**
 * search_path - Searches for the full path of a cmd in the PATH env variable
 * @commands: The command to search for
 * @envp: The environment variables
 * @status: The status of the search
 *
 * Return: void
 */
void search_path(char **commands, char **envp, int *status)
{
	char *full_path, *token, *path_env;
	int found = 0;

	path_env = mygetenv("PATH");
	if (path_env != NULL)
	{
		char *path_env_copy = strdup(path_env);

		token = strtok(path_env_copy, ":");

		while (token != NULL && !found)
		{
			full_path = malloc(strlen(token) + strlen(commands[0]) + 2);
			if (full_path != NULL)
			{
				strcpy(full_path, token);
				strcat(full_path, "/");
				strcat(full_path, commands[0]);

				if (access(full_path, X_OK) == 0)
				{
					execve(full_path, commands, envp);
					found = 1;
				}

				free(full_path);
			}

			token = strtok(NULL, ":");
		}

		free(path_env_copy);
	}

	if (!found)
	{
		*status = 127;
		write_error(commands[0]);
		exit(127);
	}
}

void wait_child_process(int *status)
{
	int child_status;

	if (wait(&child_status) == -1)
	{
		perror("wait");
		exit(EXIT_FAILURE);
	}

	if (WIFEXITED(child_status))
	{
		*status = WEXITSTATUS(child_status);
	}
}

char *mygetenv(const char *path)
{
	int i, j;
	int found;

	for (i = 0; environ[i] != NULL; i++)
	{
		found = 1;
		for (j = 0; path[j] != '\0'; j++)
		{
			if (path[j] != environ[i][j])
			{
				found = 0;
				break;
			}
		}

		if (found && environ[i][j] == '=')
		{
			return (environ[i] + j + 1);
		}
	}

	return (NULL);
}
