#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

// Global variables for user management
static char current_user[50] = "guest"; // Default user
static int is_logged_in = 0;            // Login status

// Command implementations

void whoami_command(int argc, char **argv) {
    printf("Current user: %s\n", current_user);
}

void useradd_command(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: useradd <username>\n");
        return;
    }
    printf("User '%s' added successfully (placeholder, no persistence).\n", argv[1]);
}

void login_command(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: login <username>\n");
        return;
    }
    strncpy(current_user, argv[1], sizeof(current_user) - 1);
    current_user[sizeof(current_user) - 1] = '\0';
    is_logged_in = 1;
    printf("Logged in as '%s'.\n", current_user);
}

void logout_command(int argc, char **argv) {
    if (!is_logged_in) {
        printf("No user is currently logged in.\n");
        return;
    }
    printf("User '%s' logged out.\n", current_user);
    strncpy(current_user, "guest", sizeof(current_user) - 1);
    current_user[sizeof(current_user) - 1] = '\0';
    is_logged_in = 0;
}

void passwd_command(int argc, char **argv) {
    if (!is_logged_in) {
        printf("You must be logged in to change the password.\n");
        return;
    }
    printf("Password change functionality not implemented yet.\n");
}