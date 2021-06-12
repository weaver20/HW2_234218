
#include "Tree2_Key.h"


Tree2_Key::Tree2_Key(UInt sales, UInt typeID):_sales(sales), _typeID(typeID){}

unsigned int Tree2_Key::getSales() const{
    return _sales;
}


unsigned int Tree2_Key::getTypeID() const {
    return _typeID;
}

bool Tree2_Key::operator<(const Tree2_Key &other) const {
    if(_sales < other.getSales()){
        return true;
    }
    else if(_sales == other.getSales()){
        return _typeID > other._typeID;
    }
    return false;
}

bool Tree2_Key::operator>(const Tree2_Key &other) const{
    if(_sales > other._sales){
        return true;
    }
    else if(_sales == other._sales){
        return _typeID < other._typeID;
    }
    return false;
}

bool Tree2_Key::operator==(const Tree2_Key& other) const{
    return _sales == other._sales and _typeID == other._typeID;
}

