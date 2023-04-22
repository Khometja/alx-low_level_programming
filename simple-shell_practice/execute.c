#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMANDS 10
#define MAX_COMMAND_LENGTH 100

void execute_command(char *command) 
{
    char *argv[MAX_COMMAND_LENGTH];
    char *token = strtok(command, " \t\n");
    int argc = 0;

    while (token != NULL) 
    {
        argv[argc++] = token;
        token = strtok(NULL, " \t\n");
    }
    argv[argc] = NULL;

    if (argc > 0) 
    {
        pid_t pid = fork();
        if (pid == 0) 
	{
            if (execvp(argv[0], argv) == -1) 
	    {
                perror("execvp");
            }
            exit(EXIT_FAILURE);
        } 
	else if (pid < 0) 
	{
            perror("fork");
        } 
	else 
	{
            int status;
            if (waitpid(pid, &status, 0) == -1) 
	    {
                perror("waitpid");
            }
        }
    }
}

int main() {
    char input[MAX_COMMANDS * MAX_COMMAND_LENGTH];
    char *commands[MAX_COMMANDS];
    int num_commands = 0;

    while (1) {
        printf("$ ");
        fgets(input, sizeof(input), stdin);

        char *token = strtok(input, ";");
        while (token != NULL) {
            commands[num_commands++] = token;
            token = strtok(NULL, ";");
        }

        for (int i = 0; i < num_commands; i++) {
            execute_command(commands[i]);
        }

        num_commands = 0;
    }

    return 0;
}

