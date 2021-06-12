
#ifndef HW1_WET_TREE4_DATA_H
#define HW1_WET_TREE4_DATA_H

#include "DSW.h"
#include "CarType.h"

class Tree4_Data {
private:
public:
    std::shared_ptr<class CarType> _car_type;
    std::shared_ptr<AVL_Tree<UInt, std::shared_ptr<CarModel>>> _model_tree;
    Tree4_Data(std::shared_ptr<class CarType> car_type);
    Tree4_Data(std::shared_ptr<class CarType> car_type, bool initialize);
    Tree4_Data(const Tree4_Data& other);
    Tree4_Data& operator=(const Tree4_Data& other) = default;
    ~Tree4_Data() = default;
    void setCarType(std::shared_ptr<class CarType> other);
    void setModelTree(std::shared_ptr<AVL_Tree<UInt, std::shared_ptr<CarModel>>> other);
    bool operator==(const Tree4_Data& other) const;
    bool operator!=(const Tree4_Data& other) const;
};


#endif //HW1_WET_TREE4_DATA_H
