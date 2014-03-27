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
# Authored by: Marcus Tomlinson <marcus.tomlinson@canonical.com>
#

@0xe6f283532b70ad20;

using Cxx = import "/capnp/c++.capnp";

$Cxx.namespace("unity::scopes::internal::zmq_middleware::capnproto::SigReceiver");

enum Signal
{
    scopeStarting @0;
    scopeRunning @1;
    scopeStopping @2;
}

struct PushSignalRequest
{
    signal @0 : Signal;
}
