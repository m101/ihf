/*
    ihf - Tool for bypassing firewalls
    Copyright (C) 2012  m_101, laurent

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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

