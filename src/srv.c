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

#define FIFO_OUTPUT "/tmp/output"
#define FIFO_INPUT  "/tmp/input"

// exec command
int cmd_exec (struct ihf_pkt_s *pkt) {
    char **argv;

    // check args
    if (!pkt)
        return -1;

    // parse packet
    if (pkt->argn)
        return -1;
    argv = exploded(pkt->argn, strlen(pkt->argn), " ");
    if (!argv)
        return -1;

    // exec cmd
    execv(argv[0], argv);
}

// get result
int cmd_pull (struct cmd_s *cmd, void *data) {
}

//
int main (int argc, char *argv[]) {
    // fifo
    int fifo_input, fifo_output;
    // process
    pid_t pid;
    // return code for each func
    int retcode;

    // input pipe
    fifo_input = open(FIFO_INTPUT, O_RDONLY);
    if (fifo_input < 0) {
        fprintf(stderr, "error: main(): Couldn't open(r) pipe file\n");
        exit(1);
    }

    // output pipe
    fifo_output = open(FIFO_OUTPUT, O_WRONLY);
    if (retcode < 0) {
        fprintf(stderr, "error: main(): Couldn't open(w) pipe file\n");
        exit(1);
    }

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

    /*
    unlink("/tmp/input");
    unlink("/tmp/output");
    //*/

    return 0;
}

