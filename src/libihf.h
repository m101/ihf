#ifndef _LIBIHF_H_
#define _LIBIHF_H_

#include <stdint.h>

struct ihf_pkt_s {
    uint8_t version:
    uint8_t type:
    uint16_t length:
    uint8_t *argn:
};

#endif /* _LIBIHF_H_ */
