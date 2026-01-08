// SPDX-License-Identifier: CDDL-1.0

#ifndef _STREEBOG_IMPL_H
#define _STREEBOG_IMPL_H

#include <sys/streebog.h>

#ifdef __cplusplus
extern "C" {

#endif

typedef void (*streebog256_transform_f)(STREEBOG256_CTX * ctx,
                                        const uint8_t * block);

typedef struct {
    const char * name;
    streebog256_transform_f transform;

    boolean_t (*is_supported)(void);
} streebog256_ops_t;

extern const streebog256_ops_t * streebog256_get_ops(void);

#ifdef __cplusplus
}
#endif

#endif /* _STREEBOG_IMPL_H */
