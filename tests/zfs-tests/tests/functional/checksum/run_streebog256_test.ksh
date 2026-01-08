#!/bin/ksh -p
# SPDX-License-Identifier: CDDL-1.0

. $STF_SUITE/include/libtest.shlib

#
# Description:
# Run the tests for the Streebog-256 hash algorithm.
#

log_assert "Run the tests for the Streebog-256 hash algorithm."

log_must streebog256_test

log_pass "Streebog-256 tests passed."
