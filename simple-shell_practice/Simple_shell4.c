#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 80 
/**
 * main- The maximum length command 
 * Return: 0
 */

int execute_command(char **args);

int main(void)
{
    char *args[MAX_LINE/2 + 1];
    int should_run = 1;

    while (should_run) 
    {
        printf("osh>");
        fflush(stdout);

        char input[MAX_LINE];
        fgets(input, MAX_LINE, stdin);

        int argc = 0;
        char *token = strtok(input, " n");
        while (token != NULL) 
	{
            args[argc] = token;
            argc++;
            token = strtok(NULL, " n");
        }
        args[argc] = NULL;

        if (strcmp(args[0], "exit") == 0) 
	{
            should_run = 0;
        } else 
	{
            if (access(args[0], X_OK) == -1) 
	    {
                printf("%s: command not foundn", args[0]);
                continue;
            }

            should_run = execute_command(args);
        }
    }

    return 0;
}

int execute_command(char **args)
{
    pid_t pid = fork();

    if (pid == 0) 
    {
        execvp(args[0], args);
        exit(0);
    } else if (pid < 0) {
        printf("Fork failedn");
        return 0;
    } else 
    {
        wait(NULL);
        return 1;
    }
}

