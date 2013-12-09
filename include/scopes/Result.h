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

#ifndef UNITY_API_SCOPES_RESULT_H
#define UNITY_API_SCOPES_RESULT_H

#include <scopes/Variant.h>
#include <string>
#include <memory>

namespace unity
{

namespace api
{

namespace scopes
{

class CategorisedResult;

namespace internal
{
class ResultImpl;
}

/**
   \brief Result encapsulates the basic attributes of any result
   returned by the Scope. The basic attributes (uri, title, icon, dnd_uri) must not be empty before
   calling Reply::push.
*/
class UNITY_API Result
{
public:
    /**
       \brief Creates a Result that is a copy of another Result.
    */
    Result(Result const& other);

    /**
       \brief Destructor.
    */
    virtual ~Result();

    Result& operator=(Result const& other);
    Result(Result&&);
    Result& operator=(Result&&);

    void store(Result const& other);
    bool has_stored_result() const;
    Result retrieve() const;

    void set_uri(std::string const& uri);
    void set_title(std::string const& title);
    void set_art(std::string const& image);
    void set_dnd_uri(std::string const& dnd_uri);
    void add_metadata(std::string const& key, Variant const& value);

    std::string uri() const;
    std::string title() const;
    std::string art() const;
    std::string dnd_uri() const;
    bool has_metadata(std::string const& key) const;
    Variant const& metadata(std::string const& key) const;

    /**
       \brief Returns a dictionary of all attributes of this Result instance.
       \return Dictionary of all base attributes and custom attributes set with add_metadata call.
    */
    VariantMap serialize() const;

private:
    explicit Result(const VariantMap &variant_map);
    Result(internal::ResultImpl* impl);

    std::shared_ptr<internal::ResultImpl> p;

    friend class internal::ResultImpl;
    friend class CategorisedResult;
};

} // namespace scopes

} // namespace api

} // namespace unity

#endif
