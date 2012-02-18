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
    int retcode;
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
}

int cmd_kill(void) {
    unlink(FIFO_INPUT);
    unlink(FIFO_OUTPUT);
}

int cmd_exec(char *cmd, int cmd_len) {
    char **argv;

    if (!cmd)
        return -1;

    /* XXX use cmd_len */
    argv = explode(cmd, strlen(cmd), " ");
    if (!argv)
        return -1;

    execv(argv[0], argv);
}

int cmd_read(void) {
    int retcode;
    int c;
    char **argv;
    FILE *fp;

    fp = open(FIFO_OUTPUT, "r");
    if (!fp)
        return -1;

    while (fread(&c, 1, 1, fp) > 0)
        write(STDOUT_FILENO, &c, 1);

    fclose(fp);

    return 0;
}

int cmd_write(char *data, int data_len) {
    int retcode;
    int c;
    char **argv;
    FILE *fp;

    if (!data)
        return -1;

    /* XXX use data_len */
    fp = open(FIFO_INPUT, "w");
    if (!fp)
        return -1;

    while (read(STDIN_FILENO, &c, 1) > 0)
        fwrite(&c, 1, 1, fp);

    fclose(fp);

    return 0;
}

int main(int argc, char *argv[]) {
    struct ihf_msg *msg;
    pid_t pid;
    char buf[1024];
    char *req = NULL;
    int len = 0;
    int l;

    while (l = read(STDIN_FILENO, buf, 1024) > 0) {
        len += l;
        req = realloc(req, len);
        if (!req) {
            fprintf(stderr, "Error allocating receive buffer !\n");
            return -1;
        }
        /* XXX limit size */
    }

    msg = msg_unpack(req, len);
    switch (msg->type) {
        case MSG_TYPE_INIT:
            cmd_init();
        case MSG_TYPE_KILL:
            cmd_kill();
        case MSG_TYPE_EXEC:
            cmd_exec(msg->arg, msg->arglen);
        case MSG_TYPE_READ:
            cmd_read();
        case MSG_TYPE_WRITE:
            cmd_write(msg->arg, msg->arglen);
    }

    pid = fork();
    /* parent */
    if (pid > 0) {
    }
    /* child */
    else if (pid == 0) {
    }
    /* error */
    else {
    }

    return 0;
}

