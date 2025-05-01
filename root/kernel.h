#ifndef KERNEL_H
#define KERNEL_H

// Kernel-level APIs
int fork_process();
void kill_process(int pid);
void list_processes();
void kernel_read(const char *filename);
void kernel_write(const char *filename, const char *content);

// Command routing
void route_command(const char *command, int argc, char **argv);

#endif // KERNEL_H