//
// Created by Amir on 29/11/2017.
//

#include "mtmtest.h"
#include "../Splay_Tree.h"

class Compare {

public:
    explicit Compare(){}
    int operator()(const int& x, const int& y) const {
        if (x == y) return 0;
        else if (x < y) return 1;
        return -1;
    }
};

void printInt(const int& x) {
    std::cout << x << " ";
}

int main() {
        SplayTree<int> tree;
        int arr[8] = {1,15,3,8,32,6,4,8};
        for(int i=0; i<8; i++)
            tree.Insert<Compare>(arr[i],Compare());
            //tree.insertElement<Compare>(arr[i], Comp(arr[i]));
        std::cout << "InOrder Print: " << std::endl; //EXPECTED: 1 3 4 6 8 15 32
    tree.InOrderPrint(printInt);
    tree.Delete(8,Compare());
    tree.Delete(20,Compare());
    std::cout << "InOrder Print: " << std::endl; //EXPECTED: 1 3 4 6 8 15 32
    tree.InOrderPrint(printInt);

    for(int i=1; i<20; i++)
        tree.Insert((rand()%i)*(rand()%i +i),Compare());
    tree.Insert(12,Compare());
    tree.Search(12,Compare());
    for(int i=130; i<400; i++)
        tree.Delete(i,Compare());

    std::cout << "InOrder Print: " << std::endl; //EXPECTED: 1 3 4 6 8 15 32
    tree.InOrderPrint(printInt);
    return 0;
}