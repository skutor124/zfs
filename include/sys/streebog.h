// SPDX-License-Identifier: CDDL-1.0
/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or https://opensource.org/licenses/CDDL-1.0.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

#ifndef _SYS_STREEBOG_H
#define _SYS_STREEBOG_H

#ifdef _KERNEL
#include <sys/types.h>
#else
#include <stdint.h>
#include <stdlib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define STREEBOG256_OUT_LEN 32
#define STREEBOG_BLOCK_LEN  64

typedef struct streebog256_ctx {
    uint64_t h[8];
    uint64_t n[8];
    uint64_t s[8];
    uint8_t buf[STREEBOG_BLOCK_LEN];
    size_t buf_len;
    const void *ops;
} STREEBOG256_CTX;

void Streebog256_Init(STREEBOG256_CTX *ctx);
void Streebog256_Update(STREEBOG256_CTX *ctx, const void *data, size_t len);
void Streebog256_Final(const STREEBOG256_CTX *ctx, uint8_t out[STREEBOG256_OUT_LEN]);

extern void **streebog256_per_cpu_ctx;
extern void streebog256_per_cpu_ctx_init(void);
extern void streebog256_per_cpu_ctx_fini(void);

#ifdef __cplusplus
}
#endif

#endif /* _SYS_STREEBOG_H */
