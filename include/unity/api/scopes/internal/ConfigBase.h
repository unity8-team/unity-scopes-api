/*
 * Copyright (C) 2013 Canonical Ltd
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Michi Henning <michi.henning@canonical.com>
 */

#ifndef UNITY_API_SCOPES_INTERNAL_CONFIGBASE_H
#define UNITY_API_SCOPES_INTERNAL_CONFIGBASE_H

#include <unity/util/IniParser.h>

namespace unity
{

namespace util
{
class IniParser;
}

namespace api
{

namespace scopes
{

namespace internal
{

class ConfigBase
{
public:
    ConfigBase(std::string const& configfile);
    virtual ~ConfigBase() noexcept;

    unity::util::IniParser::SPtr parser() const noexcept;

protected:
    void throw_ex(::std::string const& reason) const;

private:
    unity::util::IniParser::SPtr parser_;
    std::string configfile_;
};

} // namespace internal

} // namespace scopes

} // namespace api

} // namespace unity

#endif