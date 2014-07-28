/*
 * Copyright (C) 2014 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Marcus Tomlinson <marcus.tomlinson@canonical.com>
 */

#include <unity/scopes/CompletionDetails.h>
#include <unity/scopes/internal/CompletionDetailsImpl.h>

namespace unity
{

namespace scopes
{

/// @cond
CompletionDetails::CompletionDetails(CompletionDetails const& other)
    : p(new internal::CompletionDetailsImpl(*other.p.get()))
{
}

CompletionDetails::CompletionDetails(CompletionDetails&&) = default;

CompletionDetails& CompletionDetails::operator=(CompletionDetails const& other)
{
    if (this != &other)
    {
        p.reset(new internal::CompletionDetailsImpl(*other.p.get()));
    }
    return *this;
}

CompletionDetails& CompletionDetails::operator=(CompletionDetails&&) = default;

CompletionDetails::~CompletionDetails() = default;
/// @endcond

} // namespace scopes

} // namespace unity
