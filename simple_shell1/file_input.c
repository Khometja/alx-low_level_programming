#include <stdio.h>

void print_message(char *message);

int main(void)
{
    char *message = "Simple shell project";
    print_message(message);
    return 0;
}

void print_message(char *message)
{
    printf("%s\n", message);
}

