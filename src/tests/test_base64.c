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
#include <string.h>
#include <stdint.h>

#include "base64.h"

#define TEST_STR    "ag0 arg1 arg2 arg3 arg4\n"

void print_array_uint8_t (uint8_t *array, int n_elements) {
    int idx_array;

    if (!array || n_elements <= 0)
        return;

    for (idx_array = 0; idx_array < n_elements; idx_array++)
        printf("%02x ", array[idx_array]);
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

    printf("printing array...\n");
    print_array_uint8_t (buf, sz_buf - 1);

    printf("\nEncoding buffer ...\n");
    base64_encode_alloc(buf, sz_buf - 1, &b64_encoded);
    if (!b64_encoded) {
        fprintf(stderr, "error: Could not encode buffer\n");
        return -1;
    }

    printf("encoded: %s\n\n", b64_encoded);

    printf("Decoding buffer ...\n");
    base64_decode_ctx_init (&dctx);
    base64_decode_alloc_ctx(&dctx,
            b64_encoded, strlen(b64_encoded),
            &b64_decoded, &len_decoded);
    printf("len_decoded: %lu\n\n", len_decoded);

    printf("printing array...\n");
    print_array_uint8_t (b64_decoded, len_decoded);

    printf("comparing arrays...\n");
    if (memcmp(buf, b64_decoded, len_decoded))
        printf("Decoding failed\n");
    else
        printf("Decoding succeeded\n");

    return 0;
}

