//
// Created by Amir on 02/12/2017.
//

#include "../Colosseum.h"
#include <iostream>
#include <sstream>

#define BARCA 1
#define MANU 2
#define REAL 3

#define MESSI 10
#define FELLAINI 31
#define CR7 7
#define SUAREZ 9
#define BALE 11
#define RASHFORD 19


#define GOD 100
#define B_DOR 99
#define CAPTAIN 10
#define AVG 5

int main(){
    Colosseum* colosseum=new Colosseum;
    //Check Colosseum add trainer:
    assert(colosseum->AddTrainer(0)==INVALID_INPUT);
    assert(colosseum->AddTrainer(BARCA)==SUCCESS);
    assert(colosseum->AddTrainer(BARCA)==FAILURE);
    assert(colosseum->AddTrainer(REAL)==SUCCESS);
    assert(colosseum->AddTrainer(MANU)==SUCCESS);
    //Check Colosseum BuyGladiator
    assert(colosseum->BuyGladiator(0,7,7)==INVALID_INPUT);
    assert(colosseum->BuyGladiator(7,0,7)==INVALID_INPUT);
    assert(colosseum->BuyGladiator(0,7,7)==INVALID_INPUT);
    assert(colosseum->BuyGladiator(MESSI,BARCA,GOD)==SUCCESS);
    assert(colosseum->BuyGladiator(FELLAINI,50,1)==FAILURE);//No such trainer
    assert(colosseum->BuyGladiator(MESSI,REAL,GOD)==FAILURE);//Glad exists
    assert(colosseum->BuyGladiator(CR7,REAL,B_DOR)==SUCCESS);
    assert(colosseum->BuyGladiator(FELLAINI,MANU,CAPTAIN)==SUCCESS);
    assert(colosseum->BuyGladiator(RASHFORD,MANU,AVG)==SUCCESS);
    assert(colosseum->BuyGladiator(SUAREZ,BARCA,AVG)==SUCCESS);
    assert(colosseum->BuyGladiator(BALE,REAL,AVG)==SUCCESS);
    /** Check Colosseum_FreeGladiator-----------------------------------------*/
    assert(colosseum->FreeGladiator(0)==INVALID_INPUT);
    assert(colosseum->FreeGladiator(MESSI)==SUCCESS);
    assert(colosseum->FreeGladiator(MESSI)==FAILURE);
    /** Check Colosseum_Gladiatorlvlup and Get-Top-----------------------------------------*/
    assert(colosseum->BuyGladiator(MESSI,BARCA,GOD)==SUCCESS);
    assert(colosseum->LevelUp(CR7,1)==SUCCESS);
    int best;
    assert(colosseum->GetTopGladiator(-1,&best)==0);
    assert(best==7);
    assert(colosseum->GetTopGladiator(1,&best)==SUCCESS);
    assert(best==10);
    assert(colosseum->GetTopGladiator(2,&best)==SUCCESS);
    assert(best==31);
    assert(colosseum->GetTopGladiator(3,&best)==SUCCESS);
    assert(best==7);
    assert(colosseum->GetTopGladiator(4,&best)==FAILURE);
    assert(colosseum->GetTopGladiator(0,&best)==INVALID_INPUT);
    assert(colosseum->GetTopGladiator(2,nullptr)==INVALID_INPUT);
    colosseum->FreeGladiator(7);
    assert(colosseum->GetTopGladiator(-1,&best)==SUCCESS);
    assert(best==10);
    assert(colosseum->GetTopGladiator(3,&best)==SUCCESS);
    assert(best==11);
    assert(colosseum->BuyGladiator(CR7,REAL,B_DOR)==SUCCESS);
/** Check Colosseum_getAllbylvl-----------------------------------------*/
    int numOfGlads,*gladiators;
    assert(colosseum->GetAllGladiatorsByLevel(-1,&gladiators,&numOfGlads)==SUCCESS);
    std::cout << "Printing gladiators:(ID)\n";
    for(int i=0;i<numOfGlads;i++){
        std::cout <<"("<< gladiators[i] <<") " ;
    }
    int i=0;
    return 0;
}