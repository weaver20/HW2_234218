
#include "Tree4_Data.h"

Tree4_Data::Tree4_Data(std::shared_ptr<CarType> car_type): _car_type(car_type),
_model_tree(new AVL_Tree<UInt, std::shared_ptr<CarModel>>(_car_type->getModelArr(), ZERO, _car_type->getNumOfModels() - 1)){}

Tree4_Data::Tree4_Data(const Tree4_Data& other): _car_type(other._car_type), _model_tree(other._model_tree){
}

Tree4_Data::Tree4_Data(std::shared_ptr<class CarType> car_type, bool initialize): _car_type(car_type), _model_tree(){}

/*static std::shared_ptr<TNode<UInt, std::shared_ptr<CarModel>>>
sortedArrayToAVL(std::shared_ptr<CarModel>* arr, int start, int end){
    if(start > end){
        return nullptr;
    }
    int mid = start + (end - start) / 2;
    std::shared_ptr<TNode<UInt, std::shared_ptr<CarModel>>>
            root(new TNode<UInt, std::shared_ptr<CarModel>>(arr[mid]->getModelID(), arr[mid]));
    root->left = sortedArrayToAVL(arr, start, mid - 1);
    root->right = sortedArrayToAVL(arr, mid + 1, end);
    if(root->left != nullptr){
        root->left->parent = root;
    }
    if(root->right != nullptr){
        root->right->parent = root;
    }
    root->refresh();
    return root;
}

std::shared_ptr<TNode<UInt, std::shared_ptr<CarModel>>> Tree4_Data::arrayToAVL() const{
    return sortedArrayToAVL(_car_type->getModelArr(), ZERO, _car_type->getNumOfModels() - 1);
}
*/

void Tree4_Data::setCarType(std::shared_ptr<class CarType> other){
    _car_type = other;
}

void Tree4_Data::setModelTree(std::shared_ptr<AVL_Tree<UInt, std::shared_ptr<CarModel>>> other){
    _model_tree = other;
}

bool Tree4_Data::operator==(const Tree4_Data& other) const{
    return *_car_type == *other._car_type and _model_tree->getRoot() == other._model_tree->getRoot();
}

bool Tree4_Data::operator!=(const Tree4_Data& other) const {
    return not(*this == other);
}



