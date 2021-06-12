
#include "Tree4_Key.h"

Tree4_Key::Tree4_Key(int rate, UInt type_id): _rate(rate), _type_id(type_id) {}

bool Tree4_Key::operator<(const Tree4_Key &other) const {
    if(_rate < other._rate){
        return true;
    }
    else if(_rate == other._rate){
        return _type_id < other._type_id;
    }
    return false;
}

bool Tree4_Key::operator>(const Tree4_Key &other) const {
    if(_rate > other._rate){
        return true;
    }
    else if(_rate == other._rate) {
        if (_type_id > other._type_id) {
            return _type_id > other._type_id;
        }
    }
    return false;
}

bool Tree4_Key::operator==(const Tree4_Key& other) const{
    return _rate == other._rate and _type_id == other._type_id;
}




