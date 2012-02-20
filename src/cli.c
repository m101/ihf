#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <getopt.h>

#include "libihf.h"

extern char *__progname;

/* XXX
 * we should inspire from netcat
 * http://www.openbsd.org/cgi-bin/cvsweb/src/usr.bin/nc/
 * see readwrite(), atomicio()
 */

int usage() {
    printf("Usage: %s [-hv] host port command\n", __progname);

    exit(1);
}

int main(int argc, char *argv[]) {
    int opt;
    int verbose = 0;
    char *host;
    int port;
    char *cmd;

    while ((opt = getopt(argc, argv, "hv")) != -1) {
        switch (opt) {
            case 'h':
                usage();
            case 'v':
                verbose = 1;
                break;
            default:
                usage();
        }
    }

    argc -= optind;
    argv += optind;

    if (argc != 3)
        usage();
    host = argv[0];
    port = atoi(argv[1]);
    cmd = argv[2];
    if (!host || port < 0 || !cmd)
        usage();
    
    if (verbose)
        printf("Connecting to %s port %d, executing %s\n",
                host, port, cmd);

    return 0;
}

