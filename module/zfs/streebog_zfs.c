// SPDX-License-Identifier: CDDL-1.0

#include <sys/zfs_context.h>
#include <sys/zio_checksum.h>
#include <sys/streebog.h>
#include <sys/abd.h>

static int
streebog_incremental(void * buf, size_t size, void * arg) {
    STREEBOG256_CTX * ctx = arg;
    Streebog256_Update(ctx, buf, size);
    return (0);
}

void
abd_checksum_streebog256_native(abd_t * abd, uint64_t size,
                                const void * ctx_template, zio_cksum_t * zcp) {
    (void) ctx_template;
    STREEBOG256_CTX ctx;
    zio_cksum_t tmp;

    Streebog256_Init(&ctx);
    (void) abd_iterate_func(abd, 0, size, streebog_incremental, &ctx);
    Streebog256_Final(&ctx, (uint8_t *) &tmp);
    zcp->zc_word[0] = BE_64(tmp.zc_word[0]);
    zcp->zc_word[1] = BE_64(tmp.zc_word[1]);
    zcp->zc_word[2] = BE_64(tmp.zc_word[2]);
    zcp->zc_word[3] = BE_64(tmp.zc_word[3]);
}

void
abd_checksum_streebog256_byteswap(abd_t * abd, uint64_t size,
                                  const void * ctx_template, zio_cksum_t * zcp) {
    zio_cksum_t tmp;
    abd_checksum_streebog256_native(abd, size, ctx_template, &tmp);
    zcp->zc_word[0] = BSWAP_64(tmp.zc_word[0]);
    zcp->zc_word[1] = BSWAP_64(tmp.zc_word[1]);
    zcp->zc_word[2] = BSWAP_64(tmp.zc_word[2]);
    zcp->zc_word[3] = BSWAP_64(tmp.zc_word[3]);
}

void *
abd_checksum_streebog256_tmpl_init(const zio_cksum_salt_t * salt) {
    (void) salt;
    return (NULL);
}

void
abd_checksum_streebog256_tmpl_free(void * ctx_template) {
    (void) ctx_template;
}
