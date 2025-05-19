#include <stdio.h>
#include <string.h>
#include "tetra.h"
#include "config.h"

void tetra_command(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: tetra <download|update|remove|move|set-location> [args]\n");
        return;
    }
    if (strcmp(argv[1], "download") == 0) {
        tetra_download(argc, argv);
    } else if (strcmp(argv[1], "update") == 0) {
        tetra_update(argc, argv);
    } else if (strcmp(argv[1], "remove") == 0) {
        tetra_remove(argc, argv);
    } else if (strcmp(argv[1], "move") == 0) {
        tetra_move(argc, argv);
    } else if (strcmp(argv[1], "set-location") == 0) {
        tetra_set_location(argc, argv);
    } else {
        printf("Unknown tetra subcommand: %s\n", argv[1]);
    }
}

void tetra_download(int argc, char **argv) {
    printf("Download functionality not implemented yet.\n");
}

void tetra_update(int argc, char **argv) {
    printf("Update functionality not implemented yet.\n");
}

void tetra_remove(int argc, char **argv) {
    printf("Remove functionality not implemented yet.\n");
}

void tetra_move(int argc, char **argv) {
    printf("Move functionality not implemented yet.\n");
}

void tetra_set_location(int argc, char **argv) {
    printf("Set location functionality not implemented yet.\n");
}