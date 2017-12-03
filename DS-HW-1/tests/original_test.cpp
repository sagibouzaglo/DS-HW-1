//
// Created by Amir on 03/12/2017.
//

#include "../Colosseum.h"
#include <iostream>
#include <sstream>

int main(){
    Colosseum* colosseum=new Colosseum();
    colosseum->AddTrainer(4);
    colosseum->AddTrainer(3);
    colosseum->BuyGladiator(101,4,50);
    colosseum->AddTrainer(5);
    colosseum->BuyGladiator(101,5,25);
    colosseum->BuyGladiator(102,5,25);
    int top;
    colosseum->GetTopGladiator(-1,&top);
    colosseum->LevelUp(102,26);
    colosseum->FreeGladiator(102);
    colosseum->UpgradeGladiator(101,105);
    colosseum->UpgradeGladiator(105,101);
    colosseum->BuyGladiator(105,4,5);
    colosseum->BuyGladiator(120,5,15);
    colosseum->UpdateLevels(5,4);

    int numOfGlads,*gladiators;
    assert(colosseum->GetAllGladiatorsByLevel(-1,&gladiators,&numOfGlads)==SUCCESS);
    std::cout << "Printing gladiators:(ID)\n";
    for(int i=0;i<numOfGlads;i++){
        std::cout <<"("<< gladiators[i] <<") " ;
    }
    return 0;

}