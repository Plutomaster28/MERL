#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kernel.h"

// Process table (placeholder for process management)
#define MAX_PROCESSES 10
static int process_table[MAX_PROCESSES] = {0}; // 0 = unused, 1 = active

// Kernel-level APIs

int fork_process() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (process_table[i] == 0) {
            process_table[i] = 1; // Mark process as active
            printf("Process %d created.\n", i);
            return i; // Return process ID
        }
    }
    printf("Error: Maximum process limit reached.\n");
    return -1; // Error: No available process slots
}

void kill_process(int pid) {
    if (pid < 0 || pid >= MAX_PROCESSES || process_table[pid] == 0) {
        printf("Error: Invalid process ID.\n");
        return;
    }
    process_table[pid] = 0; // Mark process as inactive
    printf("Process %d terminated.\n", pid);
}

void list_processes() {
    printf("Active processes:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (process_table[i] == 1) {
            printf("  Process ID: %d\n", i);
        }
    }
}

// File I/O simulation
void kernel_read(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error reading file");
        return;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);
}

void kernel_write(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error writing to file");
        return;
    }
    fprintf(file, "%s", content);
    fclose(file);
    printf("Content written to %s\n", filename);
}

// Command routing
void route_command(const char *command, int argc, char **argv) {
    if (strcmp(command, "fork") == 0) {
        fork_process();
    } else if (strcmp(command, "kill") == 0) {
        if (argc < 2) {
            printf("Usage: kill <process_id>\n");
            return;
        }
        kill_process(atoi(argv[1]));
    } else if (strcmp(command, "ps") == 0) {
        list_processes();
    } else if (strcmp(command, "read") == 0) {
        if (argc < 2) {
            printf("Usage: read <filename>\n");
            return;
        }
        kernel_read(argv[1]);
    } else if (strcmp(command, "write") == 0) {
        if (argc < 3) {
            printf("Usage: write <filename> <content>\n");
            return;
        }
        kernel_write(argv[1], argv[2]);
    } else {
        printf("Unknown kernel command: %s\n", command);
    }
}