// Copyright (c) 2025-present The Briskcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BRISKCOIN_UTIL_BYTE_UNITS_H
#define BRISKCOIN_UTIL_BYTE_UNITS_H

#include <util/overflow.h>

#include <stdexcept>

//! Overflow-safe conversion of MiB to bytes.
constexpr size_t operator""_MiB(unsigned long long mebibytes)
{
    auto bytes{CheckedLeftShift(mebibytes, 20)};
    if (!bytes || *bytes > std::numeric_limits<size_t>::max()) {
        throw std::overflow_error("MiB value too large for size_t byte conversion");
    }
    return *bytes;
}

#endif // BRISKCOIN_UTIL_BYTE_UNITS_H
