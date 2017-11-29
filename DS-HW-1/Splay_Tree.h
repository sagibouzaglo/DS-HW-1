//
// Created by Amir on 24/11/2017.
//

#ifndef DS_HW_1_SPLAY_TREE_H
#define DS_HW_1_SPLAY_TREE_H

#include <stdlib.h>
#include <stdio.h>

/***************************************************************************/
/*  Splay tree class                                                       */
/*  Operations:                                                            */
/*  insert - insert node to the tree                                       */
/*  remove - remove node from the tree                                     */
/*  isEmpty - return true if tree is empty                                 */
/***************************************************************************/
template<class T>
class SplayTree {
    /***************************************************************************/
    /*  Node Declaration                                                       */
    /***************************************************************************/
    template<class N>
    class binaryNode {
        N data;
        int key;
        binaryNode<N> *l_child;
        binaryNode<N> *r_child;

        friend class Splay_Tree<T>;

    public:
        binaryNode<N>(const T &data, int key) : data(data), key(key),
                                                l_child(nullptr),
                                                r_child(nullptr) {}

        ~binaryNode<N>() = default;

        binaryNode<N>(const binaryNode<T> &node) : data(node.data),
                                                   key(node.key),
                                                   l_child(node.l_child),
                                                   r_child(node.r_child) {}

        binaryNode<N>() = delete;
    };
    /*******end of node********************/
    /**************************************************************************/
    /*  Splay_tree private  Declaration                */
    /**************************************************************************/
    const binaryNode<N> *root;

    /* Description:   Rotates left_child to be new root
    * Input:         current root
    * Output:        None.
    * Return Values: A pointer to the new root
    */
    binaryNode<T> *rightRotate(binaryNode<T> *source) {
        binaryNode<T> *new_root = source->l_child;
        source->l_child = new_root->r_child;
        new_root->r_child = source;
        return new_root;
    }

    /* Description:   Rotates right_child to be new root
    * Input:         current root
    * Output:        None.
    * Return Values: A pointer to the new root
    */
    binaryNode<T> *leftRotate(binaryNode<T> *source) {
        binaryNode<T> *new_root = source->r_child;
        source->r_child = new_root->l_child;
        new_root->l_child = source;
        return new_root;
    }

    /* Description:   This function returns the pointer to newly assigned root
     *                 if key was found then he will be the new root,if not
     *                 it makes the root the last accessed node while searching
    * Input:         current root
    * Output:        None.
    * Return Values: A pointer to the new root
    */
    binaryNode<T>* splay(binaryNode<T> *root, int key) {
        //root is NULL or key is in root
        if (root == nullptr || root->key == key) return root;

        //Key is in right tree
        if (key > root->key) {
            //Couldnt find key in tree, return the last known root
            if (root->r_child == nullptr) return root;
            /*RR-Zag-Zag rotation*/
            if (key > root->r_child->key) {
                //Make key the new Right_Right
                root->r_child->r_child = splay(root->r_child->r_child, key);
                //Rotate top_down, second rotation will follow
                root= leftRotate(root);
                //RL-Zag-Zig roatation
            } else if (key < root->r_child) {
                //Make key the new Right_Left child
                root->r_child->l_child = splay(root->r_child->l_child, key);
                //Make key the Right_child
                if (root->r_child->l_child != nullptr) {
                    root->r_child = rightRotate(root->r_child);
                }
            }
            //if possiable bring r_child to root.
            return (root->r_child== nullptr)?(root):(leftRotate(root));
        }
            //Key is in left tree
        else {
            //Couldnt find key in tree, return the last known root
            if(root->l_child== nullptr) return root;
            /*LL-Zig-Zig rotatation */
            if(key<root->l_child->key){
                //make Key the new L_L child
                root->l_child->l_child=splay(root->l_child->l_child,key);
                root=rightRotate(root);
            }
                /*LR-Zig-Zag rotatation */
            else if(key>root->l_child){
                root->l_child->r_child=splay(root->l_child->r_child,key);
                if(root->l_child!= nullptr){
                    root->l_child=leftRotate(root->l_child);
                }
            }
            return (root->l_child== nullptr)?(root):(rightRotate(root));
        }
    }



    /**
    void rotateLeft (binaryNode<T>* & node) const;
    void rotateRight (binaryNode<T>* & node) const;
    void splayRoot (const T & target, binaryNode<T>* & root) const;
     **/
public:
    SplayTree<T>() = default;

    ~SplayTree() = default;

    SplayTree<T>(const SplayTree<T> &toCopy) : root(toCopy.root) {}

    /* Description:   This function returns the pointer to newly assigned root
     *                 if key was found then he will be the new root,if not
     *                 it makes the root the last accessed node while searching
    * Input:         current root
    * Output:        None.
    * Return Values: A pointer to the new root
    */
    T& Search(int key){
        binaryNode<T>* new_root=splay(this->root,key);
        //empty Splay tree
        if(new_root== nullptr){
            throw //////////////////////////////////////////////////////////////////////////;
        }
        return new_root->data;
    }

    void Insert(SplayTree<T> &s_t, int key, const T &data);
    /**
        const SplayTree & operator= (const SplayTree & rightSide);
        bool isEmpty() const;
        void insert (const T & data);
        void remove (const T & date);
    **/
};

/**---------------Implementation of Splay_tree functions--------------------*/
void SplayTree<T>::Insert(SplayTree<T> &s_t, int key, const T &data) {

}

/**
* Splay_Tree constructor
* Constructs a new empty Splay tree
*/
Splay_Tree<T>() : root(nullptr), size(0) {};

/**
* Splay_Tree copy constructor
* Constructs a new empty Splay tree
*/
Splay_Tree<T>(const Splay_Tree <T> &toCopy) : root(nullptr), size(0) {
/***************************************************************************/
/*  Copy ctr implementation                                                */
/***************************************************************************/
};
};

/***************************************************************************/
/*  Checks if tree is Empty                                                 */
/***************************************************************************/
template<class T>
bool SplayTree<T>::isEmpty() const {
    return root == emptyNode;
}

#endif //DS_HW_1_SPLAY_TREE_H
