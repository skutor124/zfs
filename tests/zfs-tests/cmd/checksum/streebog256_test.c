// SPDX-License-Identifier: CDDL-1.0
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/streebog.h>

static void hex_to_bin(const char * in, uint8_t * out, size_t len) {
    for (size_t i = 0; i < len; i++) {
        unsigned int v;
        sscanf(&in[i * 2], "%02x", &v);
        out[i] = (uint8_t) v;
    }
}

static void bin_to_hex(const uint8_t * in, size_t n, char * out) {
    static const char * hexd = "0123456789abcdef";
    for (size_t i = 0; i < n; i++) {
        out[i * 2 + 0] = hexd[in[i] >> 4];
        out[i * 2 + 1] = hexd[in[i] & 0xF];
    }
    out[n * 2] = '\0';
}

typedef struct {
    const char * name;
    const char * msg_str;
    const char * msg_hex;
    const char * expect_hex;
} tv_t;

static const tv_t tests[] = {
    {
        .name = "M_empty (empty)",
        .msg_str = "",
        .expect_hex = "3f539a213e97c802cc229d474c6aa32a825a360b2a933a949fd925208d9ce1bb"
    },
    {
        .name = "M1 (digits)",
        .msg_str = "012345678901234567890123456789012345678901234567890123456789012",
        .expect_hex = "9d151eefd8590b89daa6ba6cb74af9275dd051026bb149a452fd84e5e57b5500"
    },
    {
        .name = " M1_my (digits long)",
        .msg_str =
        "01234567890123456789012345678901234567890123456789012345678901201234567890123456789012345678901234567890123456789",
        .expect_hex = "7b1d8f8ffdbe823dea01e256f3055174a82e09971ff0bc02c927e615f2e1dd79"
    },
    {
        .name = " M1_my (string)",
        .msg_str = "123",
        .expect_hex = "a78dc2b36dac63abe7b8f01789c3a75626f1b78db9183edfadeb1e0bfbcef5d4"
    },
    {
        .name = " M1_my (hex)",
        .msg_hex = "313233",
        .expect_hex = "a78dc2b36dac63abe7b8f01789c3a75626f1b78db9183edfadeb1e0bfbcef5d4"
    }
};

int main(void) {
    int fails = 0;
    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        const tv_t * t = &tests[i];
        STREEBOG256_CTX ctx;
        uint8_t out[STREEBOG256_OUT_LEN];
        char got[STREEBOG256_OUT_LEN * 2 + 1];
        uint8_t * input_buf = NULL;
        size_t input_len = 0;

        if (t->msg_str) {
            input_len = strlen(t->msg_str);
            input_buf = (uint8_t *) t->msg_str;
        } else if (t->msg_hex) {
            input_len = strlen(t->msg_hex) / 2;
            input_buf = malloc(input_len);
            hex_to_bin(t->msg_hex, input_buf, input_len);
        }

        Streebog256_Init(&ctx);
        Streebog256_Update(&ctx, input_buf, input_len);
        Streebog256_Final(&ctx, out);
        bin_to_hex(out, sizeof(out), got);

        int ok = (strlen(t->expect_hex) == strlen(got)) &&
                 (strcasecmp(t->expect_hex, got) == 0);
        printf("[%s] %s\n", ok ? "OK" : "FAIL", t->name);
        if (!ok) {
            printf("  got:  %s\n", got);
            printf("  exp:  %s\n", t->expect_hex);
            fails++;
        }

        if (t->msg_hex && input_buf) {
            free(input_buf);
        }
    }
    return fails ? 1 : 0;
}



