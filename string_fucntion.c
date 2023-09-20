#include "shell.h"

/**
 * _strdup - Duplicates a string
 * @src: The source string to duplicate
 *
 * Return: Returns a pointer(str)
 */
char *_strdup(const char *src)
{
	char *str;
	char *p;
	int len = 0;

	while (src[len])
		len++;

	str = malloc(len + 1);
	if (!str)
		return (NULL);

	p = str;
	while (*src)
		*p++ = *src++;
	*p = '\0';
	return (str);
}

/**
 * _strlen - Calculates the length of a string
 * @str: The string to measure
 *
 * Return: Returns the length of the string.
 */
int _strlen(char *str)
{
	int len = 0;

	while (str[len] != '\0')
		len++;
	return (len);
}

/**
 * _strcmp - Compares two strings.
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 *
 * Return: The difference between the ASCII values of the first unmatched
 * characters, 0 if the strings are identical.
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}

	return (s1[i] - s2[i]);
}


/**
 * _atoi - convert a string into an integer.
 *
 * @s: the string to use.
 *
 * Return: integer.
 */
int _atoi(char *s)
{
	int sign = 1, i = 0;
	unsigned int res = 0;

	while (!(s[i] <= '9' && s[i] >= '0') && s[i] != '\0')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	while (s[i] <= '9' && (s[i] >= '0' && s[i] != '\0'))
	{
		res = (res * 10) + (s[i] - '0');
		i++;
	}
	res *= sign;
	return (res);
}
