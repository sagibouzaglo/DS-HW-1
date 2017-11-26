//
// Created by Amir on 24/11/2017.
//

#ifndef DS_HW_1_SPLAY_TREE_H
#define DS_HW_1_SPLAY_TREE_H

#include <stdlib.h>
#include <stdio.h>

template<class T>
class Splay_Tree {
    template<class N>
    class Node {
        N data;
        Node<N> *parent;
        Node<N> *l_child;
        Node<N> *r_child;

        friend class Iterator;

        friend class Splay_Tree;

    public:
        Node<N>() = delete;

        /**
         * Node constructor
         * Constructs a new Node with the specified data.
         * @param data the data of the Node
         */
        Node<N>(const N &data) : data(data), parent(nullptr),
                                 l_child(nullptr), r_child(nullptr) {};

        /**
        * Node copy constructor
        * construct a Node with same data and Null references
        * @param toCopy the Node to copy
        */
        Node<N>(const Node<N> &toCopy) : data(toCopy.data),
                                         parent(toCopy.parent),
                                         l_child(toCopy.l_child),
                                         r_child(toCopy.r_child) {};

        /**
        * Node default destructor
        */
        ~Node<N>() = default;
/***************************************************************************/
/*  Implemant missing things in Node<N>                                    */
/***************************************************************************/
    };

/***************************************************************************/
/*  list implementation                                                    */
/***************************************************************************/
    Node<T> *root;
    unsigned int size;
public:
    /**---------------Public List Parts--------------------*/
    /**---------------internal iterator class--------------------*/
    class Iterator {
        Node<T> *current;
        const Splay_Tree<T> *tree;

        /** Empty Constructor for Iterator as private
        * @param
        * @return
        */
        Iterator(const Splay_Tree<T> &tree) : current(tree.root),
                                              tree(&tree) {};
        friend class Splay_Tree<T>;
    public:


        //Iterator destructor
        ~Iterator() = default;

        //Iterator copy constructor
        Iterator(const Iterator &iterator) = default;

        //Iterator assignment operator
        Iterator &operator=(const Iterator &iterator)= default;

        /** Operator*() for iterator
        * @param iterator object
        */
        T &operator*() const {
            if (this->current == nullptr) {
                throw mtm::ListExceptions::ElementNotFound();//////////////////////////////////
            }
            return this->current->data;
        }

        /** iterator getRight
       * @param iterator object
       */
        Iterator &getRight() {
            if (this->current == nullptr) {
                throw mtm::ListExceptions::ElementNotFound();//////////////////////////////////
            }
            this->current = this->current->r_child;
            return *this;
        }

        /** iterator getLeft
        * @param iterator object
        */
        Iterator &getLeft() {
            if (this->current == nullptr) {
                throw mtm::ListExceptions::ElementNotFound();//////////////////////////////////
            }
            this->current = this->current->l_child;
            return *this;
        }

        /** iterator getParent
        * @param iterator object
        */
        Iterator &getParent() {
            if (this->current == nullptr) {
                throw mtm::ListExceptions::ElementNotFound();//////////////////////////////////
            }
            this->current = this->current->parent;
            return *this;
        }

        /** Operator==  for iterator
      * @param iterator to be checked to
      */
        bool operator==(const Iterator &iterator) const {
            return ((this->tree == iterator.tree) &&
                    this->current == iterator.current);
        }

        /** Operator!=  for iterator
      * @param iterator to be checked to
      */
        bool operator!=(const Iterator &iterator) const {
            return !(*this == iterator);
        }

    };
    /**---------------End of internal  Iterator--------------------*/
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
