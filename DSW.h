
#ifndef HW1_WET_DSW_H
#define HW1_WET_DSW_H
#define UInt unsigned int
#define ZERO 0
#include "library.h"
#include "Tree.h"
#include "CarType.h"
#include "CarModel.h"
#include "Tree2_Key.h"
#include "Tree3_Key.h"
#include "Tree4_Key.h"
#include "Tree4_Data.h"


class DSW {
private:
    std::shared_ptr<AVL_Tree<UInt, std::shared_ptr<class CarType>>> _tree1;
    std::shared_ptr<AVL_Tree<class Tree2_Key, std::shared_ptr<class CarType>>> _tree2;
    std::shared_ptr<AVL_Tree<class Tree3_Key, std::shared_ptr<CarModel>>> _tree3;
    std::shared_ptr<AVL_Tree<class Tree4_Key,class Tree4_Data>> _tree4;
    UInt _num_of_models;
public:
    DSW();
    DSW(const DSW& other) = delete;
    DSW& operator=(const DSW& other) = delete;
    ~DSW();
    StatusType AddCarType(int typeID, int numOfModels);
    StatusType RemoveCarType(int typeID);
    StatusType SellCar(int typeID, int modelID);
    StatusType MakeComplaint(int typeID, int modelID, int t);
    StatusType GetBestSellerModelByType(int typeID, int * modelID);
    StatusType GetWorstModels(int numOfModels, int *types, int *models);

    //Auxiliary functions//
    void modifiedInOrderTree3
            (std::shared_ptr<TNode<Tree3_Key,
                    std::shared_ptr<CarModel>>> root, int* types, int *models, int numOfModels, int& count, bool& tree4_visited);

    void inOrderTraversalTree3
            (std::shared_ptr<TNode<Tree3_Key, std::shared_ptr<CarModel>>> root, int* types, int *models, int numOfModels, int& count, bool& tree4_visited);

    void modifiedInOrderTree4
            (std::shared_ptr<TNode<Tree4_Key, Tree4_Data>> root, int* types, int *models, int numOfModels, int& count);

    void inOrderTraversalTree4
            (std::shared_ptr<TNode<Tree4_Key, Tree4_Data>> root, int* types, int *models, int numOfModels, int& count);

    void modifiedInOrderTree5
            (std::shared_ptr<TNode<UInt, std::shared_ptr<CarModel>>> root, int* types, int *models, int numOfModels, int& count, UInt type_id);

    void inOrderTree5
            (std::shared_ptr<TNode<UInt, std::shared_ptr<CarModel>>> root, int* types, int *models, int numOfModels, int& count, UInt type_id);




};


#endif //HW1_WET_DSW_H
