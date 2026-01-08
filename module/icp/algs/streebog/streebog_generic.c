// SPDX-License-Identifier: CDDL-1.0

#include <sys/zfs_context.h>
#include <sys/streebog.h>
#include <streebog/streebog_impl.h>

extern const uint64_t streebog_C[12][8];

extern const unsigned long long streebog_LPS_table[8][256];

#define X(x, y, z) { \
    (z)[0] = (x)[0] ^ (y)[0]; \
    (z)[1] = (x)[1] ^ (y)[1]; \
    (z)[2] = (x)[2] ^ (y)[2]; \
    (z)[3] = (x)[3] ^ (y)[3]; \
    (z)[4] = (x)[4] ^ (y)[4]; \
    (z)[5] = (x)[5] ^ (y)[5]; \
    (z)[6] = (x)[6] ^ (y)[6]; \
    (z)[7] = (x)[7] ^ (y)[7]; \
}

#define XLPS(x, y, data) { \
    uint64_t r0, r1, r2, r3, r4, r5, r6, r7; \
    \
    r0 = (x)[0] ^ (y)[0]; \
    r1 = (x)[1] ^ (y)[1]; \
    r2 = (x)[2] ^ (y)[2]; \
    r3 = (x)[3] ^ (y)[3]; \
    r4 = (x)[4] ^ (y)[4]; \
    r5 = (x)[5] ^ (y)[5]; \
    r6 = (x)[6] ^ (y)[6]; \
    r7 = (x)[7] ^ (y)[7]; \
    \
    (data)[0] = streebog_LPS_table[0][r0 & 0xFF] ^ \
                streebog_LPS_table[1][r1 & 0xFF] ^ \
                streebog_LPS_table[2][r2 & 0xFF] ^ \
                streebog_LPS_table[3][r3 & 0xFF] ^ \
                streebog_LPS_table[4][r4 & 0xFF] ^ \
                streebog_LPS_table[5][r5 & 0xFF] ^ \
                streebog_LPS_table[6][r6 & 0xFF] ^ \
                streebog_LPS_table[7][r7 & 0xFF]; \
    (data)[1] = streebog_LPS_table[0][(r0 >> 8) & 0xFF] ^ \
                streebog_LPS_table[1][(r1 >> 8) & 0xFF] ^ \
                streebog_LPS_table[2][(r2 >> 8) & 0xFF] ^ \
                streebog_LPS_table[3][(r3 >> 8) & 0xFF] ^ \
                streebog_LPS_table[4][(r4 >> 8) & 0xFF] ^ \
                streebog_LPS_table[5][(r5 >> 8) & 0xFF] ^ \
                streebog_LPS_table[6][(r6 >> 8) & 0xFF] ^ \
                streebog_LPS_table[7][(r7 >> 8) & 0xFF]; \
    (data)[2] = streebog_LPS_table[0][(r0 >> 16) & 0xFF] ^ \
                streebog_LPS_table[1][(r1 >> 16) & 0xFF] ^ \
                streebog_LPS_table[2][(r2 >> 16) & 0xFF] ^ \
                streebog_LPS_table[3][(r3 >> 16) & 0xFF] ^ \
                streebog_LPS_table[4][(r4 >> 16) & 0xFF] ^ \
                streebog_LPS_table[5][(r5 >> 16) & 0xFF] ^ \
                streebog_LPS_table[6][(r6 >> 16) & 0xFF] ^ \
                streebog_LPS_table[7][(r7 >> 16) & 0xFF]; \
    (data)[3] = streebog_LPS_table[0][(r0 >> 24) & 0xFF] ^ \
                streebog_LPS_table[1][(r1 >> 24) & 0xFF] ^ \
                streebog_LPS_table[2][(r2 >> 24) & 0xFF] ^ \
                streebog_LPS_table[3][(r3 >> 24) & 0xFF] ^ \
                streebog_LPS_table[4][(r4 >> 24) & 0xFF] ^ \
                streebog_LPS_table[5][(r5 >> 24) & 0xFF] ^ \
                streebog_LPS_table[6][(r6 >> 24) & 0xFF] ^ \
                streebog_LPS_table[7][(r7 >> 24) & 0xFF]; \
    (data)[4] = streebog_LPS_table[0][(r0 >> 32) & 0xFF] ^ \
                streebog_LPS_table[1][(r1 >> 32) & 0xFF] ^ \
                streebog_LPS_table[2][(r2 >> 32) & 0xFF] ^ \
                streebog_LPS_table[3][(r3 >> 32) & 0xFF] ^ \
                streebog_LPS_table[4][(r4 >> 32) & 0xFF] ^ \
                streebog_LPS_table[5][(r5 >> 32) & 0xFF] ^ \
                streebog_LPS_table[6][(r6 >> 32) & 0xFF] ^ \
                streebog_LPS_table[7][(r7 >> 32) & 0xFF]; \
    (data)[5] = streebog_LPS_table[0][(r0 >> 40) & 0xFF] ^ \
                streebog_LPS_table[1][(r1 >> 40) & 0xFF] ^ \
                streebog_LPS_table[2][(r2 >> 40) & 0xFF] ^ \
                streebog_LPS_table[3][(r3 >> 40) & 0xFF] ^ \
                streebog_LPS_table[4][(r4 >> 40) & 0xFF] ^ \
                streebog_LPS_table[5][(r5 >> 40) & 0xFF] ^ \
                streebog_LPS_table[6][(r6 >> 40) & 0xFF] ^ \
                streebog_LPS_table[7][(r7 >> 40) & 0xFF]; \
    (data)[6] = streebog_LPS_table[0][(r0 >> 48) & 0xFF] ^ \
                streebog_LPS_table[1][(r1 >> 48) & 0xFF] ^ \
                streebog_LPS_table[2][(r2 >> 48) & 0xFF] ^ \
                streebog_LPS_table[3][(r3 >> 48) & 0xFF] ^ \
                streebog_LPS_table[4][(r4 >> 48) & 0xFF] ^ \
                streebog_LPS_table[5][(r5 >> 48) & 0xFF] ^ \
                streebog_LPS_table[6][(r6 >> 48) & 0xFF] ^ \
                streebog_LPS_table[7][(r7 >> 48) & 0xFF]; \
    (data)[7] = streebog_LPS_table[0][(r0 >> 56) & 0xFF] ^ \
                streebog_LPS_table[1][(r1 >> 56) & 0xFF] ^ \
                streebog_LPS_table[2][(r2 >> 56) & 0xFF] ^ \
                streebog_LPS_table[3][(r3 >> 56) & 0xFF] ^ \
                streebog_LPS_table[4][(r4 >> 56) & 0xFF] ^ \
                streebog_LPS_table[5][(r5 >> 56) & 0xFF] ^ \
                streebog_LPS_table[6][(r6 >> 56) & 0xFF] ^ \
                streebog_LPS_table[7][(r7 >> 56) & 0xFF]; \
}

#define ROUND(i, Ki, data) { \
    XLPS(Ki, streebog_C[i], Ki); \
    XLPS(Ki, data, data); \
}

static void
g(uint64_t * h, const uint64_t * N, const uint64_t * m) {
    uint64_t Ki[8], data[8];

    XLPS(h, N, data);

    memcpy(Ki, data, sizeof(Ki));

    XLPS(Ki, m, data);

    for (int i = 0; i < 11; i++)
        ROUND(i, Ki, data);

    XLPS(Ki, streebog_C[11], Ki);
    X(Ki, data, data);

    X(data, h, data);
    X(data, m, h);
}

static void
add512(uint64_t * r, const uint64_t * x, const uint64_t * y) {
    unsigned __int128 sum = 0;

    for (int i = 0; i < 8; i++) {
        sum += (unsigned __int128) x[i] + y[i];
        r[i] = (uint64_t) sum;
        sum >>= 64;
    }
}

static boolean_t streebog_supported(void) {
    return (B_TRUE);
}

static void streebog256_transform_generic(STREEBOG256_CTX * ctx,
                                          const uint8_t * block) {
    uint64_t m[8];
    memcpy(m, block, 64);

    g(ctx->h, ctx->n, m);

    {
        unsigned __int128 sum = (unsigned __int128) ctx->n[0] + 512;
        ctx->n[0] = (uint64_t) sum;
        sum >>= 64;
        for (int i = 1; i < 8 && sum; i++) {
            sum += ctx->n[i];
            ctx->n[i] = (uint64_t) sum;
            sum >>= 64;
        }
    }

    add512(ctx->s, ctx->s, m);
}

const streebog256_ops_t streebog256_generic_impl = {
    .name = "generic",
    .transform = streebog256_transform_generic,
    .is_supported = streebog_supported,
};

void ** streebog256_per_cpu_ctx;

void streebog256_per_cpu_ctx_init(void) {
    streebog256_per_cpu_ctx = kmem_zalloc(boot_ncpus * sizeof(void *), KM_SLEEP);
}

void streebog256_per_cpu_ctx_fini(void) {
    for (int i = 0; i < boot_ncpus; i++) {
        if (streebog256_per_cpu_ctx[i])
            kmem_free(streebog256_per_cpu_ctx[i], sizeof(STREEBOG256_CTX));
    }
    kmem_free(streebog256_per_cpu_ctx, boot_ncpus * sizeof(void *));
}

static void streebog256_iv(uint64_t h[8]) {
    for (int i = 0; i < 8; i++) h[i] = 0x0101010101010101ULL;
}

void Streebog256_Init(STREEBOG256_CTX * ctx) {
    memset(ctx, 0, sizeof (*ctx));
    streebog256_iv(ctx->h);
    ctx->ops = streebog256_get_ops();
}

void Streebog256_Update(STREEBOG256_CTX * ctx, const void * data, size_t len) {
    const uint8_t * p = (const uint8_t *) data;
    const streebog256_ops_t * ops = (const streebog256_ops_t *) ctx->ops;

    while (len) {
        size_t take = MIN(len, (size_t)(STREEBOG_BLOCK_LEN - ctx->buf_len));
        memcpy(ctx->buf + ctx->buf_len, p, take);
        ctx->buf_len += take;
        p += take;
        len -= take;

        if (ctx->buf_len == STREEBOG_BLOCK_LEN) {
            ops->transform(ctx, ctx->buf);
            ctx->buf_len = 0;
        }
    }
}

void Streebog256_Final(const STREEBOG256_CTX * cctx, uint8_t out[STREEBOG256_OUT_LEN]) {
    STREEBOG256_CTX ctx = *cctx;
    uint64_t buf_len_bits[8] = {0};
    uint64_t m[8];
    uint64_t zero[8] = {0};

    buf_len_bits[0] = ctx.buf_len * 8;

    if (ctx.buf_len < STREEBOG_BLOCK_LEN) {
        memset(ctx.buf + ctx.buf_len, 0, STREEBOG_BLOCK_LEN - ctx.buf_len);
        ctx.buf[ctx.buf_len] = 0x01;
    }

    memcpy(m, ctx.buf, 64);

    g(ctx.h, ctx.n, m);

    add512(ctx.n, ctx.n, buf_len_bits);

    add512(ctx.s, ctx.s, m);

    g(ctx.h, zero, ctx.n);

    g(ctx.h, zero, ctx.s);

    memcpy(out, &ctx.h[4], 32);
}
