#include <stdio.h>
#include <stdlib.h>

#include "libihf.h"

// types
enum {
    PKT_TYPE_INIT = 0,
    PKT_TYPE_KILL = 1,
    PKT_TYPE_READ = 2,
    PKT_TYPE_WRITE = 3,
    PKT_TYPE_EXEC = 4,
    PKT_TYPE_DATA = 5
};

