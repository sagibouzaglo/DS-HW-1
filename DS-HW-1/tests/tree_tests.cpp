//
// Created by Amir on 29/11/2017.
//

#include "mtmtest.h"
#include "../Splay_Tree.h"



int main() {
   // testInsert();
    SplayTree<int> tree;
    int arr[] = {1,3,2,5,4,6,7,9,8,11,10,14,13,12,20,18,19,16,17,15};
    for(int i=0; i<100; i++)
        tree.Insert(rand()%50,rand()%100);
    tree.Search(12);
    tree.Search(7);
    tree.Search(14);
    /*
    for(int i=1; i<10; i++)
        tree.Delete(i+1);
        */
    std::cout << "InOrder Print: " << std::endl; //EXPECTED: 1 3 4 6 8 15 32
    tree.InOrderPrint();
    return 0;
}