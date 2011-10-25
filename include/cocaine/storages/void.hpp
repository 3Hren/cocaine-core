#ifndef COCAINE_STORAGES_VOID_HPP
#define COCAINE_STORAGES_VOID_HPP

#include "cocaine/storages/abstract.hpp"

namespace cocaine { namespace storage { namespace backends {

class void_storage_t:
    public storage_t
{
    public:
        void put(const std::string& ns, const std::string& key, const Json::Value& value) { }
        bool exists(const std::string& ns, const std::string& key) { return false; }

        Json::Value get(const std::string& ns, const std::string& key) { return Json::Value(); }
        Json::Value all(const std::string& ns) { return Json::Value(); }

        void remove(const std::string& ns, const std::string& key) { }
        void purge(const std::string& ns) { }
};

}}}

#endif
