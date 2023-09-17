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