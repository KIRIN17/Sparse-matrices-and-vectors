#pragma once
#include "Pair.h"

template<typename T>
class tree_elem {
public:
    T DATA;
    Pair<int,int> indices;
    tree_elem *M_LEFT;
    tree_elem *M_RIGHT;

    tree_elem(const Pair<int,int>& indices_,T DATA_) : indices(indices_),DATA(DATA_){
        M_LEFT = NULL;
        M_RIGHT = NULL;
    }
    tree_elem(T key,tree_elem<T>* left,tree_elem<T>* right){//конструктор для копирования конкретного узла
        DATA = key;
        M_LEFT = left;
        M_RIGHT = right;
    }

};