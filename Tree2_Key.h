
#ifndef HW1_WET_TREE2_KEY_H
#define HW1_WET_TREE2_KEY_H

#include "DSW.h"


class Tree2_Key {
private:
    UInt _sales;
    UInt _typeID;

public:
    Tree2_Key(UInt sales, UInt typeID);
    ~Tree2_Key() = default;
    Tree2_Key& operator=(const Tree2_Key& other) = default;
    UInt getSales() const;
    UInt getTypeID() const;
    bool operator<(const Tree2_Key& other) const;
    bool operator>(const Tree2_Key& other) const;
    bool operator==(const Tree2_Key& other) const;

};


#endif //HW1_WET_TREE2_KEY_H
