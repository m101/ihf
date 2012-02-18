#ifndef _LIBIHF_H_
#define _LIBIHF_H_

#include <stdint.h>

struct ihf_pkt_s {
    uint8_t version:
    uint8_t type:
    uint16_t length:
    uint8_t *argn:
};

enum {
    PKT_TYPE_INIT = 0,
    PKT_TYPE_KILL = 1,
    PKT_TYPE_READ = 2,
    PKT_TYPE_WRITE = 3,
    PKT_TYPE_EXEC = 4,
    PKT_TYPE_DATA = 5
};

uint8_t          *msg_pack(int type, char *arg);
struct ihf_pkt_s *msg_unpack(uint8_t *);
// explode func
char **explode (char *str, int len, char *delim);

#endif /* _LIBIHF_H_ */
