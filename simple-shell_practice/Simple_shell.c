#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/**
 * prompt - Display a prompt for the user to enter a command
 */
void prompt(void)
{
    printf("$ ");
}

/**
 * read_command - Read a command from the user
 * @buffer: The buffer to store the command in
 */
void read_command(char *buffer)
{
    fgets(buffer, BUFFER_SIZE, stdin);
}

/**
 * execute_command - Execute a command
 * @command: The command to execute
 */
void execute_command(char *command)
{

    command[strcspn(command, "n")] = '0';

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
    }
    else if (pid == 0)
    {
     
        if (execlp(command, command, (char *)NULL) == -1)
        {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
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

/**
 * main - The entry point of the program
 *
 * Return: Always 0
 */
int main(void)
{
    char buffer[BUFFER_SIZE];

    while (1)
    {
        prompt();
        read_command(buffer);

        if (feof(stdin))
        {
            printf("n");
            break;
        }

        execute_command(buffer);
    }

    return (0);
}
