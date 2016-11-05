#ifndef ENTITY_DATA_DATAMANGERBASE_H_
#define ENTITY_DATA_DATAMANGERBASE_H_

#include <functional>

#include "basic.h"

#include "Data/Basic.h"


namespace gameentity {

template<class T>
class DataManagerBase {
    public:
    using findDataByName_func_t = std::function<bool(std::string, const std::shared_ptr<T>&)>;

    protected:
    std::vector<std::shared_ptr<T>> data_;

    const findDataByName_func_t findDataByName_;

    DataManagerBase(findDataByName_func_t findDataByName)
        : findDataByName_(findDataByName)
    {}

    public:

    virtual ~DataManagerBase() = default;
    DataManagerBase(const DataManagerBase&) = default;
    DataManagerBase& operator=(const DataManagerBase&) = default;
    DataManagerBase(DataManagerBase&&) = default;
    DataManagerBase& operator=(DataManagerBase&&) = default;



    std::shared_ptr<T> findByName(std::string name) const {
        auto find_func = [&](const auto& data){
            return this->findDataByName_(name, data);
        };
        auto it = std::find_if(std::begin(this->data_), std::end(this->data_), find_func);

        return (it != std::end(this->data_)) ? *it : nullptr;
    }
    
    void add(const T& data) {
        this->data_.push_back(std::make_shared<T>(data));
    }
    
    void setAll(const std::vector<std::shared_ptr<T>>& data) {
        this->data_ = data;
    }
    
    const std::vector<std::shared_ptr<T>>& getAll() const {
        return this->data_;
    }

    void erase(std::string name) {
        auto find_func = [&](const auto& data){
            return this->findDataByName_(name, data);
        };

        this->data_.erase(std::remove_if(std::begin(this->data_), 
                                         std::end(this->data_),
                                         find_func),
                          std::end(this->data_));
    }

    void save(std::string name, const T& data) {
        auto find_data = this->findByName(name);
        if(find_data){
            *find_data = data;
        } else {
            this->add(data);
        }
    }

};

}

#endif // ENTITY_DATA_DATAMANGERBASE_H_