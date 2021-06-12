
#ifndef HW1_WET_TREE4_KEY_H
#define HW1_WET_TREE4_KEY_H

#include "DSW.h"

class Tree4_Key {
private:
    int _rate;
    UInt _type_id;

public:
    Tree4_Key(int rate, UInt type_id);
    ~Tree4_Key() = default;
    Tree4_Key(const Tree4_Key& other) = default;
    Tree4_Key& operator=(const Tree4_Key& other) = default;
    bool operator<(const Tree4_Key& other) const;
    bool operator>(const Tree4_Key& other) const;
    bool operator==(const Tree4_Key& other) const;
};


#endif //HW1_WET_TREE4_KEY_H
