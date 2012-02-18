#ifndef _LIBIHF_H_
#define _LIBIHF_H_

#include <stdint.h>

#define IHF_FIXLEN 5
#define IHF_VERSION 1

// XXX RENAME pkt to msg
struct ihf_pkt_s {
    uint8_t version;
    uint8_t type;
    uint16_t arglen;
    uint8_t *arg;
};

enum {
    MSG_TYPE_INIT = 0,
    MSG_TYPE_KILL = 1,
    MSG_TYPE_EXEC = 2,
    MSG_TYPE_READ = 3,
    MSG_TYPE_WRITE = 4,
    MSG_TYPE_DATA = 5
};

uint8_t          *msg_pack(int, char *);
struct ihf_pkt_s *msg_unpack(uint8_t *, int);

char **explode (char *str, int len, char *delim);

#endif /* _LIBIHF_H_ */
