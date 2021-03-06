#ifndef HW2_WET_TNODE_H
#define HW2_WET_TNODE_H
#include <memory>


#define UInt unsigned int
#define INIT_SIZE 50

template<class K, class T>
class TNode;

template<class K, class T>
class Record {
private:
    std::shared_ptr<TNode<K,T>> root;
    UInt size;
public:
    Record();
    ~Record() = default;
    Record(const Record<K,T>& other) = delete;
    Record& operator=(const Record<K,T>& other) = delete;
    void setSize(UInt num);
    void setRoot(std::shared_ptr<TNode<K,T>> ptr);
    std::shared_ptr<TNode<K,T>> getRoot();
    UInt getSize();
};

template<class K, class T>
Record<K,T>::Record(): root(nullptr), size(1){}

template<class K, class T>
void Record<K,T>::setSize(UInt num){
    size = num;
}

template<class K, class T>
void Record<K,T>::setRoot(std::shared_ptr<TNode<K,T>> ptr){
root = ptr;
}

template<class K, class T>
std::shared_ptr<TNode<K,T>> Record<K,T>::getRoot(){
    return root;
}

template<class K, class T>
UInt Record<K,T>::getSize(){
    return size;
}


template<class K, class T>
class TNode {
    int _height;
    int _bf;
    K _key;
    T _data;
public:
    std::shared_ptr<TNode<K,T>> parent;
    std::shared_ptr<TNode<K,T>> left;
    std::shared_ptr<TNode<K,T>> right;
    std::shared_ptr<Record<K,T>> record;

    TNode(K key, T data, std::shared_ptr<Record<K,T>> rec = nullptr ,std::shared_ptr<TNode> left = nullptr,
          std::shared_ptr<TNode> right = nullptr, std::shared_ptr<TNode> parent = nullptr);
    TNode(const TNode &other);
    TNode& operator=(const TNode &other);
    ~TNode() =default;
    void refresh();
    int calculateHeight();
    int calculateBF();
    int getHeight();
    int getBF();
    const K& getKey();
    T& getValue();
    void setKey(K key);
    void setValue(T value);
    void setLeft(std::shared_ptr<TNode<K,T>>);
    void setRight(std::shared_ptr<TNode<K,T>>);
    bool operator!=(TNode<K,T>& other);
    bool operator==(TNode<K,T>& other);
};


template<class K, class T>
int TNode<K,T>::getHeight() {
    _height = calculateHeight();
    return _height;
}

template<class K, class T>
int TNode<K,T>::getBF() {
    return _bf;
}

template<class K, class T>
const K& TNode<K,T>::getKey() {
    return _key;
}

template<class K, class T>
T& TNode<K,T>::getValue() {
    return _data;
}

template<class K, class T>
void TNode<K,T>::setKey(K key) {
    _key = key;
}

template<class K, class T>
void TNode<K,T>::setValue(T value) {
    _data = value;
}

template<class K, class T>
TNode<K,T>::TNode(K key, T data, std::shared_ptr<Record<K,T>> rec, std::shared_ptr<TNode> left,
                  std::shared_ptr<TNode> right, std::shared_ptr<TNode> parent):
        _key(key),
        _data(data),
        record(rec),
        parent(parent),
        left(left),
        right(right)
{
    _height = this->calculateHeight();
    _bf = this->calculateBF();
}

template<class K, class T>
TNode<K,T>::TNode(const TNode& other):
        _height(other.height),
        _bf(other._bf),
        _key(other.key),
        _data(other.data),
        parent(other.parent),
        left(other.left),
        right(other.right){}

template<class K, class T>
TNode<K, T>& TNode<K,T>::operator=(const TNode<K, T> &other) {
    if(this == &other){ // handling self assignment
        return *this;
    }
    _key = other.key;
    _data = other.data;
    _height = other._height;
    _bf = other._bf;
    right = other.right;
    left = other.left;
    parent = other.parent;
}
template<class K, class T>
void TNode<K,T>::refresh(){
    _height = calculateHeight();
    _bf = calculateBF();
}
template<class K, class T>
int TNode<K,T>::calculateHeight() {
    int l, r, height;
    left == nullptr ? l = -1 : l = left->_height;
    right == nullptr ? r = -1 : r = right->_height;
    r > l ? height = r + 1 : height = l + 1;
    return height;
}

template<class K, class T>
int TNode<K,T>::calculateBF() {
    int l, r;
    left == nullptr ? l = -1 : l = left->_height;
    right == nullptr ? r = -1 : r = right->_height;
    return l - r;
}

template<class K, class T>
void TNode<K,T>::setLeft(std::shared_ptr<TNode<K, T>>left_param) {
    left = left_param;
}

template<class K, class T>
void TNode<K,T>::setRight(std::shared_ptr<TNode<K, T>>right_param) {
    left = right_param;
}

template<class K, class T>
bool TNode<K,T>::operator==(TNode<K,T>& other){
    return other._data == _data;
}

template<class K, class T>
bool TNode<K,T>::operator!=(TNode<K,T>& other){
    return _data != other._data;
}

#endif //HW2_WET_TNODE_H
