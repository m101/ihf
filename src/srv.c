#include <stdio.h>
#include <stdlib.h>

//
#include <unistd.h>
#include <sys/select.h>

// sockets
#include <sys/socket.h>

//
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "libihf.h"

#define FIFO_OUTPUT "/tmp/output"
#define FIFO_INPUT  "/tmp/input"

int cmd_init (struct ihf_msg_s *pkt) {
    // fifo
    int fifo_input, fifo_output;
    // return code for each func
    int retcode;
    struct stat buf;

    if (stat(FIFO_INPUT, &buf) == 0)
        unlink(FIFO_INPUT);
    if (stat(FIFO_OUTPUT, &buf) == 0)
        unlink(FIFO_OUTPUT);

    // input or output pipe
    fifo_input = mkfifo(FIFO_INPUT, O_RDONLY);
    fifo_output = mkfifo(FIFO_OUTPUT, O_WRONLY);
    if (fifo_input < 0 || fifo_output < 0) {
        fprintf(stderr, "error: main(): Couldn't open(r|w) pipe file\n");
        exit(1);
    }
}

int cmd_kill () {
    unlink(FIFO_INPUT);
    unlink(FIFO_OUTPUT);
}

// exec command
int cmd_exec (struct ihf_msg_s *pkt) {
    char **argv;

    // check args
    if (!pkt)
        return -1;

    // parse packet
    if (pkt->arg)
        return -1;
    argv = explode(pkt->arg, strlen(pkt->arg), " ");
    if (!argv)
        return -1;

    // exec cmd
    execv(argv[0], argv);
}

// get result
int cmd_read (struct ihf_msg_s *pkt) {
    int retcode;
    int c;
    char **argv;
    FILE *fp;

    if (!pkt)
        return -1;

    fp = open(FIFO_OUTPUT, "r");
    if (!fp)
        return -1;

    while (fread(&c, 1, 1, fp) > 0)
        write(STDOUT_FILENO, &c, 1);

    fclose(fp);

    return 0;
}

// send data to input
int cmd_write (struct ihf_msg_s *pkt) {
    int retcode;
    int c;
    char **argv;
    FILE *fp;

    if (!pkt)
        return -1;

    fp = open(FIFO_INPUT, "w");
    if (!fp)
        return -1;

    while (read(STDIN_FILENO, &c, 1) > 0)
        fwrite(&c, 1, 1, fp);

    fclose(fp);

    return 0;
}

//
int main (int argc, char *argv[]) {
    // process
    pid_t pid;

    // create process
    pid = fork();
    // parent
    if (pid > 0) {
    }
    // child
    else if (pid == 0) {
    }
    // error
    else {
    }

    return 0;
}

