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

#include <unity/scopes/ScopeProxyFwd.h>
#include <unity/scopes/Variant.h>
#include <unity/util/DefinesPtrs.h>

#include <set>

namespace unity
{

namespace scopes
{

namespace internal
{
class ScopeMetadataImpl;
} // namespace internal

namespace testing
{
class ScopeMetadataBuilder;
} // namespace testing

/**
\brief Holds scope attributes such as name, description, icon etc.

The information stored by ScopeMetadata comes from the .ini file for the given scope (for local scopes)
or is fetched from the remote server (for scopes running on Smart Scopes Server).
Use unity::scopes::Registry to get the metadata for a specific scope or all scopes.
*/

class ScopeMetadata final
{
public:
    /**
     \brief Enum representing the expected valid lifetime of results from the scope.
     */
    enum class ResultsTtlType
    {
        None,
        Small,
        Medium,
        Large
    };

    /// @cond
    UNITY_DEFINES_PTRS(ScopeMetadata);
    ~ScopeMetadata();
    /// @endcond

    /**@name Copy and assignment
    Copy and assignment operators (move and non-move versions) have the usual value semantics.
    */
    //{@
    ScopeMetadata(ScopeMetadata const& other);
    ScopeMetadata(ScopeMetadata&&);

    ScopeMetadata& operator=(ScopeMetadata const& other);
    ScopeMetadata& operator=(ScopeMetadata&&);
    //@}

    /**
    \brief Get the scope identifier.
    \return The ID of the scope.
    */
    std::string scope_id() const;

    /**
    \brief Get the proxy object for this scope.
    \return The scope proxy.
    */
    ScopeProxy proxy() const;

    /**
    \brief Get the display name for this scope.
    \return The scope display name.
    */
    std::string display_name() const;   // localized

    /**
    \brief Get the description for this scope.
    \return The scope description.
    */
    std::string description() const;    // localized

    /**
    \brief Get the author for this scope.
    \return The scope author.
    */
    std::string author() const;

    /**
    \brief Get the art for this scope.
    \return The scope art.
    */
    std::string art() const;            // optional

    /**
    \brief Get the icon for this scope.
    \return The scope icon.
    */
    std::string icon() const;           // optional

    /**
    \brief Get the search hint for this scope.
    \return The search hint.
    */
    std::string search_hint() const;    // localized, optional

    /**
    \brief Get the hot key for this scope.
    \return The hot key.
    */
    std::string hot_key() const;        // localized, optional

    /**
    \brief Check if this scope should be hidden in the Dash.
    \return True if this scope is invisible.
    */
    bool invisible() const;             // optional (default = false)

    /**
    \brief Get optional display attributes.

    Appearance attributes define customized look of the scope in Scopes Scope.
    \return Map of attributes (may be empty)
    */
    VariantMap appearance_attributes() const;

    /**
    \brief Get directory where scope config files and .so file lives.

    Note that the directory is not set for remote scopes; in such case this method throws unity::scopes::NotFoundException.

    \throws unity::scopes::NotFoundException if directory is not set
    \return path string
    */
    std::string scope_directory() const;

    /**
    \brief Return a dictionary of all metadata attributes.
    \return Dictionary of all metadata attributes.
    */
    VariantMap serialize() const;

    /**
    \brief Return the TTL for the results this scope produces.
    \return Enum of timeout type.
    */
    ResultsTtlType results_ttl_type() const;

    // TODO: Flesh out documentation
    /**
    \brief Return the settings definitions for this scope.
    \return The settings definition as a VariantArray. The array
    contains the definition of the settings in their original order.

    \throws unity::scopes::NotFoundException if the scope has no settings
    \see TBD TODO
    */
    VariantArray settings_definitions() const;

    /**
    \brief Check if this scope wants location data.
    \return True if this scope wants location data.
    */
    bool location_data_needed() const;  // optional (default = false)

    /**
    \brief Return the list of scope identifiers aggregated by this scope.

    The list returned by this method comes from the .ini file.
    The scope author must ensure that it contains all scopes that an aggregator
    might collect results from. This list may contain scopes that are not currently
    installed and are optional for proper functioning of the aggregator scope.

    \return The list of scopes ids aggregated by this scope.
    */
    std::vector<std::string> child_scope_ids() const;

    /**
    \brief Return the version of the scope.

    \return The version or, if the scope does not define its version,
    the value `0`.
    */
    int version() const;

    /**
    \brief Return the set of keywords specified by this scope.

    The set returned by this method is formulated from the value specified under
    the "Keywords" key in the scope's .ini file.

    \return The set of keywords specified by this scope.
    */
    std::set<std::string> keywords() const;

    /**
    \brief Check if this scope is an aggregator.
    \return True if this scope is an aggregator.
    */
    bool is_aggregator() const;  // optional (default = false)

private:
    ScopeMetadata(std::unique_ptr<internal::ScopeMetadataImpl>);           // Instantiable only by ScopeMetadataImpl
    std::unique_ptr<internal::ScopeMetadataImpl> p;

    friend class internal::ScopeMetadataImpl;
};

} // namespace scopes

} // namespace unity
