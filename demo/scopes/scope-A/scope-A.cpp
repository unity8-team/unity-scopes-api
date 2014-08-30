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

// You may also include individual headers if you prefer.
#include <unity-scopes.h>

#include <iostream>

#define EXPORT __attribute__ ((visibility ("default")))

using namespace std;
using namespace unity::scopes;

// Example scope A: replies synchronously to a query. (Replies are returned before returning from the run() method.)

class MyQuery : public SearchQueryBase
{
public:
    MyQuery(string const& scope_id, CannedQuery const& query, SearchMetadata const& metadata) :
        SearchQueryBase(query, metadata),
        scope_id_(scope_id)
    {
        cerr << scope_id_ << ": query instance for \"" << query.query_string() << "\" created" << endl;
    }

    ~MyQuery()
    {
        cerr << scope_id_ << ": query instance for \"" << query().query_string() << "\" destroyed" << endl;
    }

    virtual void cancelled() override
    {
    }

    virtual void run(SearchReplyProxy const& reply) override
    {
        if (!valid())
        {
            return;  // Query was cancelled
        }

        Department::SPtr all_depts = Department::create("", query(), "All departments");
        Department::SPtr news_dept = Department::create("news", query(), "News");
        news_dept->set_subdepartments({Department::create("news-world", query(), "World"), Department::create("news-europe", query(), "Europe")});
        all_depts->set_subdepartments({news_dept, Department::create("sport", query(), "Sport")});
        reply->register_departments(all_depts);

        Filters filters;
        OptionSelectorFilter::SPtr filter = OptionSelectorFilter::create("f1", "Options");
        filter->add_option("1", "Option 1");
        filter->add_option("2", "Option 2");
        filters.push_back(filter);
        FilterState filter_state; // TODO: push real state from query obj
        if (!reply->push(filters, filter_state))
        {
            return;  // Query was cancelled
        }

        CategoryRenderer rdr;
        auto cat = reply->register_category("cat1", "Category 1", "", rdr);
        CategorisedResult res(cat);
        res.set_uri("uri");
        res.set_title("scope-A: result 1 for query \"" + query().query_string() + "\"");
        res.set_art("icon");
        res.set_dnd_uri("dnd_uri");
        if (!reply->push(res))
        {
            return;  // Query was cancelled
        }

        CannedQuery q("scope-A", query().query_string(), "");
        experimental::Annotation annotation(experimental::Annotation::Type::Link);
        annotation.add_link("More...", q);
        reply->push(annotation);

        cerr << "scope-A: query \"" << query().query_string() << "\" complete" << endl;
    }

private:
    string scope_id_;
};

class InstallingPreview : public PreviewQueryBase
{
public:
    InstallingPreview(Result const& result, ActionMetadata const& metadata) :
                   PreviewQueryBase(result, metadata)
    {

    }

    virtual void cancelled() override
    {
    }

    void startInstallation()
    {
        // The call to download-manager to start the installation would happen *here*
    }

    virtual void run(PreviewReplyProxy const& reply) override
    {
        startInstallation();

        PreviewWidgetList widgets;
        widgets.emplace_back(PreviewWidget(R"({"id": "header", "type": "header", "title": "Actual installation happens now...", "subtitle": "0% and counting!", "rating": "rating"})"));

        if (!reply->push(widgets))
        {
            return;  // Query was cancelled
        }
        cerr << "scope-A: preview for \"" << result().uri() << "\" complete" << endl;
    }

};

class MyPreview : public PreviewQueryBase
{
public:
    MyPreview(Result const& result, ActionMetadata const& metadata, string const& scope_id) :
        PreviewQueryBase(result, metadata),
        scope_id_(scope_id)
    {
        cerr << scope_id_ << ": preview instance for \"" << result.uri() << "\" created" << endl;
    }

    ~MyPreview()
    {
        cerr << scope_id_ << ": preview instance for \"" << result().uri() << "\" destroyed" << endl;
    }

    virtual void cancelled() override
    {
    }

    virtual void run(PreviewReplyProxy const& reply) override
    {
        PreviewWidgetList widgets;
        widgets.emplace_back(PreviewWidget(R"({"id": "header", "type": "header", "title": "title", "subtitle": "author", "rating": "rating"})"));
        widgets.emplace_back(PreviewWidget(R"({"id": "img", "type": "image", "art": "screenshot-url"})"));

        PreviewWidget buttons("buttons", "actions");
        VariantBuilder builder;
        builder.add_tuple({
            {"id", Variant("install_id")},
            {"label", Variant("Install")}
        });
        buttons.add_attribute_value("actions", builder.end());
        widgets.emplace_back(buttons);

        if (!reply->push(widgets))
        {
            return;  // Query was cancelled
        }
        cerr << "scope-A: preview for \"" << result().uri() << "\" complete" << endl;
    }

private:
    string scope_id_;
};

class MyActivationQuery : public ActivationQueryBase
{
protected:
    ActivationResponse::Status status_ = ActivationResponse::Status::ShowPreview;
    VariantMap hints_;
public:
    MyActivationQuery(const Result& result, const ActionMetadata& metadata)
        : ActivationQueryBase(result, metadata)
    {

    }
    void setStatus(ActivationResponse::Status status)
    {
        status_ = status;
    }

    void setHint(std::string key, unity::scopes::Variant value)
    {
        hints_[key] = value;
    }

    ActivationResponse activate() override
    {
        auto response = ActivationResponse(status_);
        response.set_scope_data(Variant(hints_));
        return response;
    }

};

class MyScope : public ScopeBase
{
public:
    virtual void start(string const& scope_id) override
    {
        scope_id_ = scope_id;
    }

    virtual void stop() override {}

    virtual SearchQueryBase::UPtr search(CannedQuery const& q, SearchMetadata const& metadata) override
    {
        SearchQueryBase::UPtr query(new MyQuery(scope_id_, q, metadata));
        return query;
    }

    virtual PreviewQueryBase::UPtr preview(Result const& result, ActionMetadata const& metadata) override
    {

        if (metadata.scope_data().which() != Variant::Type::Null)
        {
            auto metadict = metadata.scope_data().get_dict();
            if (metadict.count("action_id") != 0  && metadict["action_id"].get_string() == "install_hint")
            {
                return PreviewQueryBase::UPtr(new InstallingPreview(result, metadata));
            }
        }

        PreviewQueryBase::UPtr preview(new MyPreview(result, metadata, scope_id_));
        cerr << "scope-A: created previewer: \"" << result.uri() << "\"" << endl;
        return preview;
    }

    virtual ActivationQueryBase::UPtr perform_action(Result const& result,
                                                     ActionMetadata const& metadata,
                                                     std::string const& /*widget_id*/,
                                                     std::string const& action_id) override
    {
        auto activation = new MyActivationQuery(result, metadata);
        if (action_id == "install_id") {
            activation->setHint("action_id", Variant("install_hint"));
            activation->setStatus(ActivationResponse::Status::ShowPreview);
        }
        return ActivationQueryBase::UPtr(activation);
    }

private:
    string scope_id_;
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
