#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "libihf.h"

uint8_t          *msg_pack(int type, char *arg) {

}

struct ihf_pkt_s *msg_unpack(uint8_t *data) {

}

// explode func
char **explode (char *str, int len, char *delim) {
    // strtok_r stuffs
    char *token, *saveptr;
    // exploded str
    char *exploded;
    //
    int idx_str, idx_delim;
    int len_str, len_delim;

    // check params
    if (!str || len <= 0 || !delim)
        return NULL;

    // alloc
    exploded = calloc(len, sizeof(*exploded));
    if (!exploded)
        return NULL;
    // copy buf
    memcpy(exploded, str, len);

    // exploded in token
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

