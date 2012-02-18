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

// cmd structure
struct cmd_s {
    //
    char *arg;
    int len;
};

// exec command
int cmd_exec (struct cmd_s *cmd, void *data) {
}

// get result
int cmd_pull (struct cmd_s *cmd, void *data) {
}

//
int main (int argc, char *argv[]) {
    // socket
    int sockfd;

    // process
    pid_t pid;
    // return code for each func
    int retcode;

    // input pipe
    retcode = mkfifo(FIFO_INPUT, O_RDONLY);
    if (retcode < 0) {
        fprintf(stderr, "error: main(): Couldn't create pipe file\n");
        exit(1);
    }

    // output pipe
    retcode = mkfifo(FIFO_OUTPUT, O_WRONLY);
    if (retcode < 0) {
        fprintf(stderr, "error: main(): Couldn't create pipe file\n");
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

