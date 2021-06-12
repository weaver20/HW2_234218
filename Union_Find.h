
#ifndef HW2_WET_UNION_FIND_H
#define HW2_WET_UNION_FIND_H
#define UInt unsigned int
#define INIT_SIZE 50
#include "TNode.h"

template<class K, class T>
class Union_Find {

private:
    std::shared_ptr<std::shared_ptr<TNode<K,T>>> elements;
    std::shared_ptr<Record<K,T>> groups;
    UInt counter;
    UInt max_size;

public:
    Union_Find();
    ~Union_Find() = default;
    void makeSet();
    Record<K,T> Find(UInt key);
    void Union(int p, int q);
};

template<class K, class T>
Union_Find<K,T>::Union_Find(): elements(new std::shared_ptr<TNode<K,T>>[INIT_SIZE]),
groups(new Record<K,T>[INIT_SIZE]), counter(0), max_size(INIT_SIZE) {}

template<class K, class T>
void Union_Find<K,T>::makeSet() {
    if(counter == max_size){
        max_size *= 2;
        std::shared_ptr<std::shared_ptr<TNode<K,T>>> new_elements(new std::shared_ptr<TNode<K,T>>[max_size]);
        std::shared_ptr<Record<K,T>> new_groups(new std::shared_ptr<Record<K,T>>[max_size]);
        for(int i = 0; i < max_size/2; i++){
            new_elements[i] = elements[i];
            elements[i] = nullptr;
        }
        elements = nullptr;

        for(int i = 0; i < max_size/2; i++){
            new_groups[i] = groups[i];
            groups[i] = nullptr;
        }
        groups = nullptr;
    }

    T new_obj = new T(counter);
    std::shared_ptr<TNode<K, T>> root_ptr(new TNode<K, T>(counter, new_obj));
    std::shared_ptr<Record<K, T>> rcd(new Record<K, T>(root_ptr));
    groups[counter] = rcd;
    elements[counter] = root_ptr;
    counter++;
}

template<class K, class T>
Record<K,T> Union_Find<K,T>::Find(UInt key){
    std::shared_ptr<TNode<K,T>> it = elements[key];
    while(it->parent){
        it = it->parent;
    }
    return it->record;
}

template<class K, class T>
void Union_Find<K,T>::Union(int p, int q){
    if(groups[p].getSize() < groups[q].getSize()){
        groups[p].setRoot(groups[q].getRoot());
        groups[q].setSize(groups[q].getSize() + groups[p].getSize());
        groups[p] = nullptr;
    }
    else{
        groups[q].setRoot(groups[p].getRoot());
        groups[p].setSize(groups[q].getSize() + groups[p].getSize());
        groups[q] = nullptr;
    }
}


#endif //HW2_WET_UNION_FIND_H
