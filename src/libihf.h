#ifndef _LIBIHF_H_
#define _LIBIHF_H_

#include <stdint.h>

#define BUFMAX 1024 * 10
#define READSIZE 1024
#define WRITESIZE 1024

#define IHF_FIXLEN  4
#define IHF_VERSION 1

struct ihf_msg {
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
    MSG_TYPE_DATA = 5,
    MSG_TYPE_OK = 6,
    MSG_TYPE_ERR = 7
};
#define MSG_TYPE_MAX 7

uint8_t        *msg_pack(int, uint8_t *, int);
struct ihf_msg *msg_unpack(uint8_t *, int);

char **explode (char *, int, char *, int *);

#endif /* _LIBIHF_H_ */
