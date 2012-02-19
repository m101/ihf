#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "libihf.h"

#define OPTION_HELP     1
#define OPTION_VERBOSE  2

int usage(char *progname) {
    if (!progname)
        return 1;

    printf("Usage: %s [h|v] host port\n", progname);

    return 0;
}

// will return TRUE for an ip
// will return FALSE otherwise
int validate_ip(char *ip) {
    long host;
    char *end;
    char integer[10];

    host = strtol(ip, &end, 10);
    if (host <= 0 || host > 255)
        return 0;
    snprintf(integer, 10, "%ld", host);

    if (strcmp(ip, integer))
        return 1;
    else
        return 0;
}

// will return TRUE for a port
// will return FALSE otherwise
int validate_port(char *port) {
    long p;
    char *end;
    char integer[10];

    p = strtol(port, &end, 10);
    if (p <= 0 || p > 65535)
        return 0;
    snprintf(integer, 10, "%ld", p);

    if (strcmp(port, integer))
        return 0;
    else
        return 1;
}

int main(int argc, char *argv[]) {
    int c;
    int flags = 0;
    int idx_arg;
    char *host;
    int port;

    if (argc < 3) {
        usage(argv[0]);
        exit(1);
    }

    while ((c = getopt (argc, argv, "hv")) != -1) {
        switch (c) {
            case 'h':
                flags |= OPTION_HELP;
                break;
            case 'v':
                flags |= OPTION_VERBOSE;
                break;
        }
    }

    if (flags & OPTION_HELP)
        usage(argv[0]);
    if (flags & OPTION_VERBOSE)
        printf("verbose not implemented\n");

    for (idx_arg = 0; idx_arg < argc; idx_arg++)
        printf("arg[%d]: %s\n", idx_arg, argv[idx_arg]);
    putchar('\n');

    for (idx_arg = 0; idx_arg < argc; idx_arg++) {
        if (validate_ip(argv[idx_arg]))
            printf("%s is an ip address\n", argv[idx_arg]);
        else {
            if (validate_port(argv[idx_arg]))
                printf("%s is a port\n", argv[idx_arg]);
            else
                printf("%s is not an ip address or port\n", argv[idx_arg]);
        }
    }

    return 0;
}

