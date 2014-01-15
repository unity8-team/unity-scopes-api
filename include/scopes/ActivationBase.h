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
 * Authored by: Pawel Stolowski <pawel.stolowski@canonical.com>
 */

#ifndef UNITY_SCOPES_ACTIVATIONBASE_H
#define UNITY_SCOPES_ACTIVATIONBASE_H

#include <unity/util/DefinesPtrs.h>
#include <unity/util/NonCopyable.h>
#include <scopes/ActivationResponse.h>

namespace unity
{

namespace api
{

namespace scopes
{

namespace internal
{
class ActivationBaseImpl;
}

/**
\brief Base class for a activation request that is executed inside a scope.
The default implementation responds with ActivationResponse(ActivationResponse::Status::NotHandled).
Reimplement this class and return an instance in ScopeBase::activate method for custom activation handling.
*/
class UNITY_API ActivationBase
{
public:
    /// @cond
    NONCOPYABLE(ActivationBase);
    UNITY_DEFINES_PTRS(ActivationBase);
    ActivationBase();
    virtual ~ActivationBase() noexcept;
    /// @endcond

    /**
     \brief Called when the originator of the activation request cancelled it.
     */
    virtual void cancelled();

    /**
     \brief Return response to the activation request.
     The response is received by the originator of the request. Default implementation
     returns ActivationResponse(ActivationResponse::Status::NotHandled.
     */
    virtual ActivationResponse activate();

private:
    void cancel();
    std::unique_ptr<internal::ActivationBaseImpl> p;
};

} // namespace scopes

} // namespace api

} // namespace unity

#endif
