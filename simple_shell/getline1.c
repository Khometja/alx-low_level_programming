#include <stdlib.h>
#include <string.h>

/**
 * split_string - Splits a string into an array of strings using a delimiter.
 * @str: The string to split.
 * @delimiter: The delimiter to split the string by.
 * @count: A pointer to an integer that will be set to the number of elements in the resulting array.
 *
 * Return: An array of strings containing the substrings of @str that are separated by @delimiter,
 * or NULL if an error occurs.
 */
char **split_string(char *str, char delimiter, int *count)
{
        int i, j, len;
        char **tokens = NULL;

        if (!str || !count)
                return (NULL);

        len = strlen(str);
        *count = 0;

        /* First, count the number of tokens */
        for (i = 0; str[i]; i++)
        {
                if (str[i] == delimiter)
                        (*count)++;
        }
        (*count)++;

        /* Allocate memory for the tokens */
        tokens = malloc(sizeof(char *) * (*count));
        if (!tokens)
                return (NULL);

        /* Fill in the tokens */
        j = 0;
        for (i = 0; i < len; i++)
        {
                if (str[i] == delimiter)
                {
                        str[i] = '\0';
                        tokens[j++] = &str[i + 1];
                }
        }
        tokens[j] = &str[i];

        return (tokens);
}

