#include <stdio.h>
#include <stdlib.h>

/**
 * exit_shell - Exits the shell.
 * @args: An array of arguments passed to the exit command.
 *
 * Return: -1 if an error occurs, or the integer value of the exit status.
 */
int exit_shell(char **args)
{
        int status = 0;

        if (args[1])
                status = atoi(args[1]);

        exit(status);

        return (-1);
}

