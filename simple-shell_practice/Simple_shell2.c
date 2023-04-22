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
 * split_command - Split a command line into an array of arguments
 * @command: The command line to split
 * @args: The array to store the arguments in
 *
 * Return: The number of arguments in the array
 */
int split_command(char *command, char **args)
{
    int argc = 0;
    char *arg;

    arg = strtok(command, " tn");
    while (arg != NULL)
    {
        args[argc++] = arg;
        arg = strtok(NULL, " tn");
    }
    args[argc] = NULL;

    return argc;
}

/**
 * execute_command - Execute a command with arguments
 * @argc: The number of arguments
 * @argv: The array of arguments
 */
void execute_command(int argc, char **argv)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
    }
    else if (pid == 0)
    {
        if (execvp(argv[0], argv) == -1)
        {
            perror("execvp");
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
    char *args[BUFFER_SIZE];
    int argc;

    while (1)
    {
        prompt();
        read_command(buffer);

        if (feof(stdin))
        {
            printf("n");
            break;
        }

        argc = split_command(buffer, args);
        if (argc > 0)
        {
            execute_command(argc, args);
        }
    }

    return (0);
}

