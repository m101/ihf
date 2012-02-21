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
