//
// Copyright (C) 2011-2012 Andrey Sibiryov <me@kobology.ru>
//
// Licensed under the BSD 2-Clause License (the "License");
// you may not use this file except in compliance with the License.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "cocaine/interfaces/plugin.hpp"

#include "cocaine/overseer.hpp"
#include "cocaine/rpc.hpp"

using namespace cocaine;
using namespace cocaine::engine;

io_t::io_t(overseer_t& overseer):
    m_overseer(overseer)
{ }

blob_t io_t::pull(bool block) {
    return m_overseer.recv(block);
}

void io_t::push(const void * data, size_t size) {
    zmq::message_t message(size);

    memcpy(message.data(), data, size);

    events::push_t event(message);
    rpc::packed<events::push_t> packed(event);

    m_overseer.send(packed);
}

void io_t::emit(const std::string& key, const void * data, size_t size) {
    // TODO: Emitters.
}

plugin_t::plugin_t(context_t& ctx):
    object_t(ctx)
{ }

plugin_t::~plugin_t()
{ }
