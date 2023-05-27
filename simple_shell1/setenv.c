#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/**
 * set_env - Set an environment variable
 * @name: The name of the variable
 * @value: The value to set the variable to
 *
 * Return: 0 on success, -1 on failure
 */
int set_env(char *name, char *value)
{
        if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL) 
	{
                fprintf(stderr, "Invalid argument: %s\n", name);
                return -1;
        }

        if (setenv(name, value, 1) == -1) 
	{
                fprintf(stderr, "setenv failed: %s\n", strerror(errno));
                return -1;
        }

        return (0);
}
