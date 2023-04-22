#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/**
 * unset_env - Unset an environment variable
 * @name: The name of the variable to unset
 *
 * Return: 0 on success, -1 on failure
 */
int unset_env(char *name)
{
        if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL) 
	{
                fprintf(stderr, "Invalid argument: %s\n", name);
                return -1;
        }

        if (unsetenv(name) == -1) 
	{
                fprintf(stderr, "unsetenv failed: %s\n", strerror(errno));
                return -1;
        }

        return (0);
}
