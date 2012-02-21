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

#include "libihf.h"

#define TEST_STR    "arg0 arg1 arg2 arg3 arg4\n"

int main(int argc, char *argv[]) {
    char *toxplod = strdup(TEST_STR);
    int n_exploded;
    char **exploded = explode(toxplod, strlen(toxplod) + 1, " ", &n_exploded);
    int idx_exploded;

    printf("\nn_exploded: %d\n", n_exploded);
    for (idx_exploded = 0; idx_exploded < n_exploded; idx_exploded++) {
        printf("exploded %d: %s\n", idx_exploded, exploded[idx_exploded]);
    }

    return 0;
}

