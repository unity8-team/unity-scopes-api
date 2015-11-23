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
 * Authored by: Pawel Stolowski <pawel.stolowski@canonical.com>
 */

#include <unity/scopes/SearchQueryBase.h>
#include <unity/scopes/PreviewQueryBase.h>
#include <unity/scopes/ScopeBase.h>
#include <unity/scopes/PreviewWidget.h>
#include <unity/scopes/SearchReply.h>

#include <boost/algorithm/string.hpp>

#define EXPORT __attribute__ ((visibility ("default")))

using namespace std;
using namespace unity::scopes;

class MyQuery : public SearchQueryBase
{
public:
    MyQuery(CannedQuery const& query, SearchMetadata const& metadata,
            string const& scope_dir, string const& cache_dir,
            string const& app_dir, string const& tmp_dir)
        : SearchQueryBase(query, metadata)
        , scope_dir_(scope_dir)
        , cache_dir_(cache_dir)
        , app_dir_(app_dir)
        , tmp_dir_(tmp_dir)
    {
    }

    virtual void cancelled() override
    {
    }

    virtual void run(SearchReplyProxy const& reply) override
    {
        auto cat = reply->register_category("cat1", "Category 1", "");
        CategorisedResult res(cat);
        res.set_uri("scope_dir");
        res.set_title(scope_dir_);
        reply->push(res);
        res.set_uri("cache_dir");
        res.set_title(cache_dir_);
        reply->push(res);
        res.set_uri("app_dir");
        res.set_title(app_dir_);
        reply->push(res);
        res.set_uri("tmp_dir");
        res.set_title(tmp_dir_);
        reply->push(res);
    }

private:
    string scope_dir_;
    string cache_dir_;
    string app_dir_;
    string tmp_dir_;
};

class MyPreview : public PreviewQueryBase
{
public:
    MyPreview(Result const& result, ActionMetadata const& metadata)
        : PreviewQueryBase(result, metadata)
    {
    }

    virtual void cancelled() override
    {
    }

    virtual void run(PreviewReplyProxy const&) override
    {
    }
};

class MyScope : public ScopeBase
{
public:
    virtual void start(std::string const&) override
    {
    }

    virtual void stop() override {}

    virtual SearchQueryBase::UPtr search(CannedQuery const& q, SearchMetadata const& metadata) override
    {
        SearchQueryBase::UPtr query(new MyQuery(q, metadata,
                                                scope_directory(), cache_directory(),
                                                app_directory(), tmp_directory()));
        return query;
    }

    virtual PreviewQueryBase::UPtr preview(Result const& result, ActionMetadata const& metadata) override
    {
        PreviewQueryBase::UPtr preview(new MyPreview(result, metadata));
        return preview;
    }
};

extern "C"
{

    EXPORT
    unity::scopes::ScopeBase*
    // cppcheck-suppress unusedFunction
    UNITY_SCOPE_CREATE_FUNCTION()
    {
        return new MyScope;
    }

    EXPORT
    void
    // cppcheck-suppress unusedFunction
    UNITY_SCOPE_DESTROY_FUNCTION(unity::scopes::ScopeBase* scope_base)
    {
        delete scope_base;
    }
}
