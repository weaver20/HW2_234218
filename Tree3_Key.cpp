

#include "Tree3_Key.h"

Tree3_Key::Tree3_Key(int rate, UInt type_id, UInt model_id): _rate(rate), _type_id(type_id), _model_id(model_id) {}

bool Tree3_Key::operator<(const Tree3_Key &other) const {
    if(_rate < other._rate){
        return true;
    }
    else if(_rate == other._rate){
        if(_type_id < other._type_id){
            return true;
        }
        else if(_type_id == other._type_id){
            return _model_id < other._model_id;
        }
    }
    return false;
}

bool Tree3_Key::operator>(const Tree3_Key &other) const {
    if(_rate > other._rate){
        return true;
    }
    else if(_rate == other._rate){
        if(_type_id > other._type_id){
            return true;
        }
        else if(_type_id == other._type_id){
            return _model_id > other._model_id;
        }
    }
    return false;
}

bool Tree3_Key::operator==(const Tree3_Key& other) const{
    return _rate == other._rate and _type_id == other._type_id and _model_id == other._model_id;
}

UInt Tree3_Key::getTypeID() const {
    return _type_id;
}


