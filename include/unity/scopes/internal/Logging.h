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

#ifndef UNITY_SCOPES_INTERNAL_LOGGING_H
#define UNITY_SCOPES_INTERNAL_LOGGING_H

#include <string>
#include <vector>
#include <unity/util/NonCopyable.h>

namespace unity
{

namespace scopes
{

namespace internal
{

class LogGatherer;

class LogStream final {
    NONCOPYABLE(LogStream);
public:
    LogStream();
    LogGatherer operator<<(const std::string &s);
    LogGatherer operator<<(const int i);
    LogGatherer operator<<(const char *msg);
    LogGatherer operator<<(const bool i);
};

class LogGatherer final {

public:

    LogGatherer();
    ~LogGatherer();
    LogGatherer& operator<<(const std::string &s);
    LogGatherer& operator<<(const int i);
    LogGatherer& operator<<(const bool i);
    LogGatherer& operator<<(const char *msg);

private:
    std::vector<std::string> strings;
};

extern LogStream errlog;

} // namespace internal

} // namespace scopes

} // namespace unity

#endif