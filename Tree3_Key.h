
#ifndef HW1_WET_TREE3_KEY_H
#define HW1_WET_TREE3_KEY_H

#include "DSW.h"


class Tree3_Key {
private:
    int _rate;
    UInt _type_id;
    UInt _model_id;

public:
    Tree3_Key(int rate, UInt type_id, UInt model_id);
    ~Tree3_Key() = default;
    Tree3_Key(const Tree3_Key& other) = default;
    Tree3_Key& operator=(const Tree3_Key& other) = default;
    UInt getTypeID() const;
    bool operator<(const Tree3_Key& other) const;
    bool operator>(const Tree3_Key& other) const;
    bool operator==(const Tree3_Key& other) const;
};


#endif //HW1_WET_TREE3_KEY_H
