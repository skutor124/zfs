// SPDX-License-Identifier: CDDL-1.0

#include <sys/zfs_context.h>
#include <sys/zfs_impl.h>
#include <sys/streebog.h>
#include <streebog/streebog_impl.h>

extern const streebog256_ops_t * streebog256_get_ops(void);

extern const streebog256_ops_t streebog256_generic_impl;

static const streebog256_ops_t * const streebog256_impls[] = {
    &streebog256_generic_impl,
};

#define IMPL_NAME       "streebog256"
#define IMPL_OPS_T      streebog256_ops_t
#define IMPL_ARRAY      streebog256_impls
#define IMPL_GET_OPS    streebog256_get_ops
#define ZFS_IMPL_OPS    zfs_streebog256_ops

#include <generic_impl.c>

#ifdef _KERNEL

#define	IMPL_FMT(impl, i)	(((impl) == (i)) ? "[%s] " : "%s ")

#if defined(__linux__)

static int
streebog256_param_get(char * buffer, zfs_kernel_param_t * unused) {
    const uint32_t impl = IMPL_READ(generic_impl_chosen);
    char * fmt;
    int cnt = 0;

    fmt = IMPL_FMT(impl, IMPL_CYCLE);
    cnt += sprintf(buffer + cnt, fmt, "cycle");

    fmt = IMPL_FMT(impl, IMPL_FASTEST);
    cnt += sprintf(buffer + cnt, fmt, "fastest");

    generic_impl_init();
    for (uint32_t i = 0; i < generic_supp_impls_cnt; ++i) {
        fmt = IMPL_FMT(impl, i);
        cnt += sprintf(buffer + cnt, fmt,
                       generic_supp_impls[i]->name);
    }

    return (cnt);
}

static int
streebog256_param_set(const char * val, zfs_kernel_param_t * unused) {
    (void) unused;
    return (generic_impl_setname(val));
}

#elif defined(__FreeBSD__)

#include <sys/sbuf.h>

static int
streebog256_param(ZFS_MODULE_PARAM_ARGS) {
    int err;

    generic_impl_init();
    if (req->newptr == NULL) {
        const uint32_t impl = IMPL_READ(generic_impl_chosen);
        const int init_buflen = 64;
        const char * fmt;
        struct sbuf * s;

        s = sbuf_new_for_sysctl(NULL, NULL, init_buflen, req);

        fmt = IMPL_FMT(impl, IMPL_CYCLE);
        (void) sbuf_printf(s, fmt, "cycle");

        fmt = IMPL_FMT(impl, IMPL_FASTEST);
        (void) sbuf_printf(s, fmt, "fastest");

        for (uint32_t i = 0; i < generic_supp_impls_cnt; ++i) {
            fmt = IMPL_FMT(impl, i);
            (void) sbuf_printf(s, fmt, generic_supp_impls[i]->name);
        }

        err = sbuf_finish(s);
        sbuf_delete(s);

        return (err);
    }

    char buf[16];

    err = sysctl_handle_string(oidp, buf, sizeof (buf), req);
    if (err) {
        return (err);
    }

    return (-generic_impl_setname(buf));
}
#endif

#undef IMPL_FMT

ZFS_MODULE_VIRTUAL_PARAM_CALL(zfs, zfs_, streebog256_impl,
                              streebog256_param_set, streebog256_param_get, ZMOD_RW,
	"Select Streebog-256 implementation.");
#endif
