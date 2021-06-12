#ifndef UNTITLED1_AVL_EXCEPTIONS_H
#define UNTITLED1_AVL_EXCEPTIONS_H
#include "iostream"

class AVL_Exception: public std::exception{};

class NullParent: public std::exception{};

class TreeBadRemoval: public std::exception{};

class NodeNotInTree : public std::exception{};

#endif //UNTITLED1_AVL_EXCEPTIONS_H
