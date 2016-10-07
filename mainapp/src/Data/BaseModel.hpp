#ifndef MODEL_BASEMODEL_HPP_
#define MODEL_BASEMODEL_HPP_

#include "basic.hpp"

/// DB Models
namespace model {

/// Status des Models
enum class ModelStatus : int32_t {
    Deleted,   ///< Gelöscht
    Published, ///< Offen
    Lock       ///< Gespeert
};


#pragma db model version(DB_APP_BASE_VERSION, DB_APP_VERSION)

/// Super-Klasse eines Models/Entity mit Zeitstempeln und Status
#pragma db object abstract callback(initdb)
class BaseModel {
    ODB_ACCESS

    private:
    std::chrono::system_clock::time_point time_created_db_;

    std::chrono::system_clock::time_point time_updated_db_;

    void initdb(odb::callback_event e, odb::database&) {
        switch (e) {
            case odb::callback_event::pre_persist: {
                this->time_created_db_ = std::chrono::system_clock::now();
                break;
            }
            case odb::callback_event::pre_update: {
                this->time_updated_db_ = std::chrono::system_clock::now();
                break;
            }
            case odb::callback_event::pre_erase: {
                this->model_status_db_ = ModelStatus::Deleted;
                break;
            }
            case odb::callback_event::pre_load: {
            } break;
            case odb::callback_event::post_load: {
            } break;
            case odb::callback_event::post_persist: {
            } break;
            case odb::callback_event::post_update: {
            } break;
            case odb::callback_event::post_erase: {
            } break;
        }
    }

    private:
    ModelStatus model_status_db_ = ModelStatus::Published;

    public:
    BaseModel();

    /// Modelstatus
    ModelStatus getModelStatus() const { return this->model_status_db_; }

    /**
     * @param model_status Modelstatus
     * @brief Modelstatus setzen
     */
    void setModelStatus(ModelStatus model_status) {
        this->model_status_db_ = model_status;
    }

    /// Erstellungs Zeitpunkt
    std::chrono::system_clock::time_point getTimeCreatedDB() const {
        return this->time_created_db_;
    }

    /// Letztes Update
    std::chrono::system_clock::time_point getTimeUpdatedDB() const {
        return this->time_updated_db_;
    }
};
} // namespace model


#endif // MODEL_BASEMODEL_HPP_
