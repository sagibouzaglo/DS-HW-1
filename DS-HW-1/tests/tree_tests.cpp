//
// Created by Amir on 29/11/2017.
//

#include "mtmtest.h"
#include "../Splay_Tree.h"

static void testInsert(){
    SplayTree<int> tree;
    tree.Insert(1,1);
    tree.Insert(2,2);
    tree.Insert(3,3);
    tree.Insert(4,4);

}


int main() {
   // testInsert();
    SplayTree<int> tree;
    int arr[] = {1,3,2,5,4,6,7,9,8,11,10,14,13,12,20,18,19,16,17,15};
    for(int i=0; i<20; i++)
        tree.Insert(arr[i],i);
    tree.Search(12);
    tree.Search(7);
    tree.Search(14);
    std::cout << "InOrder Print: " << std::endl; //EXPECTED: 1 3 4 6 8 15 32
    return 0;
}