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

    if (type >= MSG_TYPE_MAX) {
        fprintf(stderr, "error: Message type not recognized\n");
        return NULL;
    }

    msg = calloc(IHF_FIXLEN + sizeof(uint8_t) * arglen, sizeof(uint8_t));
    if (!msg)
        return NULL;
    msg->version = IHF_VERSION;
    msg->type = type;
    if (arg && arglen > 0) {
        msg->arglen = arglen;
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
    if (data_msg->type >= MSG_TYPE_MAX) {
        fprintf(stderr, "error: Message type not recognized\n");
        return NULL;
    }

    if (data_msg->arglen != datalen - IHF_FIXLEN)
        return NULL;

    msg = malloc(sizeof(struct ihf_msg));
    if (!msg)
        return NULL;
    msg->version = data_msg->version;
    msg->type = data_msg->type;
    if (data_msg->arg && data_msg->arglen > 0) {
        msg->arglen = data_msg->arglen;
        msg->arg = decode(data_msg->arg, data_msg->arglen);
        if (!msg->arg) {
            free(msg);
            return NULL;
        }
    }

    return msg;
}

char **explode (char *str, int len_str, char *delim, int *n_tokens) {
    char *token, *saveptr;
    char *to_explode;
    char **exploded;
    int idx_str, idx_delim;
    int len_delim;
    int c_tokens;

    if (!str || len_str <= 0 || !delim || !n_tokens)
        return NULL;

    to_explode = calloc(len_str, sizeof(*to_explode));
    if (!to_explode)
        return NULL;
    memcpy(to_explode, str, len_str);

    // count n_tokens
    len_delim = strlen(delim);
    c_tokens = 1;
    for (idx_str = 0; idx_str < len_str; idx_str++) {
        for (idx_delim = 0; idx_delim < len_delim; idx_delim++) {
            if (str[idx_str] == delim[idx_delim])
                c_tokens++;
        }
    }

    // copy str (strdup() does not seem to be reliable)
    exploded = calloc(c_tokens, sizeof(*exploded));
    if (!to_explode) {
        free(to_explode);
        return NULL;
    }

    // sep tokens
    *n_tokens = 0;
    token = strtok_r(to_explode, delim, &saveptr);
    while (token) {
        exploded[*n_tokens] = token;
        (*n_tokens)++;
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

