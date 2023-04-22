#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/**
 * my_getline - Reads a line from standard input and returns it as a null-terminated string.
 *
 * Return: The line read from standard input as a null-terminated string, or NULL if an error occurs.
 */
char *my_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static int buffer_position = 0;
	static int buffer_size = 0;
	char *line = NULL;
	int line_size = 0;
	int line_capacity = 0;

	while (1) {
		if (buffer_position == buffer_size) {
			buffer_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			buffer_position = 0;
			if (buffer_size == -1) {
				perror("my_getline");
				return NULL;
			} else if (buffer_size == 0) {
				if (line_size > 0) {
					if (line_capacity == line_size) {
						char *new_line = realloc(line, line_capacity * 2);
						if (!new_line) {
							perror("my_getline");
							free(line);
							return NULL;
						}
						line = new_line;
						line_capacity *= 2;
					}
					line[line_size] = '\0';
					return line;
				} else {
					return NULL;
				}
			}
		}

		while (buffer_position < buffer_size) {
			if (line_size == line_capacity) {
				char *new_line = realloc(line, line_capacity * 2);
				if (!new_line) {
					perror("my_getline");
					free(line);
					return NULL;
				}
				line = new_line;
				line_capacity *= 2;
			}
			if (buffer[buffer_position] == '\n') {
				buffer_position++;
				line[line_size] = '\0';
				return line;
			} else {
				line[line_size] = buffer[buffer_position];
				line_size++;
				buffer_position++;
			}
		}
	}
}

int main(void)
{
	char *line = NULL;
	while ((line = my_getline())) {
		printf("%s\n", line);
		free(line);
	}
	return 0;
}

