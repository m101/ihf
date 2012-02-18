#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <unistd.h>
#include <sys/select.h>
#include <sys/types.h>

#include "libihf.h"

static uint8_t *encode(uint8_t *arg, int len) {
    uint8_t *res;

    res = malloc(sizeof(char) * len);

    return res;
}

static uint8_t *decode(uint8_t *arg, int len) {
    uint8_t *res;

    res = malloc(sizeof(char) * len);

    return res;
}

uint8_t *msg_pack(int type, uint8_t *arg, int arglen) {
    struct ihf_msg *msg;

    if (type > MSG_TYPE_MAX) {
        fprintf(stderr, "error: Message type not recognized\n");
        return NULL;
    }

    msg = malloc(IHF_FIXLEN + sizeof(uint8_t) * arglen);
    if (!msg)
        return NULL;
    msg->version = IHF_VERSION;
    msg->type = type;
    msg->arglen = arglen;
    if (msg->arglen > 0) {
        msg->arg = encode(arg, arglen);
        if (!msg->arg) {
            free(msg);
            return NULL;
        }
    }

    return (uint8_t *)msg;
}

struct ihf_msg *msg_unpack(uint8_t *data, int datalen) {
    struct ihf_msg *data_msg;
    struct ihf_msg *msg;

    if (datalen < IHF_FIXLEN)
        return NULL;

    data_msg = (struct ihf_msg *)data;

    /* XXX data_msg->arg finishes with \n ? */
    if (data_msg->type < MSG_TYPE_MAX) {
        fprintf(stderr, "error: Message type not recognized\n");
        return NULL;
    }

    msg = malloc(sizeof(struct ihf_msg));
    if (!msg)
        return NULL;
    msg->version = data_msg->version;
    msg->type = data_msg->type;
    if (data_msg->arglen != datalen - IHF_FIXLEN) {
        free(msg);
        return NULL;
    }
    msg->arglen = data_msg->arglen;
    if (msg->arglen > 0) {
        msg->arg = decode(data_msg->arg, data_msg->arglen);
        if (!msg->arg) {
            free(msg);
            return NULL;
        }
    }

    return msg;
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

int readall(int fd, char **req, int max) {
    char buf[1024];
    int len, l;

    len = 0;
    *req = NULL;
    for(;;) {
        l = read(STDIN_FILENO, buf, sizeof(buf));
        if (l <= 0)
            break;
        len += l;
        if (len > max) {
            fprintf(stderr, "Buffer size too grows too big, cancelling");
            return -1;
        }
        *req = realloc(*req, len);
        if (!(*req)) {
            fprintf(stderr, "Error allocating buffer !\n");
            return -1;
        }
    }

    return len;
}

