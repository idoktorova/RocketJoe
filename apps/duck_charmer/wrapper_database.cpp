#include "forward.hpp"
#include "wrapper_database.hpp"
#include "spaces.hpp"

namespace duck_charmer {
    wrapper_database::~wrapper_database() {
    }

    auto wrapper_database::collection_names() -> py::list {
        py::list tmp;
        for (auto &i : collections_) {
            tmp.append(i.first);
        }
        return tmp;
    }

    bool wrapper_database::drop_collection(const std::string& collection_name) {
        log_.debug("wrapper_database::drop_collection: {}", collection_name);
        collections_.erase(collection_name);
        auto session_tmp = duck_charmer::session_t();
        auto result = ptr_->drop_collection(session_tmp, name_, collection_name);
        log_.debug("wrapper_database::drop_collection {}", result.is_success());
        return result.is_success();
    }

    wrapper_collection_ptr wrapper_database::create(const std::string& collection_name) {
        log_.debug("wrapper_database::create name collection: {}", collection_name);
        auto session_tmp = duck_charmer::session_t();
        auto result =  ptr_->create_collection(session_tmp,name_,collection_name);
        log_.debug("wrapper_client::get_or_create return wrapper_database_ptr");
        collections_.emplace(collection_name,result);
        return result;
    }

    wrapper_database::wrapper_database(const std::string& name, wrapper_dispatcher_t* ptr, log_t& log)
        : name_(name)
        ,ptr_(ptr)
        , log_(log.clone()) {
        log_.debug("wrapper_database");
    }

}