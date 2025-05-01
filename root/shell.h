#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum number of arguments for a command
#define MAX_ARGS 10

// Structure for a shell command
typedef struct {
    const char *name;                  // Command name
    void (*handler)(int argc, char **argv); // Function pointer to the command handler
    const char *description;          // Command description
} Command;

// Function prototypes
void start_shell(); // Start the shell loop
void handle_command(char *command);
void render_prompt();
void execute_command(const char *name, int argc, char **argv);

// Command prototypes for built-in commands
void man_command(int argc, char **argv);
void help_command(int argc, char **argv);
void sysinfo_command(int argc, char **argv);
void pwd_command(int argc, char **argv);
void ls_command(int argc, char **argv);
void cd_command(int argc, char **argv);
void mkdir_command(int argc, char **argv);
void rmdir_command(int argc, char **argv);
void touch_command(int argc, char **argv);
void rm_command(int argc, char **argv);
void cp_command(int argc, char **argv);
void mv_command(int argc, char **argv);
void rename_command(int argc, char **argv);
void search_command(int argc, char **argv);
void edit_command(int argc, char **argv);
void run_command(int argc, char **argv);
void calendar_command(int argc, char **argv);
void clock_command(int argc, char **argv);
void clear_command(int argc, char **argv);
void echo_command(int argc, char **argv);
void cat_command(int argc, char **argv);
void tetra_command(int argc, char **argv);
void flipper_command(int argc, char **argv);
void pull_command(int argc, char **argv);

// Command table (to be defined in shell.c or cmd_*.c)
extern Command command_table[];
extern const int command_table_size;

#endif // SHELL_H