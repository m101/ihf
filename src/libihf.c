#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "libihf.h"

static char *encode(char *arg, int len) {
    char *res;

    res = malloc(sizeof(char) * len);

    return res;
}

static char *decode(char *arg, int len) {
    char *res;

    res = malloc(sizeof(char) * len);

    return res;
}

uint8_t *msg_pack(int type, char *arg, int arglen) {
    struct ihf_msg *msg;

    switch (type) {
        case MSG_TYPE_INIT:
        case MSG_TYPE_KILL:
        case MSG_TYPE_READ:
            break;
        case MSG_TYPE_EXEC:
        case MSG_TYPE_WRITE:
        case MSG_TYPE_DATA:
            if (arglen <= 0)
                return NULL;
            break;
        default:
            fprintf(stderr, "error: Message type not recognized\n");
            return NULL;
            break;
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
    switch (data_msg->type) {
        case MSG_TYPE_INIT:
        case MSG_TYPE_KILL:
            if (strlen(data_msg->arg) != 0)
                return NULL;
            break;
        case MSG_TYPE_EXEC:
        case MSG_TYPE_READ:
        case MSG_TYPE_WRITE:
        case MSG_TYPE_DATA:
            if (datalen != IHF_FIXLEN + strlen(data_msg->arg))
                return NULL;
            break;
        default:
            fprintf(stderr, "error: Message type not recognized\n");
            return NULL;
            break;
    }

    msg = malloc(sizeof(struct ihf_msg));
    if (!msg)
        return NULL;
    msg->version = data_msg->version;
    msg->type = data_msg->type;
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

