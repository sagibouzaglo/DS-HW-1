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

    class KeyDoesntExists : public std::runtime_error {
    public:
        KeyDoesntExists() : std::runtime_error("Key Doesnt exists") {}
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
    class Vertex {
        N data;
        int key;
        Vertex<N> *left;
        Vertex<N> *right;

        friend class SplayTree;

    public:
        Vertex<N>(const T &data, int key) : data(data), key(key),
                                            left(nullptr),
                                            right(nullptr) {}

        Vertex<N>(const T &data, int key, Vertex<T> *left, Vertex<T> *right) :
                data(data), key(key), left(left), right(right) {}

        ~Vertex<N>() = default;

        Vertex<N>(const Vertex<T> &node) : data(node.data),
                                           key(node.key),
                                           left(node.left),
                                           right(node.right) {}

        Vertex<N>() = delete;
    };
    /*******end of node********************/
    /**************************************************************************/
    /*  Splay_tree private  Declaration                */
    /**************************************************************************/
    Vertex<T> *root;

    /* Description:   Rotates left_child to be new root
    * Input:         current root
    * Output:        None.
    * Return Values: A pointer to the new root
    */
    Vertex<T> * rightRotate(Vertex<T> *source) {
        Vertex<T> *new_root = source->left;
        source->left = new_root->right;
        new_root->right = source;
        source=new_root;
        return source;
    }

    /* Description:   Rotates right_child to be new root
    * Input:         current root
    * Output:        None.
    * Return Values: A pointer to the new root
    */
    Vertex<T> *leftRotate(Vertex<T> *source) {
        Vertex<T> *new_root = source->right;
        source->right = source->right->left;
        new_root->left = source;
        return new_root;
    }

    /* Description:   This function returns the pointer to newly assigned root
     *                 if key was found then he will be the new root,if not
     *                 it makes the root the last accessed node while searching
    * Input:         current root
    * Output:        None.
    * Return Values: A pointer to the new root
    */
    Vertex<T> *splay(Vertex<T> *root, int key) {
        //root is NULL or key is in root
        if (root == nullptr || root->key == key) return root;

        //Key is in right tree
        if (key > root->key) {
            //Couldnt find key in tree, return the last known root
            if (root->right == nullptr) return root;
            /*RR-Zag-Zag rotation*/
            if (key > root->right->key) {
                //Make key the new Right_Right
                root->right->right = splay(root->right->right, key);
                //Rotate top_down, second rotation will follow
                root = leftRotate(root);
                //RL-Zag-Zig roatation
            } else if (key < root->right->key) {
                //Make key the new Right_Left child
                root->right->left = splay(root->right->left, key);
                //Make key the Right_child
                if (root->right->left != nullptr) {
                    root->right = rightRotate(root->right);
                }
            }
            //if possiable bring r_child to root.
            return (root->right == nullptr) ? (root) : (leftRotate(root));
        }
            //Key is in left tree
        else {
            //Couldnt find key in tree, return the last known root
            if (root->left == nullptr) return root;
            /*LL-Zig-Zig rotatation */
            if (key < root->left->key) {
                //make Key the new L_L child
                root->left->left = splay(root->left->left, key);
                root = rightRotate(root);
            }
                /*LR-Zig-Zag rotatation */
            else if (key > root->left->key) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right != nullptr) {
                    root->left->right = leftRotate(root->left);
                }
            }
            return (root->left == nullptr) ? (root) : (root=rightRotate(root));
        }
    }


    /* Description:   This function splits root to 2 trees around a given
    *  key.
    * Input:           The root you want to split
     *              The key around to split, pointer to aftermath left_root.
     *              ,pointer to aftermath right_root
    *               2 pointers for the left and right tree
    * Output:        None.
    * Return Values: false if key wasnt found, true if key is in tree
    */
    bool split(Vertex<T> *root, Vertex<T> *&left, Vertex<T> *&right, int key) {
        if (root == nullptr) {
            throw TreeExceptions::TreeIsEmpty();
        }
        //splay to the root
        root=splay(root, key);
        //root is smaller then key
        if (root->key < key) {
            right = root->right;
            left = root;
            left->right = nullptr;
            return false;
        }
            //root is bigger than key
        else if (root->key > key) {
            left = root->left;
            right = root;
            right->left = nullptr;
            return false;
        }
            //root equals key
        else {
            left = root->left;
            right = root->right;
            return true;
        }
    }

    /* Description:   This function joins "this" tree with a "BiggerTree"
     * meaning all keys in "BiggerTree" are bigger then all keys in "this" Tree
    * Input:         The "Bigger Tree" to join
    * Output:        None.
    * Return Values: None.
    */
    void join(SplayTree<T> &BiggerTree) {
    }


public:
    SplayTree<T>():root(nullptr){}

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
        this->root= splay(this->root, key);
        if (this->root->key != key) {
            throw TreeExceptions::KeyNotFound();
        }
        return this->root->data;
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
        Vertex<T> *current = this->root;
        while (current->left != nullptr) {
            current = current->left;
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
        Vertex<T> *current = this->root;
        while (current->right != nullptr) {
            current = current->right;
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
    bool Insert(int key, const T &data) {
        if (this->root == nullptr) {
            this->root=new Vertex<T>(data,key);
            return true;
        }
        Vertex<T> *right, *left;
        //Key wasnt found
        if (!(split(this->root, left, right, key))) {
            Vertex<T>* new_root=new Vertex<T>(data,key,left,right);
            this->root=new_root;
            return true;
        }
        //Key exists
        else{
            throw TreeExceptions::KeyExists();
        }
    }

    /* Description:   This function deletes the given key from the S_T
     * Input:         Data to be saved
    *               key in dictionary
    * Output:        None.
    * Exceptions:    KeyDoesntExists if the given key doesnt exists
    * Return Values: None
*/
    void Delete(int key) {
    }
};

/**---------------Implementation of Splay_tree functions--------------------*/

#endif //DS_HW_1_SPLAY_TREE_H
