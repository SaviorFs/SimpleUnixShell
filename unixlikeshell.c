#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 80

void createProcess(char *args[], int background) {
    pid_t pid = fork(); // this makes a new process
    if (pid < 0) {
        perror("Fork failed"); // Something went wrong
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execvp(args[0], args) == -1) { // attempt to run the command
            perror("Execution failed");
        }
        exit(EXIT_FAILURE); // child exits if exec fails
    } else {
        if (!background) {
            wait(NULL); // waits for the child process to finish if it's not running in the bg
        }
    }
}

int main(void) {
    char *args[MAX_LINE/2 + 1]; // array that will store command args
    char input[MAX_LINE]; // user input is here
    int should_run = 1; // keeps running until the user types "exit"

    while (should_run) {
        printf("sh> "); // prints the shell prompt
        fflush(stdout);

        if (fgets(input, MAX_LINE, stdin) == NULL) continue; // this reads input from the user

        size_t length = strlen(input);
        if (input[length - 1] == '\n') {
            input[length - 1] = '\0'; // this will remove the newline character
        }

        if (strcmp(input, "exit") == 0) { // this exits the shell if the user types "exit"
            should_run = 0;
            continue;
        }

        int i = 0;
        args[i] = strtok(input, " "); // this splits the input into individual words
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " "); // this will keep on splitting until no more words
        }

        int background = 0;
        if (i > 0 && strcmp(args[i-1], "&") == 0) { // this checks if the command should run in the background
            background = 1;
            args[i-1] = NULL; // this will remove the "&" from the args
        }

        createProcess(args, background); // this passes the command to create a new process
    }
    return 0;
}
