//
// Created by Amir on 24/11/2017.
//

#ifndef DS_HW_1_SPLAY_TREE_H
#define DS_HW_1_SPLAY_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define nullptr 0

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
        Vertex<N> *left;
        Vertex<N> *right;
        friend class SplayTree;

    public:
        Vertex<N>(const T &data) : data(data),
                                            left(nullptr),
                                            right(nullptr) {}

        Vertex<N>(const T &data, Vertex<T> *left, Vertex<T> *right) :
                data(data), left(left), right(right) {}
/*
        ~Vertex<N>(){
            delete (&(this->data));//////////////////////////////////////////////////////
        }
        */

        Vertex<N>(const Vertex<T> &node) : data(node.data),
                                           left(node.left),
                                           right(node.right) {}
    };
    /*******end of node********************/
    /**************************************************************************/
    /*  Splay_tree private  Declaration                */
    /**************************************************************************/
    Vertex<T> *root;

    SplayTree<T>(Vertex<T>* root):root(root){}

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
        source=new_root;
        return source;
    }

    /* Description:   This function returns the pointer to newly assigned root
     *                 if key was found then he will be the new root,if not
     *                 it makes the root the last accessed node while searching
    * Input:         1)current root
     *               2)the data to compare to
     *               3)Function object "compare" function-
     *               that should give 1 if second arg is bigger 0 if equal and
     *               -1 if first arg is bigger.
    * Output:        None.
    * Return Values: A pointer to the new root
    */
    template <class Compare>
    Vertex<T> *splay(Vertex<T> *root,const T& check, const Compare& compare) {
        //root is NULL or key is in root
        if (root == nullptr || !(compare(root->data,check)) ) return root;

        //Key is in right tree
        if ((compare(root->data,check)>0)) {
            //Couldnt find key in tree, return the last known root
            if (root->right == nullptr) return root;
            /*RR-Zag-Zag rotation*/
            if ((compare(root->right->data,check)>0)) {
                //Make key the new Right_Right
                root->right->right = splay(root->right->right,check,compare);
                //Rotate top_down, second rotation will follow
                root = leftRotate(root);
                //RL-Zag-Zig roatation
            } else if ((compare(root->right->data,check)<0)) {
                //Make key the new Right_Left child
                root->right->left = splay(root->right->left,check,compare);
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
            if ((compare(root->left->data,check)<0)) {
                //make Key the new L_L child
                root->left->left = splay(root->left->left,check,compare);
                root = rightRotate(root);
            }
                /*LR-Zig-Zag rotatation */
            else if ((compare(root->left->data,check)>0)) {
                root->left->right = splay(root->left->right,check,compare);
                if (root->left->right != nullptr) {
                    root->left = leftRotate(root->left);
                }
            }
            return (root->left == nullptr) ? (root) : (rightRotate(root));
        }
    }


    /* Description:   This function splits root to 2 trees around a given
    *  key.
    * Input:         1)The root you want to split
     *               2)the data to compare to
     *               3)Function object "compare" function-
     *               that should give 1 if second arg is bigger 0 if equal and
     *               -1 if first arg is bigger.
     *               4)pointer to aftermath left_root.
     *              5)pointer to aftermath right_root
    * Output:        None.
    * Return Values: false if key wasnt found, true if key is in tree
    */
    template <class Compare>
    bool split(Vertex<T> *root, Vertex<T> *&left, Vertex<T> *&right,const T& check, const Compare& compare) {
        if (root == nullptr) {
            return false;
        }
        //splay to the root
        root=splay(root,check,compare);
        //root is smaller then key
        if ((compare(root->data,check)>0)) {
            right = root->right;
            left = root;
            left->right = nullptr;
            return false;
        }
            //root is bigger than key
        else if ((compare(root->data,check)<0)) {
            left = root->left;
            right = root;
            right->left = nullptr;
            return false;
        }
            //root equals key
        else {
            this->root=root;
            left = root->left;
            right = root->right;
            return true;
        }
    }

    /* Description:   This function joins "this" tree with a "BiggerTree"
     * meaning all keys in "BiggerTree" are bigger then all keys in "this" Tree
    * Input:         1) A vertex pointer for the left tree
     *               2) A vertex pointer for the right tree
     *               3)Function object "compare" function-
     *               that should give 1 if second arg is bigger 0 if equal and
     *               -1 if first arg is bigger.
    * Output:        None.
    * Return Values: new root pointer.
    */
    template <class Compare>
    Vertex<T>* join(Vertex<T>* T1,Vertex<T>* T2, const Compare& compare) {
        Vertex<T>* current=T1;
        if(current!=nullptr){
            while (current->right!=nullptr){
                current=current->right;
            }
            T1=splay(T1,current->data,compare);
        }
        current=T2;
        if(current!=nullptr){
            while (current->left!=nullptr){
                current=current->left;
            }
            T2=splay(T2,current->data,compare);
        }
        Vertex<T>* new_root;
        if(T1!= nullptr) {
            T1->right = T2;
            new_root=T1;
        } else{
            new_root=T2;
        }
        return new_root;
    }
    /* Description:   This function does an InOrder Traversal on a given root
     *                and use the function that is given on each vertex
* Input:         1) to root to start from
 *               2)Function object "function" function-
 *               that should do whatever you want on a given data
* Output:        None.
* Return Values: None.
*/
    template <class Function>
    void inOrderTraversal(Vertex<T>* root, const Function& func){
        if(root== nullptr) return;
        inOrderTraversal(root->left,func);
        func(root->data);
        inOrderTraversal(root->right,func);
        return;
    }
    void postOrderDemolition(Vertex<T>* root){
        if(root== nullptr){
            return;
        }
        postOrderDemolition(root->left);
        postOrderDemolition(root->right);
        delete root;
    }

public:
    SplayTree<T>():root(nullptr){}

    ~SplayTree(){
        postOrderDemolition(this->root);
    }

    SplayTree<T>(const SplayTree<T> &toCopy) : root(toCopy.root) {}///////////////////////////////////////////////

    /* Description:   This function returns the data in the indicated key if
     * found
    * Input:         the wanted key
    * Output:        None.
    * Exceptions:    KeynotFound- if the given key wasnt found
    *               TreeIsEmpty- if this is an empty tree
    * Return Values: true if key was found
     *               false if not
    */
    template <class Compare>
    bool Search(const T& toCheck, const Compare& compare) {
        if (this->root == nullptr) {
            return false;
        }
        this->root= splay(this->root,toCheck,compare);
        return compare(root->data,toCheck)==0 ;
    }

    /* Description:   This function returns the minimum key
    * Input:         None.
    * Output:        None.
    * Exceptions:    TreeIsEmpty- if this is an empty tree
    * Return Values: The minimum key
    */
    template <class Compare>
    void Find_Min(const Compare& compare) {
        if (this->root == nullptr) {
            return ;
        }
        Vertex<T> *current = this->root;
        while (current->left != nullptr) {
            current = current->left;
        }
        this->root=splay(this->root, current->data,compare);
    }

    /* Description:   This function returns the maximum key
    * Input:         None.
    * Output:        None.
    * Exceptions:    TreeIsEmpty- if this is an empty tree
    * Return Values: The maximum key
    */
    template <class Compare>
    void Find_Max(const Compare& compare) {
        if (this->root == nullptr) {
            return ;
        }
        Vertex<T> *current = this->root;
        while (current->right != nullptr) {
            current = current->right;
        }
        this->root=splay(this->root, current->data,compare);
    }

    /* Description:   This function inserts new data  with a given
     * key to the Splay Tree
    * Input:         Data to be saved
     *               key in dictionary
    * Output:        None.
    * Exceptions:    KeyExists if the given key already exists
    * Return Values: true-if insert succeded
     *               false if not
    */
    template <class Compare>
    bool Insert(const T &data, const Compare& compare) {
        if (this->root == nullptr) {
            this->root=new Vertex<T>(data);
            return true;
        }
        Vertex<T> *right, *left;
        //Key wasnt found
        if (!(split(this->root, left, right, data,compare))) {
            Vertex<T>* new_root=new Vertex<T>(data,left,right);
            this->root=new_root;
            return true;
        }
            //Key exists
        else{
            return false;
        }
    }

    /* Description:   This function deletes the given key from the S_T
     * Input:         Data to be saved
    *               key in dictionary
    * Output:        None.
    * Exceptions:    KeyDoesntExists if the given key doesnt exists
    * Return Values: None
*/
    template <class Compare>
    bool Delete(const T& data,const Compare& compare) {
        if(this->root== nullptr){
            return false;
        }
        //key was found
        if(this->Search(data,compare)){
            Vertex<T>* toDelete=this->root;
            this->root=join(this->root->left,this->root->right,compare);
            delete toDelete;
            return true;
        }
        else{
            return false;
        }
    }
    template <class Function>
    void InOrder(const Function& func){
        inOrderTraversal(this->root,func);
    }

    T& GetRoot(){
        return this->root->data;
    }

};

/**---------------Implementation of Splay_tree functions--------------------*/

#endif //DS_HW_1_SPLAY_TREE_H
