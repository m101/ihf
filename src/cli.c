#include <stdio.h>
#include <stdlib.h>

#define OPTION_HELP     1
#define OPTION_VERBOSE  2

char **explode (char *str, int len, char *delim);

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
    char **exploded = explode(toxplod, strlen(toxplod), " ");

    return 0;
}

char **explode (char *str, int len, char *delim) {
    char *token, *saveptr;
    char *exploded;
    int idx_str, idx_delim;
    int len_str, len_delim;

    if (!str || len <= 0 || !delim)
        return NULL;

    exploded = calloc(len, sizeof(*exploded));
    if (!exploded)
        return NULL;
    memcpy(exploded, str, len);

    token = strtok_r(exploded, delim, &saveptr);
    while (token) {
        len_str = strlen(exploded);
        for (idx_str = 0; idx_str < len_str; idx_str++) {
            // for each delim -> the byte is put to 0
            len_delim = strlen(delim);
            for (idx_delim = 0; idx_delim < len_delim; idx_delim++) {
                if (exploded[idx_str] == delim[idx_delim])
                    exploded[idx_str] = '\0';
            }
        }
        token = strtok_r(NULL, delim, &saveptr);
    }

    return exploded;
}
