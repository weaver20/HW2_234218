
#include "CarType.h"



CarType::CarType(UInt type_id, UInt num_of_models): _type_id(type_id), _num_of_models(num_of_models){
    _model_arr = new std::shared_ptr<CarModel>[num_of_models];
    for(UInt i = 0; i < num_of_models; ++i) {
        _model_arr[i] = std::shared_ptr<CarModel>(new CarModel(i, type_id));
    }
    _best_seller_model = _model_arr[ZERO];
}

CarType::~CarType() {
    _best_seller_model = nullptr;
    for (UInt i = 0; i < _num_of_models; ++i) {
        _model_arr[i] = nullptr;
    }
    delete[] _model_arr;
}

UInt CarType::getID() {
    return _type_id;
}

std::shared_ptr<CarModel> CarType::getBestSellerModel() {
    return _best_seller_model;
}

std::shared_ptr<CarModel>* CarType::getModelArr() {
    return _model_arr;
}

UInt CarType::getNumOfModels() const {
    return _num_of_models;
}

void CarType::setBestSeller(std::shared_ptr<class CarModel> best_seller_model){
    _best_seller_model = best_seller_model;
}

bool CarType::operator==(const CarType& other) const{
    return _type_id == other._type_id;
}

bool CarType::operator!=(const CarType& other) const{
    return _type_id != other._type_id;
}
