//
// Created by Amir on 24/11/2017.
//

#ifndef DS_HW_1_SPLAY_TREE_H
#define DS_HW_1_SPLAY_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

namespace TreeExceptions {
    class KeyNotFound : public std::runtime_error {
    public:
        KeyNotFound() : std::runtime_error("Key not found") {}
    };

    class TreeIsEmpty : public std::runtime_error {
    public:
        TreeIsEmpty() : std::runtime_error("Tree is Empty") {}
    };
    class KeyExists : public std::runtime_error {
    public:
        KeyExists() : std::runtime_error("Key already exists") {}
    };

}
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

    SplayTree<T>(binaryNode<T>* root):root(root){}

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
    binaryNode<T> *splay(binaryNode<T> *root, int key) {
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
                root = leftRotate(root);
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
            return (root->r_child == nullptr) ? (root) : (leftRotate(root));
        }
            //Key is in left tree
        else {
            //Couldnt find key in tree, return the last known root
            if (root->l_child == nullptr) return root;
            /*LL-Zig-Zig rotatation */
            if (key < root->l_child->key) {
                //make Key the new L_L child
                root->l_child->l_child = splay(root->l_child->l_child, key);
                root = rightRotate(root);
            }
                /*LR-Zig-Zag rotatation */
            else if (key > root->l_child) {
                root->l_child->r_child = splay(root->l_child->r_child, key);
                if (root->l_child != nullptr) {
                    root->l_child = leftRotate(root->l_child);
                }
            }
            return (root->l_child == nullptr) ? (root) : (rightRotate(root));
        }
    }

    /* Description:   This function joins "this" tree with a "BiggerTree"
     * meaning all keys in "BiggerTree" are bigger then all keys in "this" Tree
    * Input:         The "Bigger Tree" to join
    * Output:        None.
    * Return Values: None.
    */
    void join(const SplayTree<T> &BiggerTree) {
        this->Find_Max();
        assert(this->root->r_child== nullptr);
        this->root->r_child=BiggerTree.root;
    }

    /* Description:   This function splits "this" tree to 2 trees around a given
     *  key.
    * Input:         The key around to split.
     *               a pointer where the Bigger tree will be allocated
    * Output:        None.
    * Return Values: None.
    */
    void split(int key,SplayTree<T>* bigTree) {
        //Bring key to root
        this->Search(key);
        //Make A second Bigger tree from right sub-tree
        bigTree = new SplayTree(this->root->r_child);
        //make "this" the small tree if its maximum as root, therefor its
        // right child in NULL.
        this->root->r_child= nullptr;
    }

public:
    SplayTree<T>() = default;

    ~SplayTree() = default;

    SplayTree<T>(const SplayTree<T> &toCopy) : root(toCopy.root) {}

    /* Description:   This function returns the data in the indicated key if
     * found
    * Input:         the wanted key
    * Output:        None.
    * Exceptions:    KeynotFound- if the given key wasnt found
    *               TreeIsEmpty- if this is an empty tree
    * Return Values: A pointer to the new root
    */
    T &Search(int key) {
        if (this->root == nullptr) {
            throw TreeExceptions::TreeIsEmpty();
        }
        binaryNode<T> *new_root = splay(this->root, key);
        if (new_root->key != key) {
            throw TreeExceptions::KeyNotFound();
        }
        return new_root->data;
    }

    /* Description:   This function returns the minimum key
    * Input:         None.
    * Output:        None.
    * Exceptions:    TreeIsEmpty- if this is an empty tree
    * Return Values: The minimum key
    */
    int Find_Min() {
        if (this->root == nullptr) {
            throw TreeExceptions::TreeIsEmpty();
        }
        binaryNode<T> *current = this->root;
        while (current->l_child != nullptr) {
            current = current->l_child;
        }
        splay(this->root, current->key);
        return this->root->key;
    }

    /* Description:   This function returns the maximum key
    * Input:         None.
    * Output:        None.
    * Exceptions:    TreeIsEmpty- if this is an empty tree
    * Return Values: The maximum key
    */
    int Find_Max() {
        if (this->root == nullptr) {
            throw TreeExceptions::TreeIsEmpty();
        }
        binaryNode<T> *current = this->root;
        while (current->r_child != nullptr) {
            current = current->r_child;
        }
        splay(this->root, current->key);
        return this->root->key;
    }

    /* Description:   This function inserts new data  with a given
     * key to the Splay Tree
    * Input:         Data to be saved
     *               key in dictionary
    * Output:        None.
    * Exceptions:    KeyExists if the given key already exists
    * Return Values: None
    */
    void Insert(int key, const T &data) {
        SplayTree<T>* BigTree;
        this->split(key,BigTree);
        //The wanted key exists
        if(this->root->key==key){
            this->join(BigTree);
            delete BigTree;
            throw TreeExceptions::KeyExists();
        }
        binaryNode<T>* new_root=binaryNode<T>(data,key);
        new_root->l_child=this->root;
        new_root->r_child=BigTree->root;
        this->root=new_root;
        delete BigTree;
    }
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

/***************************************************************************/
/*  Checks if tree is Empty                                                 */
/***************************************************************************/
template<class T>
bool SplayTree<T>::isEmpty() const {
    return root == emptyNode;
}

#endif //DS_HW_1_SPLAY_TREE_H
