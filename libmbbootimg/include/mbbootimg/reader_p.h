/*
 * Copyright (C) 2017-2018  Andrew Gunnerson <andrewgunnerson@gmail.com>
 *
 * This file is part of DualBootPatcher
 *
 * DualBootPatcher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DualBootPatcher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DualBootPatcher.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <optional>
#include <string>

#include <cstddef>

#include "mbcommon/common.h"

#include "mbbootimg/entry.h"
#include "mbbootimg/format.h"
#include "mbbootimg/header.h"

namespace mb
{
class File;

namespace bootimg::detail
{

class FormatReader
{
public:
    FormatReader() noexcept;
    virtual ~FormatReader() noexcept;

    MB_DISABLE_COPY_CONSTRUCT_AND_ASSIGN(FormatReader)
    MB_DEFAULT_MOVE_CONSTRUCT_AND_ASSIGN(FormatReader)

    virtual Format type() = 0;

    virtual oc::result<void>
    set_option(const char *key, const char *value);
    virtual oc::result<int>
    open(File &file, int best_bid) = 0;
    virtual oc::result<void>
    close(File &file);
    virtual oc::result<Header>
    read_header(File &file) = 0;
    virtual oc::result<Entry>
    read_entry(File &file) = 0;
    virtual oc::result<Entry>
    go_to_entry(File &file, std::optional<EntryType> entry_type);
    virtual oc::result<size_t>
    read_data(File &file, void *buf, size_t buf_size) = 0;
};

enum class ReaderState : uint8_t
{
    New     = 1u << 1,
    Header  = 1u << 2,
    Entry   = 1u << 3,
    Data    = 1u << 4,
};
MB_DECLARE_FLAGS(ReaderStates, ReaderState)
MB_DECLARE_OPERATORS_FOR_FLAGS(ReaderStates)

}
}
