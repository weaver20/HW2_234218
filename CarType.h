
#ifndef HW1_WET_CARTYPE_H
#define HW1_WET_CARTYPE_H

#include "DSW.h"
#include "CarModel.h"
class CarType {
    UInt _type_id;
    std::shared_ptr<class CarModel> _best_seller_model;
    std::shared_ptr<class CarModel>* _model_arr;
    UInt _num_of_models;

public:
    CarType(UInt type_id, UInt num_of_models);
    ~CarType();
    CarType(const CarType& other) = delete;
    CarType& operator=(const CarType& other) = delete;
    UInt getID();
    std::shared_ptr<class CarModel> getBestSellerModel();
    std::shared_ptr<class CarModel>* getModelArr();
    UInt getNumOfModels() const;
    void setBestSeller(std::shared_ptr<class CarModel>best_seller_model);
    bool operator==(const CarType& other) const;
    bool operator!=(const CarType& other) const;
};


#endif //HW1_WET_CARTYPE_H
