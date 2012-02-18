#include <stdio.h>
#include <stdlib.h>
#include "libihf.h"

#define OPTION_HELP     1
#define OPTION_VERBOSE  2

int usage(char *progname) {
    if (!progname)
        return 1;

    printf("Usage: %s [h|v] host port\n", progname);

    return 0;
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

    for (idx_arg = 0; idx_arg < argc; idx_arg++) {
        printf("arg[%d]: %s\n", idx_arg, argv[idx_arg]);
        int retcode = sscanf(argv[idx_arg], "%d.%d.%d.%d", &port, &port, &port, &port);
        printf("retcode: %d\n", retcode);
    }

#define TEST_STR    "hahaha toto tata titi\n"
    char *toxplod = strdup(TEST_STR);
    int lentoxplod = strlen(TEST_STR);
    int nExploded;
    char **exploded = explode(toxplod, strlen(toxplod), " ", &nExploded);
    int idx_exploded;

    printf("nExploded: %d\n", nExploded);
    for (idx_exploded = 0; idx_exploded < nExploded; idx_exploded++) {
        printf("exploded %d: %s\n", idx_exploded, exploded[idx_exploded]);
    }

    return 0;
}

