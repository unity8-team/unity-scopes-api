/*
 * Copyright © 2014 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3,
 * as published by the Free Software Foundation.
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
#include <unity/UnityExceptions.h>
#include <unity/scopes/Variant.h>

#include <gtest/gtest.h>
#include <memory>
#include <algorithm>

using namespace testing;
using unity::scopes::internal::errlog;

namespace
{

class LoggingTest : public Test
{
public:
    LoggingTest()
    {
    }

};

TEST_F(LoggingTest, basic)
{
    std::string msg("Second message to stderr.");
    errlog << "First message to stderr.";
    errlog << msg;
    errlog << "Piecewise " << "message " << "to stderr.\n";
    errlog << 1 << " is the loneliest number. Not " << 2 << ".\n";
    errlog << "True is " << true << " and False is " << false << ".";
}


} // namespace
