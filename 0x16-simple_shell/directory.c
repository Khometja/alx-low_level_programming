#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH_LENGTH 1024

/**
 * current_dir - Changes the current directory of the process.
 *
 * @param path Path of the directory to change to. If NULL, changes to the home directory.
 * @param previous_path Pointer to a buffer where the previous path will be stored.
 * Return 0 on success, -1 on failure.
 */
int change_directory(const char* path, char* previous_path) {
    if (!path) {
        path = getenv("HOME");
        if (!path) {
            fprintf(stderr, "cd: HOME directory not set\n");
            return -1;
        }
    }
    else if (strcmp(path, "-") == 0) {
        path = getenv("OLDPWD");
        if (!path) {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return -1;
        }
    }

    char cwd[MAX_PATH_LENGTH];
    if (!getcwd(cwd, MAX_PATH_LENGTH)) {
        perror("cd");
        return -1;
    }
    if (previous_path) {
        strcpy(previous_path, cwd);
    }

    if (chdir(path) == -1) {
        perror("cd");
        return -1;
    }

    if (!getcwd(cwd, MAX_PATH_LENGTH)) {
        perror("cd");
        return -1;
    }
    if (setenv("OLDPWD", previous_path ? previous_path : "", 1) == -1) {
        perror("cd");
        return -1;
    }
    if (setenv("PWD", cwd, 1) == -1) {
        perror("cd");
        return -1;
    }

    return 0;
}

int main(int argc, char* argv[]) {
    char previous_path[MAX_PATH_LENGTH] = "";

    if (argc == 1) {
        change_directory(NULL, previous_path);
    }
    else if (argc == 2) {
        change_directory(argv[1], previous_path);
    }
    else {
        fprintf(stderr, "cd: too many arguments\n");
        return 1;
    }

    return 0;
}

