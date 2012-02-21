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
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/select.h>

#include <sys/socket.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "libihf.h"

#define FIFO_OUTPUT "/tmp/output"
#define FIFO_INPUT  "/tmp/input"

int cmd_init(void) {
    int fifo_input, fifo_output;
    struct stat buf;

    if (stat(FIFO_INPUT, &buf) == 0)
        unlink(FIFO_INPUT);
    if (stat(FIFO_OUTPUT, &buf) == 0)
        unlink(FIFO_OUTPUT);

    fifo_input = mkfifo(FIFO_INPUT, O_RDONLY);
    fifo_output = mkfifo(FIFO_OUTPUT, O_WRONLY);
    if (fifo_input < 0 || fifo_output < 0) {
        fprintf(stderr, "error: main(): Couldn't open(r|w) pipe file\n");
        exit(1);
    }

    return 0;
}

int cmd_kill(void) {
    unlink(FIFO_INPUT);
    unlink(FIFO_OUTPUT);

    return 0;
}

int cmd_exec(uint8_t *cmd, int cmd_len) {
    char **argv;
    int argc;

    if (!cmd)
        return -1;

    argv = explode(cmd, cmd_len, " ", &argc);
    if (!argv)
        return -1;

    execv(argv[0], argv);

    return 0;
}

int cmd_read(void) {
    uint8_t *buf, *msg;
    int fd;
    int len;

    fd = open(FIFO_OUTPUT, O_RDONLY);
    if (fd <= 0)
        return -1;

    buf = malloc(sizeof(char) * BUFMAX);
    if (!buf) {
        fprintf(stderr, "Error allocating reading buffer !");
        return -1;
    }
    len = read(fd, &buf, BUFMAX);
    msg = msg_pack(MSG_TYPE_DATA, buf, len);
    if (!msg) {
        free(buf);
        return -1;
    }

    len = write(STDOUT_FILENO, msg, IHF_FIXLEN + len);
    if (len <= 0) {
        /* XXX handle error */
        return -1;
    }
    else if (len < IHF_FIXLEN + len) {
        /* XXX handle error */
    }

    free(buf);
    free(msg);
    close(fd);

    return 0;
}

int cmd_write(uint8_t *data, int data_len) {
    int len;
    int fd;

    if (!data)
        return -1;

    fd = open(FIFO_INPUT, O_WRONLY);
    if (fd <= 0)
        return -1;

    len = write(fd, data, data_len);
    if (len <= 0) {
        /* XXX send ERR */
        return -1;
    }
    else if (len < data_len) {
        /* XXX send ERR with writen size ? */
    }

    close(fd);

    return len;
}

int main(int argc, char *argv[]) {
    struct ihf_msg *msg = NULL;
    uint8_t *req = NULL;
    int ret = 0;
    int len;

    req = malloc(sizeof(char) * BUFMAX);
    if (!req) {
        fprintf(stderr, "cannot allocate receiving request buffer !\n");
        ret = -1;
        goto exit;
    }
    len = read(STDIN_FILENO, req, BUFMAX);

    msg = msg_unpack(req, len);
    if (!msg) {
        fprintf(stderr, "error unpacking message\n");
        ret = -1;
        goto exit;
    }
    switch (msg->type) {
        case MSG_TYPE_INIT:
            cmd_init();
            break;
        case MSG_TYPE_KILL:
            cmd_kill();
            break;
        case MSG_TYPE_EXEC:
            cmd_exec(msg->arg, msg->arglen);
            break;
        case MSG_TYPE_READ:
            cmd_read();
            break;
        case MSG_TYPE_WRITE:
            cmd_write(msg->arg, msg->arglen);
            break;
        default:
            fprintf(stderr, "unknown request type %d\n", msg->type);
            ret = -1;
            goto exit;
    }

exit:
    if (req)
        free(req);
    if (msg)
        free(msg);

    return ret;
}

