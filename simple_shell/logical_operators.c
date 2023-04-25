#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 10

void execute_command(char **args, int bg) 
{
    pid_t pid = fork();
    if (pid == -1) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) 
    {
        if (execvp(args[0], args) == -1) 
	{
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } 
    else 
    {
        if (!bg) 
	{
            int status;
            if (waitpid(pid, &status, 0) == -1) 
	    {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
        }
    }
}

int main(void) 
{
    char input[100];
    char *args[MAX_ARGS];
    int bg = 0;

    while (1) 
    {
        printf("> ");
        fflush(stdout);
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = 0;

        char *token = strtok(input, " ");
        int i = 0;
        while (token != NULL) 
	{
            if (strcmp(token, "&&") == 0) 
	    {
                if (i > 0 && strcmp(args[i-1], "0") == 0) 
		{
                    bg = 0;
                    break;
                }
            } 
	    else if (strcmp(token, "||") == 0) 
	    {
                if (i > 0 && strcmp(args[i-1], "0") != 0) 
		{
                    bg = 0;
                    break;
                }
            } 
	    else if (strcmp(token, "&") == 0) 
	    {
                bg = 1;
                break;
            }
	    else 
	    {
                args[i] = token;
                i++;
            }
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (i > 0) 
	{
            execute_command(args, bg);
        }
        bg = 0;
    }

    return (0);
}

