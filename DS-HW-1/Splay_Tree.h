//
// Created by Amir on 24/11/2017.
//

#ifndef DS_HW_1_SPLAY_TREE_H
#define DS_HW_1_SPLAY_TREE_H

#include <stdlib.h>
#include <stdio.h>


/***************************************************************************/
/*  Node Declaration                                                       */
/***************************************************************************/

template <class T>
class binaryNode{
        T data;
        binaryNode<N> *parent;
        binaryNode<N> *l_child;
        binaryNode<N> *r_child;
    public:
        binaryNode(): l_child(NULL), r_child(NULL), parent(NULL) {}
        binaryNode(const T & data, binaryNode *left,binaryNode *right):
                            Element (data), l_child(left), r_child(right) {}
        binaryNode() = default;
        friend class Splay_Tree<T>;
}

/***************************************************************************/
/*  Splay tree class                                                       */
/*  Operations:                                                            */
/*
/***************************************************************************/
template<class T>
class Splay_Tree {
    public:
    
    const T

    };
/**---------------Implementation of Splay_tree functions--------------------*/
    /**
    * Splay_Tree constructor
    * Constructs a new empty Splay tree
    */
    Splay_Tree<T>() : root(nullptr), size(0) {};

    /**
    * Splay_Tree copy constructor
    * Constructs a new empty Splay tree
    */
    Splay_Tree<T>(const Splay_Tree<T> &toCopy) : root(nullptr), size(0) {
/***************************************************************************/
/*  Copy ctr implementation                                                */
/***************************************************************************/
    };
};

#endif //DS_HW_1_SPLAY_TREE_H
