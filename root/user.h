#ifndef USER_H
#define USER_H

// Function prototypes for user management commands
void whoami_command(int argc, char **argv);
void useradd_command(int argc, char **argv);
void login_command(int argc, char **argv);
void logout_command(int argc, char **argv);
void passwd_command(int argc, char **argv);

#endif // USER_H