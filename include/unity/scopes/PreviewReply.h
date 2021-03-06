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

#pragma once

#include <unity/scopes/ColumnLayout.h>
#include <unity/scopes/PreviewReplyProxyFwd.h>
#include <unity/scopes/PreviewWidget.h>
#include <unity/scopes/Reply.h>

#include <string>

namespace unity
{
namespace scopes
{
/**
\brief Allows the results of a preview to be sent to the preview requester.
*/

class PreviewReply : public virtual Reply
{
public:
    /**
    \brief Registers a list of column layouts for the current preview.

    Layouts must be registered before pushing a unity::scopes::PreviewWidgetList, and must be
    registered only once.
    \return True if the query is still alive, false if the query failed or was cancelled.
    \throws unity::LogicException register_layout() is called more than once.
    */
    virtual bool register_layout(ColumnLayoutList const& layouts) = 0;

    /**
    \brief Sends widget definitions to the sender of the preview query.

    This method can be called mutiple times to send widgets in stages.
    \return True if the query is still alive, false if the query failed or was cancelled.
    */
    virtual bool push(PreviewWidgetList const& widget_list) = 0;

    /**
    \brief Sends data for a preview widget attribute.
    \return True if the query is still alive, false if the query failed or was cancelled.
    */
    virtual bool push(std::string const& key, Variant const& value) = 0;

    /// @cond
    virtual ~PreviewReply();
    /// @endcond

protected:
    /// @cond
    PreviewReply();
    /// @endcond
};

} // namespace scopes

} // namespace unity
