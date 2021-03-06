/*
 * Copyright (C) 2013 Canonical Ltd
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
 * Authored by: Michi Henning <michi.henning@canonical.com>
 */

#include <unity/scopes/internal/zmq_middleware/ZmqQueryCtrl.h>

using namespace std;

namespace unity
{

namespace scopes
{

namespace internal
{

namespace zmq_middleware
{

/*

interface QueryCtrl
{
    void cancel();  // Oneway
    void destroy(); // Oneway
};

*/

ZmqQueryCtrl::ZmqQueryCtrl(ZmqMiddleware* mw_base, string const& endpoint, string const& identity, string const& category) :
    MWObjectProxy(mw_base),
    ZmqObjectProxy(mw_base, endpoint, identity, category, RequestMode::Oneway),
    MWQueryCtrl(mw_base)
{
}

ZmqQueryCtrl::~ZmqQueryCtrl()
{
}

void ZmqQueryCtrl::cancel()
{
    capnp::MallocMessageBuilder request_builder;
    make_request_(request_builder, "cancel");

    auto future = mw_base()->oneway_pool()->submit([&] { return this->invoke_oneway_(request_builder); });
    future.get();
}

void ZmqQueryCtrl::destroy()
{
    capnp::MallocMessageBuilder request_builder;
    make_request_(request_builder, "destroy");

    auto future = mw_base()->oneway_pool()->submit([&] { return this->invoke_oneway_(request_builder); });
    future.get();
}

} // namespace zmq_middleware

} // namespace internal

} // namespace scopes

} // namespace unity
