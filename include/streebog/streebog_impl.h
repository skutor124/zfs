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

#ifndef _STREEBOG_IMPL_H
#define _STREEBOG_IMPL_H

#include <sys/streebog.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*streebog256_transform_f)(STREEBOG256_CTX *ctx, const uint8_t *block);

typedef struct streebog256_ops {
    const char *name;
    streebog256_transform_f transform;
    boolean_t (*is_supported)(void);
} streebog256_ops_t;

const streebog256_ops_t *streebog256_get_ops(void);

#ifdef __cplusplus
}
#endif

#endif /* _STREEBOG_IMPL_H */
