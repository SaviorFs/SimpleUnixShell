#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_LINE 80

void createProcess(char *args[], int background) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    char command[MAX_LINE] = "C:\\Windows\\System32\\cmd.exe /C ";
    for (int i = 0; args[i] != NULL; i++) {
        strcat(command, args[i]);
        strcat(command, " ");
    }

    printf("Executing command: %s\n", command);

    if (!CreateProcess(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }

    if (!background) {
        WaitForSingleObject(pi.hProcess, INFINITE);
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int main(void) {
    char *args[MAX_LINE/2 + 1];
    char input[MAX_LINE];
    int should_run = 1;

    while (should_run) {
        printf("sh> ");
        fflush(stdout);

        if (fgets(input, MAX_LINE, stdin) == NULL) continue;

        size_t length = strlen(input);
        if (input[length - 1] == '\n') {
            input[length - 1] = '\0';
        }

        if (strcmp(input, "exit") == 0) {
            should_run = 0;
            continue;
        }

        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        int background = 0;
        if (i > 0 && strcmp(args[i-1], "&") == 0) {
            background = 1;
            args[i-1] = NULL;
        }

        createProcess(args, background);
    }
    return 0;
}
