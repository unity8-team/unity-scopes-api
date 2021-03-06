#
# Copyright (C) 2013 Canonical Ltd
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License version 3 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Authored by: Michi Henning <michi.henning@canonical.com>
#

@0x8fe122e718a84617;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("unity::scopes::internal::zmq_middleware::capnproto");

# Proxy definition. The endpoint must include
# the protocol, which controls how to interpret the remainder of the string. For example:
#
# "tcp://localhost:5555" (TCP on loopback, port 5555
#
# "ipc:///tmp/socket" (UNIX domain socket at /tmp/socket)
#
# The identity can be anything. It must be unique withing the corresponding endpoint. The identity
# determines the target object of a message sent via the proxy.
#
# The category is normally empty. For default servants, the category is used to identify the type
# of the target object, such as "Scope", "Reply", etc.

struct Proxy
{
    endpoint @0 : Text;
    identity @1 : Text;
    category @2 : Text;
    timeout  @3 : Int64;  # timeout for twoway proxies in milliseconds, -1 == wait forever
}
