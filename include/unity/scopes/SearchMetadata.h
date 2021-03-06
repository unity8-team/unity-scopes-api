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

#pragma once

#include <unity/scopes/QueryMetadata.h>
#include <unity/scopes/Location.h>
#include <unity/scopes/Variant.h>
#include <unity/util/DefinesPtrs.h>

#include <set>

namespace unity
{

namespace scopes
{

namespace internal
{

class SearchMetadataImpl;

}

/**
\brief Metadata passed with search requests.
*/

class SearchMetadata : public QueryMetadata
{
public:
    /// @cond
    UNITY_DEFINES_PTRS(SearchMetadata);
    /// @endcond

    /**
    \brief Create SearchMetadata with the given locale and form factor.
    \param locale locale string, eg. en_EN
    \param form_factor form factor name, e.g. phone, desktop, phone-version etc.
    */
    SearchMetadata(std::string const& locale, std::string const& form_factor);

    /**
    \brief Create SearchMetadata with the given cardinality, locale, and form factor.
    \param cardinality maximum number of search results
    \param locale locale string, eg. en_EN
    \param form_factor form factor name, e.g. phone, desktop, phone-version etc.
    */
    SearchMetadata(int cardinality, std::string const& locale, std::string const& form_factor);

    /**@name Copy and assignment
    Copy and assignment operators (move and non-move versions) have the usual value semantics.
    */
    //{@
    SearchMetadata(SearchMetadata const& other);
    SearchMetadata(SearchMetadata&&);

    SearchMetadata& operator=(SearchMetadata const& other);
    SearchMetadata& operator=(SearchMetadata&&);
    //@}

    /// @cond
    ~SearchMetadata();
    /// @endcond

    /**
    \brief Set cardinality.
    \param cardinality The maximum number of search results.
    */
    void set_cardinality(int cardinality);

    /**
    \brief Get cardinality.
    \return The maxmium number of search results, or 0 for no limit.
    */
    int cardinality() const;

    /**
    \brief Set location.
    \param location Location data.
    */
    void set_location(Location const& location);

    /**
    \brief Get location.
    \return Location data representing the current location, including attributes such as city and country.
    \throws unity::NotFoundException if no location data is available.
    */
    Location location() const;

    /**
    \brief Does the SearchMetadata have a location.
    \return True if there is a location property.
    */
    bool has_location() const;

    /**
    \brief Remove location data entirely.

    This method does nothing if no location data is present.
    */
    void remove_location();

    /**
    \brief Set the list of scope keywords used to initiate this search request.
    \param aggregated_keywords The list of scope keywords used to initiate this search request.
    */
    void set_aggregated_keywords(std::set<std::string> const& aggregated_keywords);

    /**
    \brief Get the list of scope keywords used to initiate this search request.
    \return The list of scope keywords used to initiate this search request.
    */
    std::set<std::string> aggregated_keywords() const;

    /**
    \brief Check if this search request originated from an aggregator scope.
    \return True if this search request originated from an aggregator scope.
    */
    bool is_aggregated() const;

    /**
    \brief Sets a hint.

    \param key The name of the hint.
    \param value Hint value
    */
    void set_hint(std::string const& key, Variant const& value);

    /**
    \brief Get all hints.

    \return Hints dictionary.
    \throws unity::NotFoundException if no hints are available.
    */
    VariantMap hints() const;

    /**
    \brief Check if this SearchMetadata has a hint.
    \param key The hint name.
    \return True if the hint is set.
    */
    bool contains_hint(std::string const& key) const;

    /**
    \brief Returns a reference to a hint.

    This method can be used to read or set hints. Setting a value of an existing hint overwrites
    its previous value.
    Referencing a non-existing hint automatically creates it with a default value of Variant::Type::Null.
    \param key The name of the hint.
    \return A reference to the hint.
    */
    Variant& operator[](std::string const& key);

    /**
    \brief Returns a const reference to a hint.

    This method can be used for read-only access to hints.
    Referencing a non-existing hint throws unity::InvalidArgumentException.
    \param key The name of the hint.
    \return A const reference to the hint.
    \throws unity::NotFoundException if no hint with the given name exists.
    */
    Variant const& operator[](std::string const& key) const;

private:
    SearchMetadata(internal::SearchMetadataImpl* impl);
    friend class internal::SearchMetadataImpl;
};

} // namespace scopes

} // namespace unity
