#include "BaseModel.hpp"

namespace model {

BaseModel::BaseModel()
    : time_created_db_(std::chrono::system_clock::now())
    , time_updated_db_(std::chrono::system_clock::now())
    , model_status_db_(ModelStatus::Published) {}
}
