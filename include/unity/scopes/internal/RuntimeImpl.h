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

#include <unity/scopes/internal/Logger.h>
#include <unity/scopes/internal/MiddlewareBase.h>
#include <unity/scopes/internal/MiddlewareFactory.h>
#include <unity/scopes/internal/Reaper.h>
#include <unity/scopes/internal/ThreadPool.h>
#include <unity/scopes/Runtime.h>

namespace unity
{

namespace scopes
{

namespace internal
{

class RuntimeImpl final
{
public:
    NONCOPYABLE(RuntimeImpl);
    UNITY_DEFINES_PTRS(RuntimeImpl);

    static UPtr create(std::string const& scope_id, std::string const& configfile = "");
    void destroy();

    std::string scope_id() const;
    MiddlewareFactory const* factory() const;
    RegistryProxy registry() const;
    std::string registry_configfile() const;
    std::string registry_identity() const;
    std::string ss_configfile() const;
    std::string ss_registry_identity() const;
    Reaper::SPtr reply_reaper() const;
    ThreadPool::SPtr async_pool() const;
    ThreadSafeQueue<std::future<void>>::SPtr future_queue() const;
    unity::scopes::internal::Logger& logger() const;
    void run_scope(ScopeBase* scope_base,
                   std::string const& scope_ini_file,
                   std::promise<void> ready_promise = std::promise<void>());

    ObjectProxy string_to_proxy(std::string const& s) const;
    std::string proxy_to_string(ObjectProxy const& proxy) const;

    std::string cache_directory() const;
    std::string tmp_directory() const;
    std::string config_directory() const;

    ~RuntimeImpl();

private:
    RuntimeImpl(std::string const& scope_id, std::string const& configfile);
    void waiter_thread(ThreadSafeQueue<std::future<void>>::SPtr const& queue) const noexcept;
    std::string demangled_id(std::string const& scope_id) const;
    bool confined() const;
    std::string confinement_type() const;
    std::string find_cache_dir() const;
    std::string find_app_dir() const;
    std::string find_log_dir(std::string const& id) const;
    std::string find_tmp_dir() const;

    bool destroyed_;
    std::string scope_id_;
    MiddlewareFactory::UPtr middleware_factory_;
    MiddlewareBase::SPtr middleware_;
    RegistryProxy registry_;
    std::string runtime_configfile_;
    std::string registry_configfile_;
    std::string registry_identity_;
    std::string ss_configfile_;
    std::string ss_registry_identity_;
    int reap_expiry_;
    int reap_interval_;
    std::string cache_dir_;
    std::string app_dir_;
    std::string log_dir_;
    std::string config_dir_;
    Logger::UPtr logger_;
    mutable Reaper::SPtr reply_reaper_;
    mutable ThreadPool::SPtr async_pool_;  // Pool of invocation threads for async query creation
    mutable ThreadSafeQueue<std::future<void>>::SPtr future_queue_;
    mutable std::thread waiter_thread_;
    mutable std::mutex mutex_;  // For lazy initialization of reply_reaper_, async_pool_, and queue_
};

} // namespace internal

} // namespace scopes

} // namespace unity
