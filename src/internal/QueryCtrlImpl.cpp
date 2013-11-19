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

#include <scopes/internal/QueryCtrlImpl.h>

#include <scopes/internal/MiddlewareBase.h>
#include <scopes/internal/MWQueryCtrl.h>
#include <scopes/internal/MWReply.h>
#include <scopes/internal/RuntimeImpl.h>
#include <scopes/QueryCtrl.h>
#include <scopes/ScopeExceptions.h>

#include <cassert>

using namespace std;

namespace unity
{

namespace api
{

namespace scopes
{

namespace internal
{

QueryCtrlImpl::QueryCtrlImpl(MWQueryCtrlProxy const& ctrl_proxy, MWReplyProxy const& reply_proxy) :
    ctrl_proxy_(ctrl_proxy),
    reply_proxy_(reply_proxy)
{
    assert(ctrl_proxy);
    assert(reply_proxy);
    // We remember the reply proxy so, when the query is cancelled, we can
    // inform the reply object belonging to this query that the query is finished.
}

QueryCtrlImpl::~QueryCtrlImpl() noexcept
{
}

void QueryCtrlImpl::cancel()
{
    try
    {
        // Forward cancellation down-stream to the query. This does not block.
        ctrl_proxy_->cancel();

        // Indicate (to ourselves) that this query is complete. Calling via the MWReplyProxy ensures
        // the finished() call will be processed by a seperate server-side thread,
        // so we cannot block here.
        reply_proxy_->finished();
    }
    catch (MiddlewareException const& e)
    {
        // TODO: log error
    }
}

QueryCtrlProxy QueryCtrlImpl::create(MWQueryCtrlProxy const& ctrl_proxy, MWReplyProxy const& reply_proxy)
{
    return QueryCtrlProxy(new QueryCtrl(new QueryCtrlImpl(ctrl_proxy, reply_proxy)));
}

} // namespace internal

} // namespace scopes

} // namespace api

} // namespace unity