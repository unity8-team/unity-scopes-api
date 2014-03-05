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
 * Authored by: Jussi Pakkanen <jussi.pakkanen@canonical.com>
 */

#include <unity/scopes/internal/Logging.h>
#include <iostream>

namespace unity
{

namespace scopes
{

namespace internal
{

LogStream errlog;

LogStream::LogStream() {

}

LogGatherer LogStream::operator<<(const std::string &s) {
    LogGatherer l;
    l << s;
    return l;
}

LogGatherer::LogGatherer()
{

}

LogGatherer::~LogGatherer()
{
    if(strings.empty())
        return;
    try
    {
        for(const auto &i : strings)
        {
            std::cerr << i;
        }
        const std::string &last = strings.back();
        if(last.empty() or last.back() != '\n')
        {
            std::cerr << std::endl;
        }
    } catch(...) {
        // There's not much we can do in this case.
    }
}

LogGatherer& LogGatherer::operator<<(const std::string &s)
{
    strings.push_back(s);
    return *this;
}

} // namespace internal

} // namespace scopes

} // namespace unity
