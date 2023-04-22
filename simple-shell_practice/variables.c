#include <stdio.h>
#include <unistd.h>

/**
  *main - varibale function
  *
  *Return: Always 0
  */

int main(void) 

{
   pid_t pid;
   
   pid = getpid();
   
   printf("The PID of the current process is %d\n", pid);
   
   return (0);
}

