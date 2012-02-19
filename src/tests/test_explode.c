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

