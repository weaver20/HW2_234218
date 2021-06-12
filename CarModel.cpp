
#include "CarModel.h"

 CarModel::CarModel(UInt model_id, UInt type_id): _model_id(model_id), _rate(ZERO), _sales(ZERO), _type_id(type_id) {}

UInt CarModel::getSales() const{
    return _sales;
}

UInt CarModel::getModelID() const{
    return _model_id;
}

int CarModel::getRate() const{
    return _rate;
}
void CarModel::sell(){
    _sales++;
    _rate += 10;
}

void CarModel::complaint(UInt t){
    _rate -= (100/t);
}

UInt CarModel::getTypeID() const {
    return _type_id;
}

bool CarModel::operator!=(const CarModel &other) const {
    return _rate != other._rate and _sales != other._sales and
    _type_id != other._type_id and _model_id != other._model_id;
}

bool CarModel::operator==(const CarModel &other) const {
    return not (*this != other);
}








