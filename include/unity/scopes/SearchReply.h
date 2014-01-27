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

#ifndef UNITY_SCOPES_SEARCHREPLY_H
#define UNITY_SCOPES_SEARCHREPLY_H

#include <unity/scopes/ReplyBase.h>
#include <unity/scopes/Category.h>
#include <unity/scopes/CategoryRenderer.h>

namespace unity
{

namespace scopes
{

class CategorisedResult;
class Annotation;

class UNITY_API SearchReply : public virtual ReplyBase
{
public:
    SearchReply(SearchReply const&) = delete;

    /**
    \brief Create and register a new Category. The category is automatically sent to the source of the query.
    \return Category instance
    */
    Category::SCPtr register_category(std::string const& id,
                                      std::string const& title,
                                      std::string const &icon,
                                      CategoryRenderer const& renderer_template = CategoryRenderer());

    /**
    \brief Register an existing category instance and send it to the source of the query.
    The purpose of this call is to register a category obtained via ReplyBase::push(Category::SCPtr) when aggregating
    results and categories from other scope(s).
    */
    void register_category(Category::SCPtr category);

    /**
    \brief Returns an instance of previously registered category.
    \return Category instance or nullptr if category hasn't been registered.
    */
    Category::SCPtr lookup_category(std::string const& id) const;

    // TODO: document return value from push()
    /**
    \brief Sends a single result to the source of a query.
    Any calls to push() after finished() was called are ignored.
    \return The return value is true if the result was accepted, false otherwise.
    A false return value is due to either finished() having been called earlier,
    or the client that sent the query having cancelled that query.
    */
    bool push(CategorisedResult const& result) const;

    bool push(Annotation const& annotation) const;

    /**
    \brief Destroys a Reply.
    If a Reply goes out of scope without a prior call to finished(), the destructor implicitly calls finished().
    */
    virtual ~SearchReply();

protected:
    SearchReply(internal::ReplyImpl* impl);         // Instantiated only by ReplyImpl
    friend class internal::ReplyImpl;
};

} // namespace scopes

} // namespace unity

#endif
