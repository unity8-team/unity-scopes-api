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

#include <unity/scopes/internal/zmq_middleware/ZmqPublisher.h>

namespace unity
{

namespace scopes
{

namespace internal
{

namespace zmq_middleware
{

ZmqPublisher::ZmqPublisher(std::string const& endpoint, std::string const& topic)
    : endpoint_(endpoint)
    , topic_(topic)
    , thread_(std::thread(&ZmqPublisher::publisher_thread, this))
{
}

ZmqPublisher::~ZmqPublisher()
{
}

void ZmqPublisher::publisher_thread()
{

}

} // namespace zmq_middleware

} // namespace internal

} // namespace scopes

} // namespace unity
