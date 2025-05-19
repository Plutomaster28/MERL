#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <direct.h> // For Windows-specific directory functions
#include "shell.h"
#include "user.h"
#include "kernel.h"
#include "tetra.h"
#include "color-and-test.h"
#include "config.h"

// Function prototypes
void handle_command(char *command);
void man_command(int argc, char **argv);
void help_command(int argc, char **argv);

// Start the shell loop
void start_shell() {
    char input[256];

    printf("=== MERL Shell ===\n");
    printf("Type 'exit' to quit.\n");

    while (1) {
        // Render the shell prompt
        printf("merl> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\nExiting shell...\n");
            break;
        }

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Exit condition
        if (strcmp(input, "exit") == 0) {
            printf("Exiting shell...\n");
            break;
        }

        // Dispatch the command
        handle_command(input);
    }
}

// Command implementations

void sysinfo_command(int argc, char **argv) {
    printf("MERL Shell: %s\n", OS_VERSION);
    printf("Developed by: Tomoko Saito\n");
    printf("System: %s\n", SYSTEM_NAME);
    printf("Note: Unlike Zora, this is meant to provide a unix-like experience :3\n");
}

void pwd_command(int argc, char **argv) {
    char cwd[256];
    if (_getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current Directory: %s\n", cwd);
    } else {
        perror("pwd");
    }
}

void ls_command(int argc, char **argv) {
    system("dir"); // Windows equivalent of 'ls'
}

void cd_command(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: cd <directory>\n");
        return;
    }
    if (_chdir(argv[1]) == 0) {
        printf("Changed directory to: %s\n", argv[1]);
    } else {
        perror("cd");
    }
}

void mkdir_command(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: mkdir <directory>\n");
        return;
    }
    if (_mkdir(argv[1]) == 0) {
        printf("Directory created: %s\n", argv[1]);
    } else {
        perror("mkdir");
    }
}

void rmdir_command(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: rmdir <directory>\n");
        return;
    }
    if (_rmdir(argv[1]) == 0) {
        printf("Directory removed: %s\n", argv[1]);
    } else {
        perror("rmdir");
    }
}

void touch_command(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: touch <filename>\n");
        return;
    }
    FILE *file = fopen(argv[1], "w");
    if (file) {
        fclose(file);
        printf("File created: %s\n", argv[1]);
    } else {
        perror("touch");
    }
}

void rm_command(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: rm <filename>\n");
        return;
    }
    if (remove(argv[1]) == 0) {
        printf("File removed: %s\n", argv[1]);
    } else {
        perror("rm");
    }
}

void cp_command(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: cp <source> <destination>\n");
        return;
    }
    FILE *src = fopen(argv[1], "rb");
    if (!src) {
        perror("cp");
        return;
    }
    FILE *dest = fopen(argv[2], "wb");
    if (!dest) {
        fclose(src);
        perror("cp");
        return;
    }
    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dest);
    }
    fclose(src);
    fclose(dest);
    printf("File copied from %s to %s\n", argv[1], argv[2]);
}

void mv_command(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: mv <source> <destination>\n");
        return;
    }
    if (rename(argv[1], argv[2]) == 0) {
        printf("File moved from %s to %s\n", argv[1], argv[2]);
    } else {
        perror("mv");
    }
}

void rename_command(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: rename <oldname> <newname>\n");
        return;
    }
    if (rename(argv[1], argv[2]) == 0) {
        printf("File renamed from %s to %s\n", argv[1], argv[2]);
    } else {
        perror("rename");
    }
}

void calendar_command(int argc, char **argv) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    printf("Current Date: %02d-%02d-%04d\n", local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
}

void clock_command(int argc, char **argv) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    printf("Current Time: %02d:%02d:%02d\n", local->tm_hour, local->tm_min, local->tm_sec);
}

void clear_command(int argc, char **argv) {
    system("cls"); // Windows equivalent of 'clear'
}

void echo_command(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");
}

void cat_command(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: cat <filename>\n");
        return;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("cat");
        return;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }
    fclose(file);
}

void pull_command(int argc, char **argv) {
    printf("Checking for updates...\n");
    printf("No updates available.\n"); // Placeholder
}

void flipper_command(int argc, char **argv) {
    printf("Sub-shell switching not implemented yet.\n"); // Placeholder
}

void search_command(int argc, char **argv) {
    printf("Search functionality not implemented yet.\n");
}

void edit_command(int argc, char **argv) {
    printf("Edit functionality not implemented yet.\n");
}

void run_command(int argc, char **argv) {
    printf("Run functionality not implemented yet.\n");
}

// Command table
Command command_table[] = {
    {"man", man_command, "Displays information about commands."},
    {"help", help_command, "Displays the help menu."},
    {"sysinfo", sysinfo_command, "Displays system information and credits."},
    {"pwd", pwd_command, "Prints the current working directory."},
    {"ls", ls_command, "Lists the contents of the current directory."},
    {"cd", cd_command, "Changes the current working directory."},
    {"mkdir", mkdir_command, "Creates a new directory."},
    {"rmdir", rmdir_command, "Removes a directory."},
    {"touch", touch_command, "Creates a new file."},
    {"rm", rm_command, "Removes a file."},
    {"cp", cp_command, "Copies a file."},
    {"mv", mv_command, "Moves a file."},
    {"rename", rename_command, "Renames a file."},
    {"search", search_command, "Searches for files matching a pattern."},
    {"edit", edit_command, "Edits a text file."},
    {"run", run_command, "Runs an external program."},
    {"calendar", calendar_command, "Displays the current date."},
    {"clock", clock_command, "Displays the current time."},
    {"clear", clear_command, "Clears the screen."},
    {"echo", echo_command, "Prints a string to the console."},
    {"cat", cat_command, "Displays the contents of a file."},
    {"tetra", tetra_command, "Handles package management."},
    {"flipper", flipper_command, "Switches to sub-shells."},
    {"pull", pull_command, "Checks and applies updates."},
    {"whoami", whoami_command, "Displays the current logged-in user."},
    {"useradd", useradd_command, "Adds a new user (placeholder)."},
    {"login", login_command, "Logs in as a specified user."},
    {"logout", logout_command, "Logs out the current user."},
    {"passwd", passwd_command, "Changes the password for the current user (placeholder)."},
    {"fork", (void (*)(int, char **))route_command, "Creates a new process."},
    {"kill", (void (*)(int, char **))route_command, "Terminates a process by ID."},
    {"ps", (void (*)(int, char **))route_command, "Lists all active processes."},
    {"read", (void (*)(int, char **))route_command, "Reads a file."},
    {"write", (void (*)(int, char **))route_command, "Writes to a file."},
    {"color-and-test", color_and_test_command, "Displays colors and system info."}
};
const int command_table_size = sizeof(command_table) / sizeof(Command);

void handle_command(char *command) {
    // Tokenize the command
    char *args[10];
    int argc = 0;

    char *token = strtok(command, " ");
    while (token != NULL && argc < 10) {
        args[argc++] = token;
        token = strtok(NULL, " ");
    }
    args[argc] = NULL;

    // Search for the command in the command table
    for (int i = 0; i < command_table_size; i++) {
        if (strcmp(args[0], command_table[i].name) == 0) {
            command_table[i].handler(argc, args);
            return;
        }
    }

    printf("Unknown command: %s\n", args[0]);
}

void man_command(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: man <command>\n");
        return;
    }

    for (int i = 0; i < command_table_size; i++) {
        if (strcmp(argv[1], command_table[i].name) == 0) {
            printf("%s: %s\n", command_table[i].name, command_table[i].description);
            return;
        }
    }

    printf("No manual entry for '%s'\n", argv[1]);
}

void help_command(int argc, char **argv) {
    printf("Available commands:\n");
    for (int i = 0; i < command_table_size; i++) {
        printf("  %s - %s\n", command_table[i].name, command_table[i].description);
    }
}