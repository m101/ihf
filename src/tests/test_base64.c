#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "base64.h"

#define TEST_STR    "ag0 arg1 arg2 arg3 arg4\n"

void print_array_uint8_t (uint8_t *array, int n_elements) {
    int idx_array;

    if (!array || n_elements <= 0)
        return;

    for (idx_array = 0; idx_array < n_elements; idx_array++)
        printf("%08x ", array[idx_array]);
    putchar('\n');
}

int main(int argc, char *argv[]) {
    int idx_buf, sz_buf;
    char *buf;
    // b64
    struct base64_decode_context dctx;
    char *b64_encoded, *b64_decoded;
    size_t len_decoded;

    sz_buf = 256 + strlen(TEST_STR) + 1;

    buf = calloc(sz_buf, sizeof(*buf));
    if (!buf) {
        fprintf(stderr, "error: Could not alloc buffer\n");
        return -1;
    }

    for (idx_buf = 0; idx_buf < 256; idx_buf++)
        buf[idx_buf] = idx_buf;
    memcpy(buf + 256, TEST_STR, strlen(TEST_STR));

    print_array_uint8_t (buf, sz_buf - 1);

    base64_encode_alloc(buf, sz_buf - 1, &b64_encoded);
    if (!b64_encoded) {
        fprintf(stderr, "error: Could not encode buffer\n");
        return -1;
    }

    printf("encoded: %s\n", b64_encoded);

    base64_decode_alloc_ctx(&dctx,
            b64_encoded, strlen(b64_encoded),
            &b64_decoded, &len_decoded);

    print_array_uint8_t (b64_decoded, len_decoded);

    return 0;
}

