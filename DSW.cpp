
#include "DSW.h"

DSW::DSW():
        _tree1(new AVL_Tree<UInt,std::shared_ptr<class CarType>>()),
        _tree2(new AVL_Tree<class Tree2_Key, std::shared_ptr<class CarType>>()),
        _tree3(new AVL_Tree<class Tree3_Key, std::shared_ptr<CarModel>>()),
        _tree4(new AVL_Tree<class Tree4_Key,class Tree4_Data>()),
        _num_of_models(ZERO){}

StatusType DSW::AddCarType(int typeID, int numOfModels){
    if(typeID <= ZERO or numOfModels <= ZERO){
        return INVALID_INPUT;
    }
    if(_tree1->findNodeWithKey(typeID) != nullptr){
        return FAILURE;
    }
    try {
        std::shared_ptr<CarType> car_type(new CarType(typeID, numOfModels));
        _tree1->insert(car_type->getID(), car_type);
        Tree2_Key key2(car_type->getBestSellerModel()->getSales(),car_type->getID());
        _tree2->insert(key2, car_type);
        Tree4_Key key4(ZERO, car_type->getID());
        Tree4_Data data4(car_type);
        _tree4->insert(key4, data4);
    }
    catch(std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
    _num_of_models += numOfModels;
    return SUCCESS;
}

StatusType DSW::RemoveCarType(int typeID) {
    if(typeID <= 0){
        return INVALID_INPUT;
    }
    try {
        std::shared_ptr<CarType> car_ptr;
        if(_tree1->findNodeWithKey(typeID)) {
            car_ptr = _tree1->findNodeWithKey(typeID)->getValue();
        }
        else{
            throw NodeNotInTree();
        }
        Tree2_Key key2(car_ptr->getBestSellerModel()->getSales(),car_ptr->getID());
        _tree1->findNodeWithKey(typeID)->setValue(nullptr);
        _tree1->remove(typeID);
        _tree2->findNodeWithKey(key2)->setValue(nullptr);
        _tree2->remove(key2);
        std::shared_ptr<CarModel>* model_arr = car_ptr->getModelArr();
        for(UInt i = 0; i < car_ptr->getNumOfModels(); i++){
            Tree3_Key key3(model_arr[i]->getRate(), car_ptr->getID(), i);
            if(_tree3->findNodeWithKey(key3)){
                _tree3->findNodeWithKey(key3)->setValue(nullptr);
                _tree3->remove(key3);
            }
        }
        Tree4_Key key4(ZERO, car_ptr->getID());
        if(_tree4->findNodeWithKey(key4)) {
            _tree4->remove(key4);
        }
        _num_of_models -= car_ptr->getNumOfModels();
        long count = car_ptr.use_count();
    }
    catch (std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
    catch (NodeNotInTree&){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType DSW::MakeComplaint(int typeID, int modelID, int t){
    if(t <= 0 or modelID < 0 or typeID <= 0){
        return INVALID_INPUT;
    }
    try {
        if(not _tree1->findNodeWithKey(typeID)){
            throw NodeNotInTree();
        }
        if(_tree1->findNodeWithKey(typeID)->getValue()->getNumOfModels() <=modelID){
            return FAILURE;
        }
        std::shared_ptr<CarType> car_ptr(_tree1->findNodeWithKey(typeID)->getValue());
        std::shared_ptr<CarModel> model = car_ptr->getModelArr()[modelID];
        int old_rate = model->getRate();
        model->complaint(t);
        Tree4_Key key4(ZERO, typeID);
        if(model->getRate() == 0){
            Tree3_Key key3(old_rate, typeID, modelID);
            _tree3->remove(key3);
            Tree4_Data data4(car_ptr);
            _tree4->insert(key4, data4);
        }
        else{
            if(old_rate == 0){
                _tree4->findNodeWithKey(key4)->getValue()._model_tree->remove(modelID);
                Tree3_Key key3(model->getRate(), typeID, modelID);
                _tree3->insert(key3, model);
            }
            else {
                Tree3_Key key3_old(old_rate, typeID, modelID);
                Tree3_Key key_new(model->getRate(), typeID, modelID);
                _tree3->remove(key3_old);
                _tree3->insert(key_new, model);
            }
        }
    }
    catch (std::bad_alloc&){
        return FAILURE;
    }
    catch (NodeNotInTree&){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType DSW::SellCar(int typeID, int modelID){
    if(modelID < 0 or typeID <= 0){
        return INVALID_INPUT;
    }
    try{
        if(not _tree1->findNodeWithKey(typeID)){
            throw NodeNotInTree();
        }
        std::shared_ptr<CarType> car_type(_tree1->findNodeWithKey(typeID)->getValue());
        UInt model_id = (UInt) modelID;
        if(model_id >= car_type->getNumOfModels()){
            return FAILURE;
        }

        // Checking most sold model
        std::shared_ptr<CarModel> car_model(car_type->getModelArr()[modelID]);
        std::shared_ptr<CarModel> best_seller_model(car_type->getBestSellerModel());
        std::shared_ptr<CarModel> old_best_seller = _tree1->findNodeWithKey(typeID)->getValue()->getBestSellerModel();

        int old_rate = car_model->getRate();
        car_model->sell();
        bool changed = false;
        bool identical = false;
        if(car_model->getSales() >= best_seller_model->getSales()){
            if(car_model->getSales() > best_seller_model->getSales()) {
                car_type->setBestSeller(car_model);
                changed = true;
            }
            else{
                if(car_model->getModelID() < best_seller_model->getModelID()){
                    car_type->setBestSeller(car_model);
                    changed = true;
                }
            }
        }
        if(car_model == best_seller_model){
            identical = true;
        }

        // Handling _tree2
        if(changed) {
            Tree2_Key key2_old(best_seller_model->getSales(), best_seller_model->getTypeID());
            Tree2_Key key2_new(car_model->getSales(), typeID);
            _tree2->remove(key2_old);
            _tree2->insert(key2_new, car_type);
        }
        else if(identical){
            Tree2_Key key2_old(best_seller_model->getSales() - 1, best_seller_model->getTypeID());
            Tree2_Key key2_new(car_model->getSales(), typeID);
            _tree2->remove(key2_old);
            _tree2->insert(key2_new, car_type);
        }

        // Handling tree3 and tree4 if necessary
        if(old_rate != ZERO){
            Tree3_Key key3_old(old_rate, typeID, modelID);
            Tree3_Key key_new(car_model->getRate(), typeID, modelID);
            _tree3->remove(key3_old);
            if(car_model->getRate() == 0){
                Tree4_Key key4(ZERO, typeID);
                std::shared_ptr<TNode<Tree4_Key, Tree4_Data>> to_find(_tree4->findNodeWithKey(key4));
                if(to_find) {
                    Tree4_Data data4 = to_find->getValue();
                    data4._model_tree->insert(modelID, car_model);
                }
                else{
                    Tree4_Data to_insert(car_type, false);
                    _tree4->insert(key4, to_insert);
                    Tree4_Data insertion = _tree4->findNodeWithKey(key4)->getValue();
                    insertion._model_tree->insert(modelID, car_model);
                }
            }
            else _tree3->insert(key_new, car_model);
        }

        // Handling tree4
        else{
            Tree4_Key key4(ZERO, typeID);
            Tree4_Data to_find(_tree4->findNodeWithKey(key4)->getValue());
            if(not to_find._model_tree or not to_find._model_tree->getRoot()){
                _tree4->remove(key4);
            }
            else to_find._model_tree->remove(modelID);
            Tree3_Key key_new(car_model->getRate(), typeID, modelID);
            _tree3->insert(key_new, car_model);
        }
    }
    catch (std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
    catch(NodeNotInTree&){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType DSW::GetBestSellerModelByType(int typeID, int* modelID){
    if(typeID < 0){
        return INVALID_INPUT;
    }
    try {
        if(not _tree1->getRoot()){
            throw NodeNotInTree();
        }
        if(typeID == 0){
            *modelID = _tree2->getRightMost()->getValue()->getBestSellerModel()->getModelID();
        }
        else{
            if(not _tree1->findNodeWithKey(typeID)){
                throw NodeNotInTree();
            }
            *modelID = _tree1->findNodeWithKey(typeID)->getValue()->getBestSellerModel()->getModelID();
        }
    }
    catch (std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
    catch (NodeNotInTree&){
        return FAILURE;
    }
    return SUCCESS;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


StatusType DSW::GetWorstModels(int numOfModels, int *types, int *models){
    UInt num_of_models = (UInt) numOfModels;
    if(numOfModels <= 0){
        return INVALID_INPUT;
    }
    if(num_of_models > _num_of_models){
        return FAILURE;
    }
    try {
        int count = 0;
        bool visited = false;
        modifiedInOrderTree3(_tree3->getLeftMost(), types, models, numOfModels, count, visited);
    }
    catch(std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}


void DSW::modifiedInOrderTree3
        (std::shared_ptr<TNode<Tree3_Key,
                std::shared_ptr<CarModel>>> root, int* types, int *models, int numOfModels, int& count, bool& tree4_visited){
    if(count >= numOfModels){
        return;
    }
    if(not root){
        if(tree4_visited){
            return;
        }
        else{
            tree4_visited = true;
            modifiedInOrderTree4(_tree4->getLeftMost(), types, models, numOfModels, count);
        }
    }
    else{
        if(root->getValue()->getRate() < 0){
            types[count] = root->getKey().getTypeID();
            models[count] = root->getValue()->getModelID();
            count++;
            if(root->right){
                inOrderTraversalTree3(root->right, types, models, numOfModels, count, tree4_visited);
            }
            modifiedInOrderTree3(root->parent, types, models, numOfModels, count, tree4_visited);
        }
        else {
            if(not tree4_visited) {
                tree4_visited = true;
                modifiedInOrderTree4(_tree4->getLeftMost(), types, models,
                                     numOfModels, count);
            }
            if(count < numOfModels){
                types[count] = root->getKey().getTypeID();
                models[count] = root->getValue()->getModelID();
                count++;
            }
            else{
                return;
            }
            inOrderTraversalTree3(root->right, types, models, numOfModels, count, tree4_visited);
            modifiedInOrderTree3(root->parent, types, models, numOfModels, count, tree4_visited);
        }
    }
}

void DSW::inOrderTraversalTree3
        (std::shared_ptr<TNode<Tree3_Key, std::shared_ptr<CarModel>>> root, int* types, int *models, int numOfModels, int& count, bool& tree4_visited){
    if(count >=numOfModels){
        return;
    }
    if(not root){
        return;
    }
    else{
        inOrderTraversalTree3(root->left, types, models, numOfModels, count, tree4_visited);
        if(root->getValue()->getRate() < 0){
            if(count < numOfModels){
                types[count] = root->getKey().getTypeID();
                models[count] = root->getValue()->getModelID();
                count++;
            }
            else{
                return;
            }
            inOrderTraversalTree3(root->right, types, models, numOfModels, count, tree4_visited);
        }
        else {
            if (not tree4_visited) {
                tree4_visited = true;
                modifiedInOrderTree4(_tree4->getLeftMost(), types, models,
                                     numOfModels, count);
            }
            if (count < numOfModels) {
                types[count] = root->getKey().getTypeID();
                models[count] = root->getValue()->getModelID();
                count++;
            }
            else{
                return;
            }
            inOrderTraversalTree3(root->right, types, models, numOfModels, count, tree4_visited);
        }
    }
}

void DSW::modifiedInOrderTree4
        (std::shared_ptr<TNode<Tree4_Key, Tree4_Data>> root, int* types, int *models, int numOfModels, int& count){
    if(not root){
        return;
    }
    else{
        if(count < numOfModels){
            if(root->getValue()._model_tree){
                modifiedInOrderTree5(root->getValue()._model_tree->getLeftMost(),
                                     types,models,numOfModels,count,root->getValue()._car_type->getID());
            }
        }
        else{
            return;
        }
        if(root->right){
            inOrderTraversalTree4(root->right, types, models, numOfModels, count);
        }
        modifiedInOrderTree4(root->parent, types, models, numOfModels, count);
    }

}

void DSW::inOrderTraversalTree4
        (std::shared_ptr<TNode<Tree4_Key, Tree4_Data>> root, int* types, int *models, int numOfModels, int& count){
    if(count >= numOfModels) {
        return;
    }
    if(not root){
        return;
    }
    else{
        inOrderTraversalTree4(root->left, types, models, numOfModels, count);
        if(count < numOfModels) {
            modifiedInOrderTree5(root->getValue()._model_tree->getLeftMost(),types,models,numOfModels,count,root->getValue()._car_type->getID());
        }
        else{
            return;
        }
        inOrderTraversalTree4(root->right, types, models, numOfModels, count);
    }
}

void DSW::modifiedInOrderTree5
        (std::shared_ptr<TNode<UInt, std::shared_ptr<CarModel>>> root, int* types, int *models, int numOfModels, int& count, UInt type_id){
    if(not root){
        return;
    }
    else{
        if(count < numOfModels){
            types[count] = type_id;
            models[count] = root->getValue()->getModelID();
            count++;
        }
        else{
            return;
        }
        if(root->right){
            inOrderTree5(root->right, types, models, numOfModels, count, type_id);
        }
        modifiedInOrderTree5(root->parent, types, models, numOfModels, count, type_id);
    }
}


void DSW::inOrderTree5
        (std::shared_ptr<TNode<UInt, std::shared_ptr<CarModel>>> root, int* types, int *models, int numOfModels, int& count, UInt type_id){
    if(count >= numOfModels) {
        return;
    }
    if(not root){
        return;
    }
    else{
        inOrderTree5(root->left, types, models, numOfModels, count, type_id);
        if(count < numOfModels) {
            types[count] = type_id;
            models[count] = root->getValue()->getModelID();
            count++;
        }
        else{
            return;
        }
        inOrderTree5(root->right, types, models, numOfModels, count, type_id);
    }
}

DSW::~DSW() {
    _tree1 = nullptr;
    _tree2 = nullptr;
    _tree3 = nullptr;
    _tree4 = nullptr;
}












