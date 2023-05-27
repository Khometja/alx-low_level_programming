#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALIAS_LENGTH 100
#define MAX_VALUE_LENGTH 1000
#define MAX_NUM_ALIASES 100

/**
  *Alias - Max value
  *
  *Return:  0
  */

struct alias 
{
  char name[MAX_ALIAS_LENGTH];
  char value[MAX_VALUE_LENGTH];
};

int num_aliases = 0;
struct alias aliases[MAX_NUM_ALIASES];

void print_all_aliases() 
{
  for (int i = 0; i < num_aliases; i++) 
  {
    printf("%s='%s'\n", aliases[i].name, aliases[i].value);
  }
}

void print_specific_aliases(int num_names, char **names) 
{
  for (int i = 0; i < num_names; i++) 
  {
    for (int j = 0; j < num_aliases; j++) 
    {
      if (strcmp(names[i], aliases[j].name) == 0) 
      {
        printf("%s='%s'\n", aliases[j].name, aliases[j].value);
        break;
      }
    }
  }
}

void define_aliases(int num_names, char **names) 
{
  for (int i = 0; i < num_names; i++) 
  {
    char *name_value = strdup(names[i]);
    char *name = strtok(name_value, "=");
    char *value = strtok(NULL, "=");
    if (value == NULL) 
    {
      for (int j = 0; j < num_aliases; j++) 
      {
        if (strcmp(name, aliases[j].name) == 0) 
	{
          printf("%s='%s'\n", aliases[j].name, aliases[j].value);
          break;
        }
      }
    } 
    else 
    {
      int found = 0;
      for (int j = 0; j < num_aliases; j++) 
      {
        if (strcmp(name, aliases[j].name) == 0) 
	{
          strcpy(aliases[j].value, value);
          found = 1;
          break;
        }
      }
      if (!found) 
      {
        if (num_aliases == MAX_NUM_ALIASES) 
	{
          fprintf(stderr, "Too many aliases defined.\n");
          exit(1);
        }
        strcpy(aliases[num_aliases].name, name);
        strcpy(aliases[num_aliases].value, value);
        num_aliases++;
      }
    }
    free(name_value);
  }
}

int main(int argc, char **argv) {
  if (argc == 1) 
  {
    print_all_aliases();
  }
  else if (argc == 2) 
  {
    char *arg = argv[1];
  if (strchr(arg, '=') == NULL) 
    {
      print_specific_aliases(1, argv+1);
    }
  else 
    {
      define_aliases(1, argv+1);
    }
  } 
  else 
  {
    define_aliases(argc-1, argv+1);
  }
  return (0);
}

