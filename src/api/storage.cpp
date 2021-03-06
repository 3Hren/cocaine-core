#include "cocaine/api/storage.hpp"
#include "cocaine/context.hpp"
#include "cocaine/context/config.hpp"
#include "cocaine/repository/storage.hpp"

#include <boost/optional/optional.hpp>

#include <cassert>

namespace cocaine {
namespace api {
namespace ph = std::placeholders;

std::future<std::string>
storage_t::read(const std::string& collection, const std::string& key) {
    auto promise = std::make_shared<std::promise<std::string>>();
    read(collection, key, [=](std::future<std::string> future){
        assign_future_result(*promise, std::move(future));
    });
    return promise->get_future();
}

std::future<void>
storage_t::write(const std::string& collection,
                      const std::string& key,
                      const std::string& blob,
                      const std::vector<std::string>& tags) {
    auto promise = std::make_shared<std::promise<void>>();
    write(collection, key, blob, tags, [=](std::future<void> future){
        assign_future_result(*promise, std::move(future));
    });
    return promise->get_future();
}

std::future<void>
storage_t::remove(const std::string& collection, const std::string& key) {
    auto promise = std::make_shared<std::promise<void>>();
    remove(collection, key, [=](std::future<void> future){
        assign_future_result(*promise, std::move(future));
    });
    return promise->get_future();
}

std::future<std::vector<std::string>>
storage_t::find(const std::string& collection, const std::vector<std::string>& tags) {
    auto promise = std::make_shared<std::promise<std::vector<std::string>>>();
    find(collection, tags, [=](std::future<std::vector<std::string>> future){
        assign_future_result(*promise, std::move(future));
    });
    return promise->get_future();
}

storage_ptr
storage(context_t& context, const std::string& name) {
    auto storage = context.config().storages().get(name);
    if(!storage) {
        throw error_t(error::component_not_found, "storage component \"{}\" not found in the config", name);
    }
    return context.repository().get<storage_t>(storage->type(), context, name, storage->args());
}

} // namespace api
} // namespace cocaine
